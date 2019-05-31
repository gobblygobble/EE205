#include <iostream>
#include <stdexcept>
#include <string>
#include "student.h"

int checkform_grad(std::string& _name, int& _stu_num, std::string& _lab_name);
int checkform_ugrad(std::string& _name, int& _stu_num, int& _freshmenclass);
int checkform_withIndex_grad(int& _index, std::string& _name, int& _stu_num, std::string& _lab_name);
int checkform_withIndex_ugrad(int& _index, std::string& _name, int& _stu_num, int& _freshmenclass);

// //****************************************************************
// //                   MAIN FUNCTION IN PROJECT
// //****************************************************************

int main()
{
  char command;
  Manager myman;
  int isgrad;
  std::string name;
  int stunum;
  std::string labname;
  int freshmenclass;
  int index;

  while(1){
    if (std::cin.eof()) {
      std::cout << "End of file. Terminating program." << std::endl;
      break;
    }
    std::cout << "\n\n\n*---------------------Welcome to Student Management System---------------------*" << std::endl;
    std::cout << "What do you want to do?\n1. Add student:a\n2. Compare student:c\n3. Find student:f\n4. Delete student:d\n5. Print all student:p" << std::endl;
    if (std::cin.fail()) {
      //std::cout << "failed! command: " << command << std::endl;
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      //std::getline(std::cin, cleaner);
      std::cin.clear();
      //std::cout << "got line: " << cleaner << std::endl;
    }
    std::cin >> command;
    if (std::cin.fail()) {
      std::cout << "Invalid argument." << std::endl;
      continue;
    }
    switch(command)
      {
      case 'a':{
	// Type of student you want to add (Graduate student or Undergraduate student)
	std::cout << "Add student executed\n\nType\nUndergraduate:0 Graduate:1"<< std::endl;
	if (std::cin >> isgrad) {
	  // Input is of integer type
	  if (isgrad == 1){
	    std::cout << "\nFormat: (name, stunum, labname)" << std::endl;
	    if (checkform_grad(name, stunum, labname)) {
	      myman.add_student(name, stunum, labname);
	    } 
	    else {
	      std::cout << "Invalid argument." << std::endl;
	    }
	    break;
	  }
		  
	  else if (isgrad == 0){
	    std::cout << "\nFormat: (name, stunum, freshmenclass) " << std::endl;
	    if (checkform_ugrad(name, stunum, freshmenclass)) {
	      myman.add_student(name, stunum, freshmenclass);
	    }
	    else {
	      std::cout << "Invalid argument." << std::endl;
	    }
	    break;
	  }
	  else {
	    // Input is an integer, but not 0 or 1.
	    std::cout << "Invalid argument." << std::endl;
	    break;
	  }
	}
	else {
	  // Input is NOT of integer type
	  std::cout << "Invalid argument." << std::endl;
	  std::cin.clear();
	  std::cin.ignore(100, '\n');
	  //std::getline(std::cin, cleaner);
	  std::cin.clear();
	  break;
	}
      }break;

      case 'c':{
	std::cout << "Compare student executed\n\nType\nUndergraduate:0 Graduate:1" << std::endl;
	if (std::cin >> isgrad) {
	  //Input is of integer type
	  if (isgrad == 1){
	    std::cout << "\nTarget student\nFormat: (index, name, stunum, labname)" << std::endl;
	    if (checkform_withIndex_grad(index, name, stunum, labname)) {
	      if (myman.compare_student(index, name, stunum, labname)) {
		std::cout << "The two students are identical." << std::endl;
	      }
	      else {
		std::cout << "The two students are not identical." << std::endl;
	      }
	    }
	    else {
	      std::cout << "Invalid argument." << std::endl;
	    }
	    break;
	  }
	      
	  else if (isgrad == 0){
	    std::cout << "\nTarget student\nFormat: (index, name, stunum, freshmenclass) " << std::endl;
	    if (checkform_withIndex_ugrad(index, name, stunum, freshmenclass)) {
	      if (myman.compare_student(index, name, stunum, freshmenclass)) {
		std::cout << "The two students are identical." << std::endl;
	      }
	      else {
		std::cout << "The two students are not identical." << std::endl;
	      }
	    }
	    else {
	      std::cout << "Invalid argument." << std::endl;
	    }
	    break;
	  }
	}
	else {
	  // Input is NOT of integer type
	  std::cout << "Invalid argument." << std::endl;
	  break;
	}
      }break;

      case 'f':{
	std::cout << "Find student executed\n\nType\nUndergraduate:0 Graduate:1" << std::endl;
	if (std::cin >> isgrad) {
	  //Input is of integer type
	  if (isgrad == 1){
	    std::cout << "\nFormat: (name, stunum, labname)" << std::endl;
	    if (checkform_grad(name, stunum, labname)) {
	      if (int found = (myman.find_student(name, stunum, labname))) {
		std::cout << "Student found. Index: " << found << std::endl;
	      }
	      else {
		std::cout << "Such student does not exist." << std::endl;
	      }
	    }
	    else {
	      std::cout << "Invalid argument." << std::endl;
	    }
	    break;
	  }
	  else if (isgrad == 0){
	    std::cout << "\nFormat: (name, stunum, freshmenclass)" << std::endl;
	    if (checkform_ugrad(name, stunum, freshmenclass)) {
	      if (int found = (myman.find_student(name, stunum, freshmenclass))) {
		std::cout << "Student found. Index: " << found << std::endl;
	      }
	      else {
		std::cout << "Such student does not exist." << std::endl;
	      }
	    }
	    else {
	      std::cout << "Invalid argument." << std::endl;
	    }
	    break;
	  }
	}
	else {
	  //Input is NOT of integer type
	  std::cout << "Invalid argument." << std::endl;
	  break;
	}
      }break;

      case 'd':{
	std::cout << "Delete student executed\n\nType\nUndergraduate:0 Graduate:1" << std::endl;
	if (std::cin >> isgrad) {
	  //Input is of integer type
	  if (isgrad == 1){
	    std::cout << "\nFormat: (name, stunum, labname)" << std::endl;
	    if (checkform_grad(name, stunum, labname)) {
	      myman.delete_student(name, stunum, labname);
	    }
	    else {
	      std::cout << "Invalid argument." << std::endl;
	    }
	    break;
	  }
	  else if (isgrad == 0){
	    std::cout << "\nFormat: (name, stunum, freshmenclass)" << std::endl;
	    if (checkform_ugrad(name, stunum, freshmenclass)) {
	      myman.delete_student(name, stunum, freshmenclass);
	    }
	    else {
	      std::cout << "Invalid argument." << std::endl;
	    }
	    break;
	  }
	}
	else {
	  //Input is NOT of integer type
	  std::cout << "Invalid argument." << std::endl;
	  break;
	}
      }break;

      case 'p':{
	std::cout << "Print all executed" << std::endl;
	myman.print_all();
	break;
      }break;

      default:{
	std::cout << "Invalid argument" << std::endl;
	break;
      }break;
      }
  }
  return 0;
}


int checkform_grad(std::string& _name, int& _stu_num, std::string& _lab_name) {
  
  /* Returns 1 if correct input */
  /* Returns 0 otherwise */
  /* This function parses the whole line. */
  int length;
  std::string line;
  int start0, start1, start2, end0, end1, end2, i;
  std::getline(std::cin, line); //Flush that '\n' left by "std::cin >>"
  std::getline(std::cin, line);
  length = line.length();
	
  i = 0;
  // First argument
  while ((i < length) && (isspace(line[i]))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  start0 = i;
  while ((i < length) && (!(isspace(line[i])))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  end0 = i - 1;
  // Second argument
  while ((i < length) && (isspace(line[i]))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  start1 = i;
  while ((i < length) && (!(isspace(line[i])))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  end1 = i - 1;
  // Third argument
  while ((i < length) && (isspace(line[i]))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  start2 = i;
  while ((i < length) && (!(isspace(line[i])))) {
    i++;
  }
  end2 = i - 1;

  if (i < length - 1) {
    i++;
    while ((i < length) && (isspace(line[i]))) {
      i++;
    }
    if (i != length) {
      return 0;
    }
  }
  // Now, 3 arguments have been passed successfully
  // name -> check if all isalpha()
  for (int j = start0; j < end0 + 1; j++) {
    if (!(isalpha(line[j]))) {
      return 0;
    }
  }
  // student number -> check if all isdigit(),
  // and check if ranges from 10000000 to 99999999 (8-digit number)
  for (int j = start1; j < end1 + 1; j++) {
    if (!(isdigit(line[j]))) {
      return 0;
    }
  }
  int check1 = atoi((line.substr(start1, end1 - start1 + 1)).c_str());
  if ((check1 < 10000000) || (check1 > 99999999)) {
    return 0;
  }
  // lab name -> check if all isalpha()
  for (int j = start2; j < end2 + 1; j++) {
    if (!(isalpha(line[j]))) {
      return 0;
    }
  }
  // All pass -> pass all arguments
  _name = line.substr(start0, end0 - start0 + 1);
  _stu_num = check1; // == atoi((line.substr(start1, end1 - start1 + 1)).c_str());
  _lab_name = line.substr(start2, end2 - start2 + 1);
  return 1;
}

int checkform_ugrad(std::string& _name, int& _stu_num, int& _freshmenclass) {
  
  /* Almost identical to checkform_grad() */
  int length;
  std::string line;
  int start0, start1, start2, end0, end1, end2, i;
  std::getline(std::cin, line); //Flush that '\n' left by "std::cin >>"
  std::getline(std::cin, line);
  length = line.length();
  i = 0;
  // First argument
  while ((i < length) && (isspace(line[i]))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  start0 = i;
  while ((i < length) && (!(isspace(line[i])))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  end0 = i - 1;
  // Second argument
  while ((i < length) && (isspace(line[i]))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  start1 = i;
  while ((i < length) && (!(isspace(line[i])))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  end1 = i - 1;
  // Third argument
  while ((i < length) && (isspace(line[i]))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  start2 = i;
  while ((i < length) && (!(isspace(line[i])))) {
    i++;
  }
  end2 = i - 1;

  if (i < length - 1) {
    i++;
    while ((i < length) && (isspace(line[i]))) {
      i++;
    }
    if (i != length) {
      return 0;
    }
  }
  // Now, 3 arguments have been passed successfully
  // name -> check if all isalpha()
  for (int j = start0; j < end0 + 1; j++) {
    if (!(isalpha(line[j]))) {
      return 0;
    }
  }
  // student number -> check if all isdigit(),
  // and check if ranges from 10000000 to 99999999 (8-digit number)
  for (int j = start1; j < end1 + 1; j++) {
    if (!(isdigit(line[j]))) {
      return 0;
    }
  }
  int check1 = atoi((line.substr(start1, end1 - start1 + 1)).c_str());
  if ((check1 < 10000000) || (check1 > 99999999)) {
    return 0;
  }
  // freshmen class -> check if all isdigit(),
  // and check if ranges from 1 to 31
  for (int j = start2; j < end2 + 1; j++) {
    if (!(isdigit(line[j]))) {
      return 0;
    }
  }
  int check2 = atoi((line.substr(start2, end2 - start2+ 1)).c_str());
  if ((check2 < 1) || (check2 > 31)) {
    return 0;
  }
  // All pass -> pass all arguments
  _name = line.substr(start0, end0 - start0 + 1);
  _stu_num = check1; // == atoi((line.substr(start1, end1 - start1 + 1)).c_str());
  _freshmenclass = check2; // == atoi((line.substr(start2, end2 - start2 + 1)).c_str());
  return 1;
}

int checkform_withIndex_grad(int& _index, std::string& _name, int& _stu_num, std::string& _lab_name) {
  
  /* Almost identical to checkform_grad() */
  int length;
  std::string line;
  int start0, start1, start2, end0, end1, end2, i;
  int start3, end3;
  std::getline(std::cin, line); //Flush that '\n' left by "std::cin >>"
  std::getline(std::cin, line);
  length = line.length();

  i = 0;
  // First argument
  while ((i < length) && (isspace(line[i]))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  start0 = i;
  while ((i < length) && (!(isspace(line[i])))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  end0 = i - 1;
  // Second argument
  while ((i < length) && (isspace(line[i]))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  start1 = i;
  while ((i < length) && (!(isspace(line[i])))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  end1 = i - 1;
  // Third argument
  while ((i < length) && (isspace(line[i]))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  start2 = i;
  while ((i < length) && (!(isspace(line[i])))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  end2 = i - 1;
  // Fourth argument
  while ((i < length) && (isspace(line[i]))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  start3 = i;
  while ((i < length) && (!(isspace(line[i])))) {
    i++;
  }
  end3 = i - 1;

  if (i < length - 1) {
    i++;
    while ((i < length) && (isspace(line[i]))) {
      i++;
    }
    if (i != length) {
      return 0;
    }
  }
  // Now, 4 arguments have been passed successfully
  // index -> check if all isdigit(),
  // and check if ranges from 1 to 300
  for (int j = start0; j < end0 + 1; j++) {
    if (!(isdigit(line[j]))) {
      return 0;
    }
  }
  int check0 = atoi((line.substr(start0, end0 - start0 + 1)).c_str());
  if ((check0 < 1) || (check0 > 300)) {
    return 0;
  }
  // name -> check if all isalpha()
  for (int j = start1; j < end1 + 1; j++) {
    if (!(isalpha(line[j]))) {
      return 0;
    }
  }
  // student number -> check if all isdigit(),
  // and check if ranges from 10000000 to 99999999 (8-digit number)
  for (int j = start2; j < end2 + 1; j++) {
    if (!(isdigit(line[j]))) {
      return 0;
    }
  }
  int check1 = atoi((line.substr(start2, end2 - start2 + 1)).c_str());
  if ((check1 < 10000000) || (check1 > 99999999)) {
    return 0;
  }
  // lab name -> check if all isalpha()
  for (int j = start3; j < end3 + 1; j++) {
    if (!(isalpha(line[j]))) {
      return 0;
    }
  }
  // All pass -> pass all arguments
  _index = check0; // == atoi((line.substr(start0, end0 - start0 + 1)).c_str());
  _name = line.substr(start1, end1 - start1 + 1);
  _stu_num = check1; // == atoi((line.substr(start2, end2 - start2 + 1)).c_str());
  _lab_name = line.substr(start3, end3 - start3 + 1);
  return 1;
}

int checkform_withIndex_ugrad(int& _index, std::string& _name, int& _stu_num, int& _freshmenclass) {
  
  /* Almost identical to checkform_grad() */
  int length;
  std::string line;
  int start0, start1, start2, end0, end1, end2, i;
  int start3, end3;
  std::getline(std::cin, line); //Flush that '\n' left by "std::cin >>"
  std::getline(std::cin, line);
  length = line.length();

  i = 0;
  // First argument
  while ((i < length) && (isspace(line[i]))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  start0 = i;
  while ((i < length) && (!(isspace(line[i])))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  end0 = i - 1;
  // Second argument
  while ((i < length) && (isspace(line[i]))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  start1 = i;
  while ((i < length) && (!(isspace(line[i])))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  end1 = i - 1;
  // Third argument
  while ((i < length) && (isspace(line[i]))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  start2 = i;
  while ((i < length) && (!(isspace(line[i])))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  end2 = i - 1;
  // Fourth argument
  while ((i < length) && (isspace(line[i]))) {
    i++;
  }
  if (i == length) {
    return 0;
  }
  start3 = i;
  while ((i < length) && (!(isspace(line[i])))) {
    i++;
  }
  end3 = i - 1;

  if (i < length - 1) {
    i++;
    while ((i < length) && (isspace(line[i]))) {
      i++;
    }
    if (i != length) {
      return 0;
    }
  }
  // Now, 4 arguments have been passed successfully
  // index -> check if all isdigit(),
  // and check if ranges from 1 to 300
  for (int j = start0; j < end0 + 1; j++) {
    if (!(isdigit(line[j]))) {
      return 0;
    }
  }
  int check0 = atoi((line.substr(start0, end0 - start0 + 1)).c_str());
  if ((check0 < 1) || (check0 > 300)) {
    return 0;
  }
  // name -> check if all isalpha()
  for (int j = start1; j < end1 + 1; j++) {
    if (!(isalpha(line[j]))) {
      return 0;
    }
  }
  // student number -> check if all isdigit(),
  // and check if ranges from 10000000 to 99999999 (8-digit number)
  for (int j = start2; j < end2 + 1; j++) {
    if (!(isdigit(line[j]))) {
      return 0;
    }
  }
  int check1 = atoi((line.substr(start2, end2 - start2 + 1)).c_str());
  if ((check1 < 10000000) || (check1 > 99999999)) {
    return 0;
  }
  // freshmen class -> check if all isdigit(),
  // and check if ranges from 1 to 31
  for (int j = start2; j < end2 + 1; j++) {
    if (!(isdigit(line[j]))) {
      return 0;
    }
  }
  int check2 = atoi((line.substr(start3, end3 - start3 + 1)).c_str());
  if ((check2 < 1) || (check2 > 31)) {
    return 0;
  }
  // All pass -> pass all arguments
  _index = check0; // == atoi((line.substr(start0, end0 - start0 + 1)).c_str());
  _name = line.substr(start1, end1 - start1 + 1);
  _stu_num = check1; // == atoi((line.substr(start2, end2 - start2 + 1)).c_str());
  _freshmenclass = check2; // == atoi((line.substr(start3, end3 - start3 + 1)).c_str());
  return 1;
}

