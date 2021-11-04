#include "MyString.h"
#include <iostream>

// Default constructor
MyString::MyString() {
	characters = nullptr;
	// Check everywhere that pointer is not null
}

// Constructor with one parameter
MyString::MyString(const char* value) {
	std::cout << "Constructed string" << std::endl;
	if (value == nullptr) {
		characters = new char[1];
		characters[0] = '\0';
	}

	else {
		characters = new char[MyString::strlen(value) + 1];
		strcpy(characters, value);
	}
}

// Copy constructor
MyString::MyString(const MyString& value) {
	std::cout << "Copied string" << std::endl;
	characters = new char[strlen(value.characters) + 1];
	strcpy(characters, value.characters);
}

// Move constructor
MyString::MyString(MyString&& value) noexcept {
	std::cout << "Moved string" << std::endl;
	characters = value.characters;
	value.characters = nullptr;
}

MyString::~MyString() {
	std::cout << "Destroyed string" << std::endl;
	delete characters;
}

int MyString::length() const {
	return strlen(characters);
}

void MyString::clear() {
	if(characters != null)
		delete characters;
	characters = new char[1];
	characters[0] = '\0';
}

int MyString::strlen(const char* value) const{
	int size = 0;
	while (value[size] != '\0') {
		++size;
	}
	return size;
}

char* MyString::strcpy(char* destination, const char* source) {
	char* start = destination;

	while (*source != '\0') {
		*destination = *source;
		++destination;
		++source;
	}

	*destination = '\0';
	return start;
}

// Also need this function for rvalues.
MyString& MyString::operator=(const MyString& value){
	if (this == &value)
		return *this;
	delete[] characters;
	characters = new char[strlen(value.characters) + 1];
	strcpy(characters, value.characters);
	return *this;
}

std::ostream& operator<<(std::ostream& os, const MyString& string){
	os << string.characters;
	return os;
}

MyString operator+(const MyString& string1, const MyString& string2){
	int length = strlen(string1.characters)
		+ strlen(string2.characters);

	char* buff = new char[length + 1];

	//strcpy(buff, string1.characters);
	//strncat_s(buff, string2.characters, strlen(string2.characters));

	MyString temp{ buff };

	delete[] buff;

	return temp;
}

bool operator==(const MyString& string1, const MyString& string2){
	int it = 0;
	if (strlen(string1.characters) != strlen(string2.characters)) {
		return false;
	}
	else {
		while (string1.characters[it] != '\0') {
			if (string1.characters[it] != string2.characters[it])
				return false;
			else
				++it;
		}
	}
	
}

bool MyString::compare(const char* buffer, length){
	// ...
}


