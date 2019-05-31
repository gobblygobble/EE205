#include <iostream>
#include <string>

#include "double_list.h"

using namespace std;

//////////////////////////////////////////////
// CAUTION: DO NOT CHANGE INCLUDED HEADERS  //
//////////////////////////////////////////////

/* Our doubly linked lists have two header elements: the "head"
   just before the first element and the "tail" just after the
   last element. The 'prev' link of the front header is null, as
   is the 'next' link of the back header. Their other two links
   point toward each other via the interior elements of the list.

   An empty list looks like this:

                      +------+     +------+
                  <---| head |<--->| tail |--->
                      +------+     +------+

   A list with two elements in it looks like this:

        +------+     +-------+     +-------+     +------+
    <---| head |<--->|   1   |<--->|   2   |<--->| tail |<--->
        +------+     +-------+     +-------+     +------+

   The symmetry of this arrangement eliminates lots of special
   cases in list processing. That's a lot simpler than the code 
   would be without header elements.

   (Because only one of the pointers in each header element is used,
   we could in fact combine them into a single header element
   without sacrificing this simplicity.  But using two separate
   elements allows us to do a little bit of checking on some
   operations, which can be valuable.) 

   You SHOULD NOT change the name, input arguments, and
   input/output data types of existing functions. */



/*** COMPLETE FUNCTIONS BELOW ***/

/* Doubly LINKED LIST */

/* Initializes LIST as an empty list. 'prev' of 'head' and 'next' of
   'tail' in LIST have null. 'next' of 'head' points 'tail' and 'prev'
   of 'tail' points 'head'. */
double_list::double_list()
{
  head = new d_list_elem();
  tail = new d_list_elem();
  head->next = tail;
  tail->prev = head;
}

double_list::~double_list()
{
  while (!(d_list_empty())) {
    d_list_remove(d_list_front());
  }
  delete head;
  delete tail;
}

int
double_list::d_list_get_data1(d_list_elem *elem)
{
  return elem->data1;
}

int
double_list::d_list_get_data2(d_list_elem *elem)
{
  return elem->data2;
}

string
double_list::d_list_get_data3(d_list_elem *elem)
{
  return elem->data3;
}

/* Returns the element before ELEM in its list. If ELEM is the first 
   element in its list, returns the list head. Results are undefined 
   if ELEM is itself a list head. */
d_list_elem *
double_list::d_list_prev (d_list_elem *elem)
{
  return elem->prev;
}

/* Returns the element after ELEM in its list. If ELEM is the last
   element in its list, returns the list tail. Return NULL if ELEM is
   itself a list tail. */
d_list_elem *
double_list::d_list_next (d_list_elem *elem)
{
  return elem->next;
}


/* Returns LIST's head. */
d_list_elem *
double_list::d_list_head (void)
{
  return head;
}

/* Returns LIST's tail. */
d_list_elem *
double_list::d_list_tail (void)
{
  return tail;
}

/* Returns the front element in LIST. Return NULL if LIST is empty. */
d_list_elem *
double_list::d_list_front (void)
{
  if ((!d_list_empty())) {
    return head->next;
  }
  return NULL;
}

/* Returns the back element in LIST. Return NULL if LIST is empty. */
d_list_elem *
double_list::d_list_back (void)
{
  if (!(d_list_empty())) {
    return tail->prev;
  }
  return NULL;
}


/* Insert ELEM at the beginning of LIST, so that it becomes the front 
   in LIST. */
void 
double_list::d_list_insert_front (d_list_elem *elem)
{
  elem->next = head->next;
  head->next->prev = elem;
  head->next = elem;
  elem->prev = head;
}

/* Insert ELEM at the end of LIST, so that it becomes the back in LIST. */
void 
double_list::d_list_insert_back (d_list_elem *elem)
{
  elem->prev = tail->prev;
  tail->prev->next = elem;
  tail->prev = elem;
  elem->next = tail;
}

/* Insert ELEM just before BEFORE, which may be either an interior
   element or a tail. The latter case is equivalent to list_insert_back().
   Results are undefined if BEFORE is itself a list head. */
void 
double_list::d_list_insert_before (d_list_elem *before, d_list_elem *elem)
{
  before->prev->next = elem;
  elem->prev = before->prev;
  elem->next = before;
  before->prev = elem;
}

/* Insert ELEM just after AFTER, which may be either an interior
   element or a head. The latter case is equivalent to list_insert_front().
   Results are undefined if AFTER is itself a list tail. */
void 
double_list::d_list_insert_after (d_list_elem *after, d_list_elem *elem)
{
  after->next->prev = elem;
  elem->next = after->next;
  elem->prev = after;
  after->next = elem;
}

/* Replace FROM with TO and deconstruct FROM*/
void 
double_list::d_list_replace (d_list_elem *from, d_list_elem *to)
{
  d_list_elem* before = from->prev;
  d_list_elem* after = from->next;
  before->next = to;
  to->prev = before;
  after->prev = to;
  to->next = after;
  if (from) {
    delete(from);
  }
}


/* Removes ELEM from its list and deconstructs it.
   Undefined behavior if ELEM is not in a list. Results are undefined
   if ELEM is not an interior element of its list.
*/

void
double_list::d_list_remove (d_list_elem *elem)
{
  elem->prev->next = elem->next;
  elem->next->prev = elem->prev;
  if (elem) {
    delete(elem);
  }
}

/* Returns true if LIST is empty, false otherwise. */
bool 
double_list::d_list_empty (void)
{
  return (head->next == tail);
}

