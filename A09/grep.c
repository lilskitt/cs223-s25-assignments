/*----------------------------------------------
 * grep.c
 * Author: Lola Peyrouse-Bremer
 * Date: March 28 2025
 * Implements a program that uses N processes to search for a keyword in a set of files
---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

/**
* search_in_file
* Opens a file and searches for the specified keyword line by line
* @param filenameecho "This is a test file." > file1.txt

* @param keyword
* @return void
*/
void search_in_file(const char *filename, const char *keyword) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("Process [%d] Error: Cannot open file %s\n", getpid(), filename);
    exit(0);
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int occurrences = 0;

  while ((read = getline(&line, &len, file)) != -1) {  
    //getline(char **lineptr, size_t *n, FILE *stream) stores lines of various lengths
    printf("[%d] Checking line: %s", getpid(), line); //debugging the output
    char *ptr = line;
    while ((ptr = strstr(ptr, keyword)) != NULL) { //count occurrences
      occurrences++;
      ptr += strlen(keyword); //continue counting after found one
    }
  }

  free(line);
  fclose(file);
  exit(occurrences); //does this save occurances
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("usage: ./grep <NumProcesses> <Keyword> <Files>\n");
    return 1;
  }

  int num_processes = atoi(argv[1]); //number of processes
  char *keyword = argv[2]; //keyword to look for
  int num_files = argc - 3;
  char **files = &argv[3];

  //number of processes only go as high as number of files given
  if (num_processes > num_files) { 
    num_processes = num_files;
  }

  printf("Searching %d files using %d processes for keyword: %s\n", num_files, num_processes, keyword);

  //"Your program should report the amount of time needed to search using gettimeofday"
  struct timeval start, end;
  gettimeofday(&start, NULL);

  int total_occurrences = 0;
  int file_index = 0;

  //dynamically allocate the different pipes
  int **pipes = malloc(num_processes * sizeof(int *));
  for (int i = 0; i < num_processes; i++) {
    pipes[i] = malloc(2 * sizeof(int));
    pipe(pipes[i]); //create a pipe
  }

  int files_per_process = num_files / num_processes; //split work
  int extra_files = num_files % num_processes; //remainder, work toward correctly assigning processes to files
  for (int i = 0; i < num_processes; i++) {
    pid_t pid = fork();
    if (pid == 0) { //child
      close(pipes[i][0]); //close

      int process_occurrences = 0;

      //shortened if-statement: 
      //if i < extra_files is true, it evaluates to 1, if i < extra_files is false, it evaluates to 0
      int num_files_for_this_process = files_per_process + (i < extra_files ? 1 : 0);

      //printing what the proccesses are doing
      int start_idx = file_index + 1;
      int end_idx = start_idx + num_files_for_this_process - 1;
      printf("Process [%d] searching %d files (%d to %d)\n", getpid(), num_files_for_this_process, start_idx, end_idx);

      //files per process
      for (int j = 0; j < num_files_for_this_process; j++) {
        int local_occurrences = 0;
        FILE *file = fopen(files[file_index + j], "r");
        if (!file) {
          printf("Process [%d] Error: Cannot open file %s\n", getpid(), files[file_index + j]);
          continue; //jump to next iteration of loop skipping the rest
        }

        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        while ((read = getline(&line, &len, file)) != -1) {
          char *ptr = line;
          while ((ptr = strstr(ptr, keyword)) != NULL) {
            local_occurrences++;
            ptr += strlen(keyword); //continue through file after finding occurance to get all of em
          }
        }

        free(line);
        fclose(file);
        process_occurrences += local_occurrences; //update 
      }

      //be able to return number of occurances
      printf("Process [%d] found %d lines containing keyword: %s\n", getpid(), process_occurrences, keyword);
      write(pipes[i][1], &process_occurrences, sizeof(int));
      close(pipes[i][1]);
      exit(0);
      } else if (pid > 0) { //parent
        close(pipes[i][1]); //close
        file_index += files_per_process + (i < extra_files ? 1 : 0); //if-statement shortened
      } else {
        printf("fork");
        exit(1);
      }
  }

  for (int i = 0; i < num_processes; i++) {
    int occurrences = 0;
    read(pipes[i][0], &occurrences, sizeof(int));
    close(pipes[i][0]);
    total_occurrences += occurrences; //update total occurances after going thru
    free(pipes[i]); //free ALL
  }
  free(pipes);

  //random stuff that's supposed to print
  //"Your program should report the amount of time needed to search using gettimeofday"
  gettimeofday(&end, NULL);
  double elapsed_time = (end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec) / 1000000.0);
  printf("Total occurrences: %d\n", total_occurrences);
  printf("Elapsed time is %f seconds\n", elapsed_time);
  return 0;
}
