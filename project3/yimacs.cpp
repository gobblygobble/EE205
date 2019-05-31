/*
 * Skeleton code for project 3 in EE205 2017 Fall KAIST
 * Created by Yoonpyo Koo
 *
 * Helper functions are from Michael Mrozek's answer on stackoverflow
 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "avl_tree.h"
#include <list>
#include <algorithm>
// for measuring time:
//#include <ctime>
/* Include more if you need to */

using namespace std;

/* typedef for AVLTree<T> and AVLNode<T> */
typedef AVLTree<std::list<int> > AVT;
typedef AVLNode<std::list<int> > AVN;
/* typedef for std::list<std::string> */
typedef std::list<std::string> LL;

/* Helper functions */ 
/* Use these functions to replace words in a string. */
bool replace(string& str, const string& from, const string& to) {
  size_t start_pos = str.find(from);
  if(start_pos == std::string::npos)
    return false;
  str.replace(start_pos, from.length(), to);
  return true;
}

void replace_all(string& str, const string& from, const string& to) {
  if(from.empty())
    return;
  size_t start_pos = 0;
  while((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}

/* This function is a modified version of replace_all()
 * It is changed to not change words such as Who-ville to What-ville,
 * when we try to replace 'Who' with 'What' */
void modified_replace_all(string& str, const string& from, const string& to) {
  if (from.empty())
    return;
  size_t start_pos = 0;
  string new_from = " " + from + " ";
  string new_to = " " + to + " ";
  string new_from2 = " " + from;
  string new_to2 = " " + to;
  // first, replace all that have spaces on both ends.
  while ((start_pos = str.find(new_from, start_pos)) != std::string::npos) {
    str.replace(start_pos, new_from.length(), new_to);
    start_pos += new_to.length();
  }
  // check if first word of str is from
  if (str.find(from) == 0) {
    // change if the next letter is a space
    if (str.at(from.length()) == ' ') {
      str.replace(0, from.length(), to);
    }
  }
  // check if the last word of str is from, and if it has a space in front of it
  if (str.find(new_from2, (str.length() - new_from2.length())) == (str.length() - new_from2.length())) {
    str.replace((str.length() - new_from2.length()), new_from2.length(), new_to2);
  }
}
/* Helper functions end */

int main(int argc, char* argv[])
{
  // for measuring time:
  //clock_t beginTime = clock();
  if (argc != 3) {
    std::cerr << "Wrong format of arguments given." << std::endl;
    return -1;
  }

  AVT* groot = new AVT;
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
    /* the next line and the do-while statement are from
     * community wiki's Ashwin Nanjappa's post on Stack Overflow,
     * on "the most elegant way to iterate the words of a string" */

    std::istringstream one_word(line);
    do {
      one_word >> word;
      AVN* node = groot->search(word);
      if (groot->is_external(node)) {
	// the word does not exist
	groot->insert(word);
	groot->search(word)->value->push_back(lineNum);
      }
      else {
	// the word already exists
	if (std::find(node->value->begin(), node->value->end(), lineNum) ==
	    node->value->end()) {
	  // if the word did not already exist in the line
	  node->value->push_back(lineNum);
	}
	// if the word already exists, do nothing
      }
    } while (one_word);
  }
  // done with input file -> close
  ifile.close();

  while (std::getline(std::cin, line)) {
    std::istringstream command(line);
    command >> rq;
    if (rq.compare("R") == 0) {
      // replace
      if ((command >> w_from)&&(command >> w_to)) {
	// if two valid words are given
	AVN* wf_node = groot->search(w_from);
	AVN* wt_node = groot->search(w_to);
	if (groot->is_external(wf_node)) {
	  // if wf_node doeen't exist, stop processing
	  continue;
	}
	if (groot->is_external(wt_node)) {
	  // if wt_node doesn't already exist, create one
	  groot->insert(w_to);
	  wt_node = groot->search(w_to);
	}
	int lineNow;
	LL::iterator it;
	while (!wf_node->value->empty()) {
	  // change sentence, and print them
	  it = Giancarlo_Stanton->begin();
	  lineNow = wf_node->value->front();
	  wf_node->value->pop_front();
	  for (int i = 0; i < lineNow - 1; i++) {
	    it++;
	  }
	  std::string &sentence = *it;
	  std::cout << "< " << sentence << std::endl;
	  //replace_all(sentence, w_from, w_to);
	  modified_replace_all(sentence, w_from, w_to);
	  std::cout << "> " << sentence << std::endl;
	  wt_node->value->push_back(lineNow);
	}
	// sort the list of wt_node
	wt_node->value->sort();
	groot->remove(w_from);
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
  // DO SOMETHING ABOUT TREE ELEMENTS BEFORE DELETING GROOT!
  delete(groot);
  // close the output file and terminate program
  ofile.close();
  // for measuring time:
  //clock_t endTime = clock();
  //double runTime = double(endTime - beginTime) / CLOCKS_PER_SEC;
  //std::cout << "Running time: " << runTime << " s." << std::endl;
  return 0;
}
