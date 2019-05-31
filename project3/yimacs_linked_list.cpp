/*
 * Modified code for Linked-list based impelementation of Yimacs (Yi + emacs)
 * Created by Jinha Chung
 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
/* Include more if you need to */
// for measuring time:
//#include <ctime>
using namespace std;

/* typedef for std::list<std::string> */
typedef std::list<std::string> LL;

/* Helper function */ 
/* This function is a modified version of modified_replace_all() in yimacs.cpp
 * It is changed to return the number of changes made in the given string& str */
int modified_replace_all2(string& str, const string& from, const string& to) {
  int is_modified = 0;
  if (from.empty()) {
    return is_modified;
  }
  size_t start_pos = 0;
  string new_from = " " + from + " ";
  string new_to = " " + to + " ";
  string new_from2 = " " + from;
  string new_to2 = " " + to;
  // first, replace all that have spaces on both ends.
  while ((start_pos = str.find(new_from, start_pos)) != std::string::npos) {
    str.replace(start_pos, new_from.length(), new_to);
    is_modified++;
    start_pos += new_to.length();
  }
  // check if first word of str is from
  if (str.find(from) == 0) {
    // change if the next letter is a space
    if (str.at(from.length()) == ' ') {
      str.replace(0, from.length(), to);
      is_modified++;
    }
  }
  // check if the last word of str is from, and if it has a space in front of it
  if (str.find(new_from2, (str.length() - new_from2.length())) == (str.length() - new_from2.length())) {
    str.replace((str.length() - new_from2.length()), new_from2.length(), new_to2);
    is_modified++;
  }return is_modified;
}
/* Helper function end */

int main(int argc, char* argv[])
{
  // for measuring time:
  //clock_t beginTime = clock();
  
  if (argc != 3) {
    std::cerr << "Wrong format of arguments given." << std::endl;
    return -1;
  }

  std::ifstream ifile(argv[1]); // input file - read only
  std::string line;
  std::string word;
  int lineNum = 0;
  int commandCount;
  std::string rq, w_from, w_to; // command variables
  LL* Giancarlo_Stanton = new LL;
	
  while (std::getline(ifile, line)) {
    lineNum++;
    Giancarlo_Stanton->push_back(line); // copy input file string into linked list
  }
  // done with input file -> close
  ifile.close();
  LL::iterator it;
  while (std::getline(std::cin, line)) {
    std::istringstream command(line);
    command >> rq;
    if (rq.compare("R") == 0) {
      // replace
      if ((command >> w_from)&&(command >> w_to)) {
	// if two valid words are given
	for (it = Giancarlo_Stanton->begin(); it != Giancarlo_Stanton->end(); it++) {
	  string temp = *it;
	  if (modified_replace_all2(*it, w_from, w_to)) {
	    std::cout << "< " << temp << std::endl;
	    std::cout << "> " << *it << std::endl;
	  }
	}
      }
      else {
	// wrong format
	goto wrong;
      }
    }
    else if (rq.compare("Q") == 0) {
      // quit
      goto quit;
    }
    else {
      // wrong format
    wrong:
      std::cout << "Wrong format of command given." << std::endl;
    }
  }
	
 quit:
  std::ofstream temp_ofile(argv[2]); // make output file if it did not exist already
  temp_ofile.close(); // close the file so we can reopen as read & write
  std::fstream ofile(argv[2]); // reopen output file as read & write
  while (!Giancarlo_Stanton->empty()) {
    ofile << Giancarlo_Stanton->front() << std::endl;
    Giancarlo_Stanton->pop_front();
  }
  delete(Giancarlo_Stanton);
  // close the output file and terminate program
  ofile.close();
  // for measuring time:
  //clock_t endTime = clock();
  //double runTime = double(endTime - beginTime) / CLOCKS_PER_SEC;
  //std::cout << "Running time: " << runTime << " s." << std::endl;
  return 0;
}
