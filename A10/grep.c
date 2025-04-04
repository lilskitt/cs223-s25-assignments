/*----------------------------------------------
 * grep.c
 * Author: Lola Peyrouse-Bremer
 * Date: April 4 2025
 * Implements a simplified version of the bash command grep
---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>
#include <time.h> //get elapsed time

typedef struct {
  int thread_id;
  int num_files;
  int start_index;
  int end_index;
  char **files;
  char *keyword;
  int count;
} ThreadData;

/**
* search_file
* porcess files and print summary of lines found with teh keyword
* @param arg 
* @return void
*/
void *search_files(void *arg) {
  ThreadData *data = (ThreadData *)arg; //general ptr casted to ThreadData
  data->count = 0;

  printf("Thread %d searching %d files (%d to %d)\n",
    data->thread_id,
    data->num_files,
    data->start_index,
    data->end_index - 1);

  for (int i = 0; i < data->num_files; i++) {
    char *filename = data->files[i];
    FILE *file = fopen(filename, "r");

    if (!file) {
      printf("Thread [%d] Error: Cannot open file %s\n", data->thread_id, filename);
      continue;
    }

    char full_path[PATH_MAX];
    realpath(filename, full_path);
    char line[1024];
    int line_number = 0;

    //read line by line, buffer stores each line, line_number stores the line number
    while (fgets(line, sizeof(line), file)) {
      line_number++;
      //checks each line for keyword
      if (strstr(line, data->keyword)) {
        printf("%s:%d: %s", full_path, line_number, line);
        data->count++;
      }
    }
    fclose(file);
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  /**
  use these:
  echo "This is a test file." > file1.txt
  echo "The keyword class appears here." > file2.txt
  echo "Another line with class keyword." > file3.txt
  echo "No keyword here." > file4.txt
  */

  if (argc < 4) {
    printf("usage: ./grep <NumThreads> <Keyword> <Files>\n");
    return 1;
  }

  //take command line input, same as last time
  int num_threads = atoi(argv[1]);
  char *keyword = argv[2];
  int num_files = argc - 3;
  char **files = &argv[3];

  if (num_threads > num_files) {
    num_threads = num_files; //so there's not more threads than files
  }

  //reiterating user request
  printf("Searching %d files using %d threads for keyword: %s\n", num_files, num_threads, keyword);
  
  //time tracking
  time_t start_time = time(NULL);

  pthread_t *threads = malloc(sizeof(pthread_t) * num_threads);
  ThreadData *thread_data = malloc(sizeof(ThreadData) * num_threads);

  int files_per_thread = num_files / num_threads; //how many threads each file will be assigned
  int extra_files = num_files % num_threads; //for remainder files that get distributed to threads
  int file_index = 0; //where to start assigning

  //thread cretion and file distribution
  for (int i = 0; i < num_threads; i++) {
    int current_files = files_per_thread + (i < extra_files ? 1 : 0);
    thread_data[i].thread_id = i;
    thread_data[i].num_files = current_files;
    thread_data[i].files = &files[file_index];
    thread_data[i].keyword = keyword;
    thread_data[i].start_index = file_index;
    thread_data[i].end_index = file_index + current_files;
    file_index += current_files;

    pthread_create(&threads[i], NULL, search_files, &thread_data[i]);
  }

  //join when finished
  for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  //print everything assignment wanted
  for (int i = 0; i < num_threads; i++) {
    printf("Thread %d found %d lines containing keyword: %s\n",
    thread_data[i].thread_id, thread_data[i].count, keyword);
  }
  time_t end_time = time(NULL);
  double elapsed = difftime(end_time, start_time);
  printf("Elapsed time is %.2f seconds\n", elapsed); //why was it 0s

  //free because malloc'd
  free(threads);
  free(thread_data);
  return 0;
}
