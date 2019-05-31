#include <iostream>
#include <string>
#include <cstdlib>
// //***************************************************************
// //                   CLASS USED IN PROJECT
// //****************************************************************


class Student{
  //private:
 protected:
  std::string name;
  int stu_num;
  int stu_type;
 public:
  Student(std::string _name, int _stu_num);
  virtual void getInfo() = 0; // Pure virtual function
  int getType();
  std::string getName();
  int getStuNum();
};

class Grad_Student: public Student{
 private:
  std::string lab_name;
  //protected:
 public:
  Grad_Student(std::string _name, int _stu_num, std::string _labname);
  virtual void getInfo();
  std::string getLabName();
};

class Undergrad_Student: public Student{
 private:
  int freshmen_class;
  //protected:
 public:
  Undergrad_Student(std::string _name, int _stu_num, int _freshmenclass);
  virtual void getInfo();
  int getFreshmenClass();
};


class Manager {
 private:
  Student* studentArray[300];
  int totalStudents;
  //protected:
 public:
  Manager();
  int add_student(std::string name, int stunum, std::string labname);
  int add_student(std::string name, int stunum, int freshmenclass);
  bool compare_student(int index, std::string name, int stunum, std::string labname);
  bool compare_student(int index, std::string name, int stunum, int freshmenclass);
  int find_student(std::string name, int stunum, std::string labname);
  int find_student(std::string name, int stunum, int freshemenclass);
  int delete_student(std::string name, int stunum, std::string labname);
  int delete_student(std::string name, int stunum, int freshmenclass);
  int print_all();
  int how_many_students();
};

bool operator==(const Student& student1, const Student& student2);
