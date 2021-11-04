#include "MyString.h" 
#include <iostream>

MyString GetMeAString();

int main()
{
	MyString a("hello");
	MyString c = GetMeAString();
	MyString b(a);
	//MyString d = a + c;
	
	if(c == "hello hello")
		std::cout << "Working well." << std::endl;
	else
		std::cout << "Error." << std::endl;
		

	std::cout << "The string 'a' is: " << a.length() << " characters long." << std::endl;

	c.clear();
	std::cout << "String a: " << a << std::endl;
}

MyString GetMeAString() {
	return MyString(std::move("another string"));
}