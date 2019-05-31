#include <iostream>
#include <string>

#include "single_list.h"

using namespace std;


//////////////////////////////////////////////
// CAUTION: DO NOT CHANGE INCLUDED HEADERS  //
//////////////////////////////////////////////


/* Our singly linked lists have one header elements: the "head" which
   points the first element. The 'next' link of the back header is
   NULL. 
   An empty list looks like this:

                  
          HEAD ---> NULL 
                  

   A list with two elements in it looks like this:
   
                   +-------+    +-------+
          HEAD --->|   1   |--->|   2   |--->NULL
                   +-------+    +-------+

   You should not change the name, input arguments, and
   input/output data types of existing functions. */



/*** COMPLETE FUNCTIONS BELOW ***/

/* SINGLY LINKED LIST */

/* Initializes LIST as an empty list with a head. */
single_list::single_list()
{
  head = NULL;
}

single_list::~single_list()
{
  list_elem* now = head;
  while (now != NULL) {
    list_elem* erase = now;
    now = now->next;
    delete(erase);
    erase = NULL;
  }
}

int
single_list::list_get_data1(list_elem *elem)
{
  return elem->data1;
}

int
single_list::list_get_data2(list_elem *elem)
{
  return elem->data2;
}

string
single_list::list_get_data3(list_elem *elem)
{
  return elem->data3;
}


/* Returns the element after ELEM in its list. */
list_elem *
single_list::list_next (list_elem *elem)
{
  return elem->next;
}


/* Returns LIST's head. */
list_elem *
single_list::list_head (void)
{
  return head;
}

/* Insert ELEM at the beginning of LIST, so that it becomes the head 
   in LIST. */
void 
single_list::list_insert_front (list_elem *elem)
{
  elem->next = head;
  head = elem;
}

/* Insert ELEM just before BEFORE, which may be either an interior
   element or a head. */
void 
single_list::list_insert_before (list_elem *before, list_elem *elem)
{
  if (before == head) {
    list_insert_front(elem);
  }
  else {
    for (list_elem* now = head; now != NULL; now = now->next) {
      if (now->next == before) {
	now->next = elem;
	elem->next = before;
	break;
      }
    }
  }
}

/* Insert ELEM just after AFTER, which may be either an interior
   element or a head. */
void 
single_list::list_insert_after (list_elem *after, list_elem *elem)
{
  elem->next = after->next;
  after->next = elem;
}

/* Replace FROM with TO and deconstruct FROM */
void 
single_list::list_replace (list_elem *from, list_elem *to)
{
  list_insert_after(from, to);
  list_remove(from);
}


/* Removes ELEM from its list and deconstructs it. */
void
single_list::list_remove (list_elem *elem)
{
  if (elem == head) {
    head = elem->next;
    if (elem) {
      delete(elem);
      elem = NULL;
    }
  }
  else {
    for (list_elem* now = head; now != NULL; now = now->next) {
      if (now->next == elem) {
	now->next = elem->next;
	if (elem) {
	  delete(elem);
	  elem = NULL;
	}
	break;
      }
    }
  }
}

/* Returns true if LIST is empty, false otherwise. */
bool 
single_list::list_empty (void)
{
  if (head == NULL) {
    return true;
  }
  return false;
}


