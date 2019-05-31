#include <iostream>
#include "student.h"

// //****************************************************************
// //                   REQUIRED FUNCTIONALITY IN PROJECT
// //****************************************************************

// 1. You need to implement every detail of the function defined below
// 2. You additionally need to implement getInfo methods in each classes.
// 3. You additionally need to implement 'operator overloading' with '==' which compares two students whether all the members are the same

/* Manager Class Method Implementation */
Manager::Manager()
{
  // Sets totalStudents to 0;
  totalStudents = 0;
};

int Manager::add_student(std::string name, int stunum, std::string labname)
{
  // Adds Grad_Student object with given argument
  // Returns the total number of objects in the student array after adding
  if (totalStudents >= 300) {
    // Storage is full
    std::cout << "Sorry, storage space is full." << std::endl;
    return totalStudents;
  }
  
  studentArray[totalStudents] = new Grad_Student(name, stunum, labname);
  std::cout << "add graduate student DONE" << std::endl;
  totalStudents++;
  return totalStudents;
};

int Manager::add_student(std::string name, int stunum, int freshmenclass)
{
  // Creates Undergrad_Student object with given argument
  // Returns the total number of objects in the student array after adding
  if (totalStudents >= 300) {
    // Storage is full
    std::cout << "Sorry, storage space is full." << std::endl;
    return totalStudents;
  }

  studentArray[totalStudents] = new Undergrad_Student(name, stunum, freshmenclass);
  std::cout << "add undergraduate student DONE" << std::endl;
  totalStudents++;
  return totalStudents;
};

// You need to implement operator overloading and use it in compare_student

bool Manager::compare_student(int index, std::string name, int stunum, int freshmenclass)
{
  // Compares whether the object with given index argument in the student array is the same to Undergrad_Student object with given arguments followed by index.
  // Returns true if they are the same, false otherwise
  int index1 = index;
  int index2 = find_student(name, stunum, freshmenclass);
  if (index2 == 0) {
    //std::cout << "Such student does not exist." << std::endl;
    return false;
  }
  std::cout << "compare to undergraduate student DONE" << std::endl;
  /* THIS DOES NOT WORK->WHY?
   * Student first_student = *studentArray[index1 - 1];
   * Student second_student = *studentArray[index2 - 1];
   * return (first_student == second_student); */
  return (studentArray[index1 - 1] == studentArray[index2 - 1]);
};

bool Manager::compare_student(int index, std::string name, int stunum, std::string labname)
{
  // Compares whether the (index argument)th object in the student array is the same to Grad_Student object with given given argument follwed by index.
  // Returns true if they are the same, false otherwise

  int index1 = index;
  int index2 = find_student(name, stunum, labname);
  if (index2 == 0) {
    //std::cout << "Such student does not exist." << std::endl;
    return false;
  }
  std::cout << "compare to graduate student DONE" << std::endl;
  /*
   * Student first_student = *studentArray[index1 - 1];
   * Student second_student = *studentArray[index2 - 1];
   * return (first_student == second_student); */
  return (studentArray[index1 - 1] == studentArray[index2 - 1]);
};

int Manager::find_student(std::string name, int stunum, std::string labname)
{
  // Finds the Grad_Student object in the student array which is the same to Grad_Student object with given argument
  // This method should print all the information about matched object
  // Returns index of matched object (index of first object = 1), 0 if there's no match
  int i, index;
  int found = 0;
  Grad_Student* GradStudent;
  for (i = 0; i < totalStudents; i++) {
    if (studentArray[i]->getType() == 4) {
      GradStudent = (Grad_Student*)studentArray[i];
      if ((GradStudent->getName() == name)
	  && (studentArray[i]->getStuNum() == stunum)
	  && (GradStudent->getLabName() == labname)) {
	found = 1;
	index = i + 1;
	break;
      }
    }
  }
  std::cout << "find graduate student DONE" << std::endl;
  if (found) {
    return index;
  }
  std::cout << "find undergraduate student DONE" << std::endl;
  return 0;
};

int Manager::find_student(std::string name, int stunum, int freshmenclass)
{
  // Finds the Undergrad_Student object in the student array which is the same to Undergrad_Student object with given argument
  // This method should prints all the information about matched object
  // Returns index of matched object (index of first object = 1), 0 if there's no match
  int i, index;
  int found = 0;
  Undergrad_Student* UgradStudent;
  for (i = 0; i < totalStudents; i++) {
    if (studentArray[i]->getType() == 8) {
      UgradStudent = (Undergrad_Student*)studentArray[i];
      if ((UgradStudent->getName() == name)
	  && (studentArray[i]->getStuNum() == stunum)
	  && (UgradStudent->getFreshmenClass() == freshmenclass)) {
	found = 1;
	index = i + 1;
	break;
      }
    }
  }
  std::cout << "find undergraduate student DONE" << std::endl;
  if (found) {
    return index;
  }
  std::cout << "Such student does not exist." <<std::endl;
  return 0;
};

int Manager::delete_student(std::string name, int stunum, std::string labname)
{
  // Deletes the Grad_Student object in the student array which is the same to Grad_Student object with given argument, does nothing if there's no matching
  // Returns the total number of objects in the student array after deleting
  int index = find_student(name, stunum, labname);
  if (index) {
    delete studentArray[index - 1];
    for (int i = index - 1; i < (totalStudents - 1); i++) { //Does not execute if totalStudents = 1
      studentArray[i] = studentArray[i + 1];
    }
    totalStudents--;
  }
  std::cout << "delete graduate student DONE" << std::endl;
  return totalStudents;
};

int Manager::delete_student(std::string name, int stunum, int freshmenclass)
{
  // Deletes the Undergrad_Student object in the student array which is the same to Undergrad_Student object with given argument, does nothing if there's no matching
  // Returns the total number of objects in the student array after deleting
  int index = find_student(name, stunum, freshmenclass);
  if (index) {
    delete studentArray[index - 1];
    for (int i = index - 1; i < (totalStudents - 1); i++) { //Does not execute if totalStudents = 1
      studentArray[i] = studentArray[i + 1];
    }
    totalStudents--;
  }
  std::cout << "delete undergraduate student DONE" << std::endl;
  return totalStudents;
};

int Manager::print_all()
{
  for (int i = 0; i < totalStudents; i++) {
    studentArray[i]->getInfo();
  }
  if (totalStudents == 0) std::cout << "Storage space is empty." << std::endl;
  std::cout << "print all DONE" << std::endl;
  return 0;
};

int Manager::how_many_students()
{
  // Returns the total number of students in the student array
  return totalStudents;
}

/* Student Class Method Implementations */

Student::Student(std::string _name, int _stu_num)
{
  name = _name;
  stu_num = _stu_num;
  stu_type = 0;
};

int Student::getType()
{
  return stu_type;
}

std::string Student::getName()
{
  return name;
}

int Student::getStuNum()
{
  return stu_num;
}

/*void Student::getInfo()
{
  // This function will NOT be executed.
  std::cout << "Student name: " << name << "\nStudent number: " << stu_num << std::endl << std::endl;
  return;
};*/

/* Grad_Student Class Method Implementations */

Grad_Student::Grad_Student(std::string _name, int _stu_num, std::string _labname):
  Student(_name, _stu_num)
{
  lab_name = _labname;
  stu_type = 4;
};

std::string Grad_Student::getLabName()
{
  return lab_name;
}

void Grad_Student::getInfo()
{
  std::cout << "Student name: " << name << "\nStudent status: Graduate\nStudent number: "
	    << stu_num << "\nStudent's lab name: " << lab_name << std::endl << std::endl;
  return;
};

/* Undergrad_Student Class Method Implementations */

Undergrad_Student::Undergrad_Student(std::string _name, int _stu_num, int _freshmenclass):
  Student(_name, _stu_num)
{
  freshmen_class = _freshmenclass;
  stu_type = 8;
};

int Undergrad_Student::getFreshmenClass()
{
  return freshmen_class;
}

void Undergrad_Student::getInfo()
{
  std::cout << "Student name: " << name << "\nStudent status: Undergraduate \nStudent number: "
	    << stu_num << "\nStudent's freshmen class: " << freshmen_class << std::endl << std::endl;
  return;
};

/** Operator Overloading for Students **/

bool operator==(const Student& student1, const Student& student2)
{
  Student& kid1 = (Student&)student1;
  Student& kid2 = (Student&)student2;
  if (!(kid1.getType() == kid2.getType())) return false;
  if (kid1.getType() == 0) {
    std::cout << "We cannot compare two unspecified students." << std::endl;
    // CANNOT REACH HERE
    return false;
  }
  else if (kid1.getType() == 4) {
    // Grad_Student
    Grad_Student* gradStudent1 = (Grad_Student*)(&student1);
    Grad_Student* gradStudent2 = (Grad_Student*)(&student2);
    return ((gradStudent1->getName() == gradStudent2->getName())
	    &&(gradStudent1->getStuNum() == gradStudent2->getStuNum())
	    &&(gradStudent1->getLabName() == gradStudent2->getLabName()));
  }

  // Undergrad_Student
  Undergrad_Student* UgradStudent1 = (Undergrad_Student*)(&student1);
  Undergrad_Student* UgradStudent2 = (Undergrad_Student*)(&student2);
  /*std::cout << "Comparing two undergraduate students:" << std::endl
    << UgradStudent1->getName() << " "
    << UgradStudent2->getName() << std::endl
    << UgradStudent1->getStuNum() << " "
    << UgradStudent2->getStuNum() << std::endl
    << UgradStudent1->getFreshmenClass() << " "
    << UgradStudent2->getFreshmenClass() << std::endl;*/
  return ((UgradStudent1->getName() == UgradStudent2->getName())
	  &&(UgradStudent1->getStuNum() == UgradStudent2->getStuNum())
	  &&(UgradStudent1->getFreshmenClass() == UgradStudent2->getFreshmenClass()));
}
