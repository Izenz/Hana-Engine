#include "MyString.h" 
#include <iostream>

MyString GetMeAString();

int main()
{
	MyString a = GetMeAString();
	MyString b(a);
	std::cout << "The string passed is: " << a.length() << " characters long." << std::endl;
}

MyString GetMeAString() {
	return MyString("another string");
}