#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"



struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE* fp = fopen(filename, "rb");
  if (!fp) {
    printf("Error opening input file\n");
    return NULL;
  }

  char format[3];
  if (fscanf(fp, "%2s", format) != 1 || strcmp(format, "P6") != 0) {
    printf("Unsupported PPM format (must be P6).\n");
    fclose(fp);
    return NULL;
  }
   //skip whitespace and comment lines manually
  int c;
  while ((c = fgetc(fp)) != EOF) {
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
      // whitespace means skip
      continue;
    } else if (c == '#') {
      //skip entire comment line
      while ((c = fgetc(fp)) != '\n' && c != EOF);
    } else {
      //not whitespace or comment means put back
      ungetc(c, fp);
      break;
    }
  }

  //checking for valid header of a p6 file
  int maxval;
  if (fscanf(fp, "%d %d %d", w, h, &maxval) != 3 || maxval != 255) {
    printf("Invalid PPM header.\n");
    fclose(fp);
    return NULL;
  }

  fgetc(fp); //should skip space after header

  int size = (*w) * (*h);
  struct ppm_pixel* data = malloc(size * sizeof(struct ppm_pixel)); //allocating memory
  if (!data) {
    printf("Failed to allocate memory.\n");
    fclose(fp);
    return NULL;
  }

  if (fread(data, sizeof(struct ppm_pixel), size, fp) != size) {
    printf("Error reading pixel data.\n");
    free(data);
    fclose(fp);
    return NULL;
  }

  fclose(fp);
  return data;
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  
  return NULL;
}
