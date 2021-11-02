#include "MyString.h"
#include <iostream>

// Default constructor
MyString::MyString() {
	characters = new char[1];
	characters[0] = '\0';
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
	characters = nullptr;
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

