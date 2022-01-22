#include <iostream>
#include<math.h>
#include<cstring>
#include<string>

#define PI 3.1416
using namespace std;

class Rectangle {
 public:
  int length;
  int breath;

  int area() {
	return length * breath;
  }

  int perimeter() {
	return 2 * (length + breath);
  }

};

int main() {
  Rectangle r;
  Rectangle *p = new Rectangle();
  r.length = 10;
  r.breath = 299;
  p->breath = 10;
  p->length = 2999;
  cout << p->perimeter() << endl;
  cout << r.area() << endl;
  cout << r.perimeter() << endl;
  cout << &r << endl;
  cout << p << endl;

}
