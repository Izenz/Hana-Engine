#pragma once
#include <iostream>

// Documentation: https://www.geeksforgeeks.org/how-to-create-a-custom-string-class-in-c-with-basic-functionalities/
// Install RenderDock
class MyString {

	friend MyString operator+(const MyString& string1, const MyString& string2);
	friend std::ostream& operator<<(std::ostream& os, const MyString& string);

public:
	MyString();
	MyString(const char* value);
	MyString(const MyString& str);
	MyString(MyString&& str) noexcept;
	~MyString();

	MyString& operator=(const MyString& value);
	bool operator==(const MyString& string1);
	bool operator==(const char* string1);

	int length() const;
	void clear();
private:
	int strlen(const char* value) const;
	char* strcpy(char* destination, const char* source);
	bool compare(const char* buffer, int length)

private:
	char* characters;
};