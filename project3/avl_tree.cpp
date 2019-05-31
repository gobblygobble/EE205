/*
 * Skeleton code for project 3 in EE205 2017 Fall KAIST
 * Created by Yoonpyo Koo.
 */

#include "avl_tree.h"
#include <iostream>
#include <string>
#include <list>
/* 
 * Include your linked list here 
 * e.g., #include "your_linked_list_header.h"
 */

using namespace std;

/* 
 * You can do this! Feel free to ask to TA if you have anything unclear. 
 * I'm here to help you!
 */

/* Return the height of the tree. Remember external nodes are valid nodes. 
 * Suppose we have a tree as follows. * means an external node.
 *           a
 *         /   \
 *        b     c
 *       / \   / \
 *      d   * *   *
 *     / \
 *    *   *
 * Then this tree has the height of 3
 *
 * ### Already implemented.
 */
template <class T>
int AVLTree<T>::height(AVLNode<T> *n) {
  return n->height;
}

/*
 * Assign proper height value after operations on nodes.
 * You will need this function in some functions.
 * such as rotate_right(), rotate_left(), balance(), etc.
 *
 * Make sure all children have proper heights before you execute
 * this function on a node.
 *
 * ### Already implemented.
 */
template <class T>
void AVLTree<T>::update_height(AVLNode<T> *n) {
  if (is_external(n)) {
    n->height = 0;
  }
  else {
    int lh = height(n->leftChild);
    int rh = height(n->rightChild);

    n->height = (lh >= rh ? lh : rh) + 1;
  }
}

/* Print keys along inorder traversal. Separate each key by a single space.
 * Do not print external node's key, which is an empty string.
 * e.g.,
 *           a
 *         /   \
 *        b     c
 *       / \   / \
 *      d   * *   *
 *     / \
 *    *   *
 * Then this function should print "d b a c " (with no newline character).
 * 
 */
template <class T>
void AVLTree<T>::inorder_print(AVLNode<T> *n) {
  //if ((n->leftChild != NULL) || (n->rightChild != NULL)) {
  if (!is_external(n)) {
    // if n is an internal node
    inorder_print(n->leftChild);
  }
  if (!is_external(n)) {
    // 'visit' a node - print only if the key is not 'null'
    std::cout << n->key << " ";
  }
  //if ((n->leftChild != NULL) || (n->rightChild != NULL)) {
  if (!is_external(n)) {
    // if n is an internal node
    inorder_print(n->rightChild);
  }
}

/* 
 * Print keys along preorder traversal. 
 * The rule is the same as inorder_print(), except the order. 
 */
template <class T>
void AVLTree<T>::preorder_print(AVLNode<T> *n) {
  //if ((n->leftChild != NULL) || (n->rightChild != NULL)) {
  if (!is_external(n)) {
    std::cout << n->key << " "; // 'visit' a node
    // if n is an internal node
    preorder_print(n->leftChild);
    preorder_print(n->rightChild);
  }
}

/* Refer to the supplementary PPT file. */
template <class T>
void AVLTree<T>::balance(AVLNode<T> *n) {
  AVLNode<T>* node = n;
  if (!is_external(node)) {
    update_height(node);
  }
  while (!is_root(node)) {
    node = node->parent;
    update_height(node);
    if (balance_factor(node) == 2) {
      // left - 
      if (balance_factor(node->leftChild) >= 0) {
	// left - left
	rotate_right(node);
      }
      else {
	// left - right
	rotate_left(node->leftChild);
	rotate_right(node);
      }

    }
    else if (balance_factor(node) == -2) {
      // right - 
      if (balance_factor(node->rightChild) <= 0) {
	// right - right
	rotate_left(node);
      }
      else {
	// right - left
	rotate_right(node->rightChild);
	rotate_left(node);
      }
    }
    // do nothing if well balanced
  }
}

/* For your reference, the function has already been implemented. */
template <class T>
AVLNode<T>* AVLTree<T>::rotate_right(AVLNode<T> *n) {
  AVLNode<T> *x = n->leftChild;

  n->leftChild = x->rightChild;
  n->leftChild->parent = n;

  x->rightChild = n;
  x->parent = n->parent;
  if (is_root(n)) {
    // make sure root always points to the root of the tree
    root = x;
  }
  else {
    // originally: if (!is_root(n)) {...
    if (n->parent->leftChild == n)
      n->parent->leftChild = x;
    else
      n->parent->rightChild = x;
  }
  n->parent = x;

  /* the order of updates is important */
  update_height(n);
  update_height(x);

  return x;
}

/* Refer to the supplementary PPT file. And right above ↑↑↑ */
template <class T>
AVLNode<T>* AVLTree<T>::rotate_left(AVLNode<T> *n) {
  AVLNode<T>* y = n->rightChild;

  n->rightChild = y->leftChild;
  n->rightChild->parent = n;

  y->leftChild = n;
  y->parent = n->parent;
  if (is_root(n)) {
    root = y;
  }
  else {
    // originally: if (!is_root(n)) {...
    if (n->parent->leftChild == n) {
      n->parent->leftChild = y;
    }
    else {
      n->parent->rightChild = y;
    }
  }
  n->parent = y;

  update_height(n);
  update_height(y);

  return y;
}

/* 
 * Refer to page 6 of the lecture note 'SearchTrees-BST_AVL'.
 * CAUTION: You HAVE TO implement this function the way described in the lecture note.
 * Use string::compare function for comparison between two keys.
 */
template <class T>
AVLNode<T>* AVLTree<T>::search(string key) {
  AVLNode<T>* n = root;
  while (!is_external(n)) {
    if (key < n->key) {
      n = n->leftChild;
    }
    else if (key > n->key) {
      n = n->rightChild;
    }
    else {
      return n;
    }
  }
  // reaching here means such node does not exist - n is external
  return n;
}

/*
 * I have also implemented this function for your reference and convenience. 
 * 조교 자비 오지고 지리고 렛잇고 아리랑 고개를 넘ㅇ...
 */
template <class T>
bool AVLTree<T>::insert(string key) {
  AVLNode<T> *n = search(key);

  if (is_external(n)) {
    n->key = key;
    n->leftChild = new AVLNode<T>("", n);
    n->rightChild = new AVLNode<T>("", n);

    balance(n);

    return true;
  }
  else
    return false; // the key already exists
}

/* 
 * Remove a node. Return true if successful(if the key exists), false otherwise. 
 * Refer to page 8~9, 22~23 of the lecture note 'SearchTrees-BST_AVL'.
 * CAUTION: You HAVE TO implement this function the way described in the lecture note.
 */
template <class T>
bool AVLTree<T>::remove(string key) {
  AVLNode<T>* rNode = search(key);
  if (is_external(rNode)) {
    // such key does not exist
    return false;
  }
  // such key is found
  if ((is_external(rNode->leftChild)) || (is_external(rNode->rightChild))) {
    /* case 1: the node has at least one external node as a child
     * in this case, make sure to re-balance the tree after deletion */
    AVLNode<T>* Child = is_external(rNode->leftChild) ? rNode->rightChild : rNode->leftChild;
    AVLNode<T>* delChild = Child == rNode->leftChild ? rNode->rightChild : rNode->leftChild;
    Child->parent = rNode->parent;
    if (is_root(rNode)) {
      root = Child;
    }
    else {
      // originally: if (!is_root(rNode)) {...
      if (rNode->parent->leftChild == rNode) {
	rNode->parent->leftChild = Child;
      }
      else {
	rNode->parent->rightChild = Child;
      }
      update_height(rNode->parent);
    }

    delete(delChild);
    delete(rNode);
    balance(Child);
    return true;
  }
  /* case 2: both of the nodes are internal
   * in this case, the tree is still balanced 
   * therefore, no need to rebalance */
  int went_left = 0;
  AVLNode<T>* inorderNext = rNode->rightChild;
  while (!is_external(inorderNext->leftChild)) {
    inorderNext = inorderNext->leftChild;
    went_left = 1;
  }
  rNode->key = inorderNext->key;
  delete(rNode->value);
  rNode->value = inorderNext->value;
  // information copy complete
  if (went_left) {
    // if the above while loop has been executed at least once
    inorderNext->parent->leftChild = inorderNext->rightChild;
    inorderNext->rightChild->parent = inorderNext->parent;
  }
  else {
    // if while loop has not been executed - inorderNext->parent == rNode
    rNode->rightChild = inorderNext->rightChild;
    inorderNext->rightChild->parent = rNode;
  }
  delete(inorderNext->leftChild);
  delete(inorderNext);
  return true;
}

/* 
 * You need to explicitly instantiate the template to use it in the main function.
 * Instantiate here if you need to.
 * e.g., 
 * template class AVLTree<Your_linkedlist_class>;
 */
template class AVLTree<std::list<int> >;

/* You can do it! */

