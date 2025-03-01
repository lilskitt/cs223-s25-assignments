/*----------------------------------------------
 * tree.c
 * Author: Lola Peyrouse-Bremer
 * Date: February 28 2025
 * Implement a binary search tree
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

/**
 * Finds a node with a name in the tree
 * @param name of the node to find
 * @param root of the tree or subtree to search in
 * @return pointer to the node if found, NULL otherwise
 */
struct tree_node* find(const char* name, struct tree_node* root) {
  if (root == NULL) {
    return NULL;
  }
  int cmp = strcmp(name, root->data.name);
  if (cmp == 0) {
    return root;  //found the node with the name
  } else if (cmp < 0) {
    return find(name, root->left); //search in the left subtree
  } else {
    return find(name, root->right); //search in the right subtree
  }
}

/**
 * Inserts a node with a name
 * @param name of the node to insert
 * @param root of the tree or subtree
 * @return new root of the tree or subtree
 */
struct tree_node* insert(const char* name, struct tree_node* root) {
  if (root == NULL) {
    root = (struct tree_node*)malloc(sizeof(struct tree_node));
    if (root == NULL) {
      printf("Unable to allocate memory for new tree node");
      exit(1);
    }
    strcpy(root->data.name, name);
    root->left = NULL;
    root->right = NULL;
    return root;
  }
  int cmp = strcmp(name, root->data.name);
  if (cmp < 0) {
    root->left = insert(name, root->left); //insert in the left subtree
  } else if (cmp > 0) {
    root->right = insert(name, root->right); //insert in the right subtree
  }

  return root;
}

/**
 * Clears the entire tree
 * @param root of the tree or subtree to clear
 * @return void
 */
void clear(struct tree_node* root) {
  if (root != NULL) {
    clear(root->left); //clear the left subtree
    clear(root->right); //clear the right subtree
    free(root); //free the current node
  }
}

/**
 * Prints the tree in a structured way
 * @param root of the tree or subtree to print
 * @return void
 */
void print(struct tree_node* root) {
  if (root == NULL) {
    return;
  }
  printf(" %s\n", root->data.name); //print the current node's name
  if (root->left != NULL) {
    printf(" l:%s\n", root->left->data.name); //print the left child
  }
  if (root->right != NULL) {
    printf(" r:%s\n", root->right->data.name); //print the right child
  }
  print(root->left); //print the left subtree
  print(root->right); //print the right subtree
}

/**
 * Prints the tree in order
 * @param root of the tree or subtree to print
 * @return void
 */
void printSorted(struct tree_node* root) {
  if (root == NULL) {
    return;
  }

  printSorted(root->left); //print the left subtree
  printf(" %s\n", root->data.name); //print the current node's name
  printSorted(root->right); //print the right subtree
}

