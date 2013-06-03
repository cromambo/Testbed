#include <iostream>
using std::cout;
using std::endl;

class Integer 
{
public:
	// Integer();
	// ~Integer();
	Integer operator++(int);
	Integer& operator++();
protected:

private:
	int i;
};

Integer Integer::operator++(int)
{
Integer temp = (*this); //copy by value
	operator++(); //could be the increment but this prevents duplicating code
	return temp;
}

Integer& Integer::operator++()
{
	i = i+1;
	return *this;
}


int main(int argc, char* argv[]) 
{
	  int a = 5;
	  cout << a <<endl;
	  cout <<a++ <<endl;
	  cout <<++a <<endl;
	  return 0;
}