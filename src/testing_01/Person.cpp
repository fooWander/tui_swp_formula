
#include <unistd.h>
#include <iostream>

class Person
{
public:
	int name;
};

class Mitarbeiter : public Person
{
public:
	void setNum(int num);
private:
	int my_num;
};

void Mitarbeiter::setNum(int num) {
	my_num = num;
	std::cout << my_num;
}

class Kunde : public Mitarbeiter
{
public:
	char a;
};

int main()
{

	std::cout << "Test";
	Person hans;

	hans.name = 4;

	Mitarbeiter x;
	x.name= 4;

	Kunde b;
	b.name = 4;
	b.a = 'c';

	std::cout << hans.name << std::endl << b.name << std::endl;
	x.setNum(42);
	b.setNum(64);
	return 0;
}