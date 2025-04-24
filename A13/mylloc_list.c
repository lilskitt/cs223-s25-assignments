/*----------------------------------------------
 * mylloc_list.c
 * Author: Lola Peyrouse-Bremer
 * Date: April 25 2025
 * Edit the file to pass tests in unit_tests
---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

//this is the header
struct chunk {
  int size;
  int used;
  struct chunk *next;
};

//head ptr to flist
struct chunk *flist = NULL;

/**
 * aligns memory for all data types w void *
 * @param size requezted size
 * @return int new size
 */
 int align(int size) {
  int alignment = sizeof(void *);
  return (size + alignment - 1) & ~(alignment - 1);
}

/** 
 * look thru the free list for a free chunk, first-fit strat
 * removes the matching chunk
 * @param size needed
 * @return struct chunk thats suitable
 */
struct chunk *find_free_chunk(int size) {
  struct chunk *current = flist;
  struct chunk *prev = NULL;

  while (current) {
    if (current->used == 0 && current->size >= size) {
      //remove from free list to fix test 8
      if (prev) {
        prev->next = current->next;
      } else {
        flist = current->next;
      }
      current->next = NULL;
      return current;
    }
    prev = current;
    current = current->next;
  }

  return NULL;
}

/** 
 * creates new chunk of requested size
 * @param size of mem to allocate
 * @return struct chunk new chunk
 */
struct chunk *request_memory(int size) {
  void *p = sbrk(size + sizeof(struct chunk));
  if (p == (void *) -1) return NULL;

  struct chunk *new_chunk = (struct chunk *)p;
  new_chunk->size = size;
  new_chunk->used = size;
  new_chunk->next = NULL;

  return new_chunk;
}

/**
 * reuses any suitable free chunks, if not, create new
 */
void *malloc (size_t size) {
  // TODO: Implement malloc with a free list (See reading for details)
  if (size == 0) return NULL;

  int aligned_size = align(size);

  struct chunk *chunk = find_free_chunk(aligned_size);
  if (!chunk) {
    chunk = request_memory(aligned_size);
    if (!chunk) return NULL;

    //didn't work, test 2
    //chunk->next = flist;
    //flist = chunk;
  } else {
    chunk->used = aligned_size;
  }

  //return pointer to after metadata
  return (void *)(chunk + 1);
}

/**
 * to free is to mark as used, add to flist for future use
 */
void free(void *memory) {
  // TODO: Implement malloc with a free list (See reading for details)
  if (!memory) {
    return;
  }

  //add chunk to FRONT of flist
  struct chunk *chunk = ((struct chunk *)memory) - 1;
  chunk->used = 0;
  chunk->next = flist;
  flist = chunk;
}
