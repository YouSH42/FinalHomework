#include <iostream>
using namespace std;

class A{
	public:
		A(int x){ cout << x << endl;}
		//A(){cout << "생성자A" << endl;}
		//~A(){cout << "소멸자A" << endl;}
};

class B : public A{
	public:
		B() : A(10){cout << "생성자B" << endl;}
		//~B(){cout << "소멸자B" << endl;}
};

class C : public B{
	public:
		C(){cout << "생성자C" << endl;}
		//~C(){cout << "소멸자C" << endl;}
};

int main(void){
	C c;

	return 0;
}
