#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>
#include <sstream>

#include "single_list.h"

using namespace std;

/* DO NOT CHANGE INCLUDED HEADERS */

/* Returns 1 if inserting should go further back,
 * 0 if it is same(should be removed) and -1 if it should stop */
/* New functions are not allowed:
   int elementComparison(int insertdata1, int insertdata2, int comparedata1, int comparedata2) {
   if (insertdata1 > comparedata1) {
   return 1;
   }
   else if (insertdata1 < comparedata1) {
   return -1;
   }

   // Now inserting->data1 == compared->data1
   if (insertdata2 > comparedata2) {
   return 1;
   }
   else if (insertdata2 < comparedata2) {
   return -1;
   }
   // The numbers are identical.
   return 0;
   }
*/

int main(int argc, char* argv[])
{
  /* 1st arg: input file name , 2nd arg: output file name */
  /* Begin measuring time */
  clock_t beginTime = clock();
  int packetNum, packetOrder;
  int curPacketNum, newPacketNum, curPacketOrder, newPacketOrder;
  std::string message;
  std::string message2print;
  single_list list; // list of message packets
  list_elem* elem2add; // element to add to the list

  if (argc != 3) {
    std::cerr << "Wrong format of arguments given." << std::endl;
    return -1;
  }
	
  std::freopen(argv[1], "r", stdin);
  std::freopen(argv[2], "w", stdout);
	
  // Insert the first line, at the front
  if (std::cin >> packetNum) {
    std::cin >> packetOrder;
    std::cin >> message;
    elem2add = new list_elem(packetNum, packetOrder, message);
    list.list_insert_front(elem2add);
  }

  // Keep inserting at the correct place
  while (std::cin >> packetNum) {
    /* Format is always correct
     * therefore, while loop terminates when EOF is read */
    int checked = 0;
    list_elem* now;
    list_elem* before;
    std::cin >> packetOrder;
    std::cin >> message;
    elem2add = new list_elem(packetNum, packetOrder, message);

    for (now = list.list_head(); now != NULL; now = list.list_next(now)) {
      /*int check = elementComparison(packetNum,
	packetOrder,
	list.list_get_data1(now),
	list.list_get_data2(now));*/
      // Functions are not allowed. So change to:
      int insertdata1 = packetNum;
      int insertdata2 = packetOrder;
      int comparedata1 = list.list_get_data1(now);
      int comparedata2 = list.list_get_data2(now);
      int check;
      if (insertdata1 > comparedata1) {
	check = 1;
      }
      else if (insertdata1 < comparedata1) {
	check = -1;
      }

      else {
	// Now inserting->data1 == compared->data1
	if (insertdata2 > comparedata2) {
	  check = 1;
	}
	else if (insertdata2 < comparedata2) {
	  check = -1;
	}
	// The numbers are identical.
	else {
	  check = 0;
	}
      }

      if (check == 1) {
	// keep traversing.
	checked = 0;
	before = now;
	continue;
      }
      else if (check == -1) {
	list.list_insert_before(now, elem2add);
	checked = 1;
	before = now; // Not necessary
	break;
      }
      else {
	// Now check == 0
	list.list_replace(now, elem2add);
	checked = 1;
	before = now; // Not necessary
	break;
      }
    }
    if (checked == 0) {
      list.list_insert_after(before, elem2add);
    }
  }

  /* *** ONLY TO CHECK IF ABOVE CODE WORKS FINE *** */
  /*
    for (list_elem* now = list.list_head(); now != NULL; now = list.list_next(now)) {
    std::cout << list.list_get_data3(now) << std::endl;
    }
  */

  list_elem* elem2erase;
  curPacketNum = 0;
  while (!(list.list_empty())) {
    elem2erase = list.list_head();
    newPacketNum = list.list_get_data1(elem2erase);
    newPacketOrder = list.list_get_data2(elem2erase);
    message2print = list.list_get_data3(elem2erase);
    // Check packet status and 'goto' the right state processing place
    if (newPacketNum != curPacketNum) {
      goto newPacketNumber;
    }
    // message packet is unchanged.
    if ((curPacketOrder + 1) == newPacketOrder) {
      goto correctPacketOrder;
    }
    // packet is missing
    else {
      goto missingPacketOrder;
    }
  newPacketNumber:
    // if packet number has changed
    /* if curPacketNum != 0 (If a certain message has existed before),
     * print the end message sign. */
    if (curPacketNum != 0) {
      std::cout << "- End Message " << curPacketNum << std::endl << std::endl;
    }
    std::cout << "- Message " << newPacketNum << std::endl;
    curPacketOrder = 0;
    curPacketNum = newPacketNum;
    continue;
  correctPacketOrder:
    // if packet order is correct
    std::cout << message2print << std::endl;
    list.list_remove(elem2erase);
    curPacketOrder++;
    continue;
  missingPacketOrder:
    // if packet order is missing
    curPacketOrder++;
    std::cout << "WARNING: packet "
	      << curPacketOrder
	      << " of message "
	      << curPacketNum
	      << " is missing"
	      << std::endl;
    continue;
  }

  // print last 'end of message sign.'
  std::cout << "- End Message " << curPacketNum << std::endl << std::endl;

  /* End measuring time */
  clock_t endTime = clock();
  double runTime = double(endTime - beginTime) / CLOCKS_PER_SEC;
  std::cout << "Running time: " << runTime << " s." << std::endl;
  /* Close files and exit. */
  std::fclose(stdin);
  std::fclose(stdout);
  return 0;
}
