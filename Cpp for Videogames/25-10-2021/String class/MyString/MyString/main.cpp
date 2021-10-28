#include "MyString.h"
#include <stdlib.h>

void main() {
	MyString str("hello");
	MyString a = GetMeAString();

}

MyString GetMeAString() {
	return MyString("another string");
}