/*----------------------------------------------
 * dependency.c
 * Author: Lola Peyrouse-Bremer
 * Date: February 28 2025
 * List file dependencies
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

/** 
 * Process each file and extract dependencies
 * @param root of the tree
 * @param filename of file
 * @return void
 */
void processFile(struct tree_node* root, const char* filename) {
  FILE* file = fopen(filename, "r");
  if (!file) {
    printf("%s not found\n", filename);
    return;
  }

  char line[1024];
  //fgets reads a line of text from a file, read whole file
  //looks for any #include's and skips + any leading spaces
  while (fgets(line, sizeof(line), file)) {
    char* includePos = strstr(line, "#include"); //strstr returns loc of subtring "#include" within "line"
    if (includePos) {
      char depFilename[256];
      int i = 0;
      includePos += 8; //move ahead of #include

      //skip spaces/tabs
      while (*includePos == ' ' || *includePos == '\t') {
        includePos++;
      }
      
      //check if in quotes or brackets
      if (*includePos == '"') {
        includePos++; //skip opening quote
        while (*includePos && *includePos != '"') {
          depFilename[i++] = *includePos++;
        }
      } else if (*includePos == '<') {
        includePos++;  //skip opening bracket
        while (*includePos && *includePos != '>') {
          depFilename[i++] = *includePos++;
        }
      }
      depFilename[i] = '\0';
      //check if the dependency exists in the tree
      struct tree_node* depNode = find(depFilename, root);
      if (!depNode) {
        root = insert(depFilename, root);
        depNode = find(depFilename, root);
      }
    }
  } //end outer while loop

  fclose(file);
}

/** 
 * Print the dependencies of a file
 * @param root
 * @param filename
 * @return void
 */
void printDependencies(struct tree_node* root, const char* filename) {
  struct tree_node* fileNode = find(filename, root);
  if (fileNode == NULL) {
      printf("%s not found\n", filename);
      return;
  }
  printf("%s has the following dependencies\n", fileNode->data.name);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
      printf("Please provide a file\n");
      return 1;
  }

  struct tree_node* root = NULL;
  //insert each file into the binary search tree (tree.c)
  for (int i = 1; i < argc; i++) {
      root = insert(argv[i], root);
  }

  //process each file dependency
  for (int i = 1; i < argc; i++) {
      processFile(root, argv[i]);
  }
  printf("Processing %d files\n", argc - 1);

  //command loop
  char command[256];
  while (1) {
      printf("$ ");
      fgets(command, sizeof(command), stdin);

      command[strcspn(command, "\n")] = '\0';

      if (strcmp(command, "quit") == 0) {
          break;
      } else if (strcmp(command, "list") == 0) {
          printSorted(root);
      } else {
          printDependencies(root, command);
      }
  }

  clear(root);
  return 0;
}
