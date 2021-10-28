#pragma once

// Documentation: https://www.geeksforgeeks.org/how-to-create-a-custom-string-class-in-c-with-basic-functionalities/
// Install RenderDock
class MyString {
public:
	MyString();
	MyString(const char* value);
	MyString(const MyString& str);
	MyString(MyString&& str);
	~MyString() { delete characters; }

	//MyString& push_back();
	int length() const;
	void clear();

private:
	char* characters;
};