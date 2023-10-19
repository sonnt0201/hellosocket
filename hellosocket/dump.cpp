#include <iostream>

#include <string>

using namespace std;

struct Student  {
  int p_id;
  string name;

};

int main() {
  int ex_id = 45;
  struct Student *s1 = new Student;
  
  s1->p_id= 123;
  // s1.p_id;
  printf("%d", ex_id);
}