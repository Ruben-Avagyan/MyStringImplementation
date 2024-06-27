#include "MyString.h"

#include <cctype>

void MyString::copyString(const char* cString)
{
	delete[] data;
	size = strlen(cString);
	data = new char[size + 1];

	for (size_t i = 0; i < size; ++i)
	{
		data[i] = cString[i];
	}

	data[size] = '\0';
}

void MyString::invalidate()
{
	data = nullptr;
	size = 0;
}

MyString::MyString(const char* cString)
{
	copyString(cString);
}

MyString::MyString(const MyString& string)
{
	copyString(string.data);
}

MyString::MyString(MyString&& string) noexcept :
data(string.data),
size(string.size)
{
	string.invalidate();
}

MyString& MyString::operator+=(const MyString& string)
{
	size_t sizeOfNewString = string.size + size;
	char* newString = new char[sizeOfNewString + 1];
	newString[sizeOfNewString] = '\0';

	for(size_t i = 0; i < size; ++i)
	{
		newString[i] = data[i];
	}

	for(size_t i = size; i < sizeOfNewString; ++i)
	{
		newString[i] = string.data[i - size];
	}

	delete[] data;
	size = sizeOfNewString;
	data = newString;

	return *this;
}

MyString& MyString::operator+=(const char* cString)
{
	size_t sizeOfNewString = strlen(cString) + size;
	char* newString = new char[sizeOfNewString + 1];
	newString[sizeOfNewString] = '\0';

	for (size_t i = 0; i < size; ++i)
	{
		newString[i] = data[i];
	}

	for (size_t i = size; i < sizeOfNewString; ++i)
	{
		newString[i] = cString[i - size];
	}

	delete[] data;
	size = sizeOfNewString;
	data = newString;

	return *this;
}

MyString& MyString::operator=(const MyString& string)
{
	if (this == &string)
		return *this;

	copyString(string.data);
	return *this;
}

MyString& MyString::operator=(MyString&& string) noexcept
{
	if (this == &string)
		return *this;

	delete[] data;
	size = string.size;
	data = string.data;
	string.invalidate();

	return *this;
}

MyString& MyString::operator=(const char* cString)
{
	copyString(cString);
	return *this;
}

MyString operator+(const MyString& firstString, const MyString& secondString)
{
	return MyString(firstString) += secondString;
	// No need to use std::move here.
	// The compiler will automatically use move semantics
	// due to Return Value Optimization (RVO) or Named Return Value Optimization (NRVO).
}

MyString operator+(const MyString& firstString, const char* cString)
{
	return MyString(firstString) += MyString(cString);
}

MyString operator+(const char* cString, const MyString& secondString)
{
	return MyString(cString) += MyString(secondString);
}

bool operator<(const MyString& firstString, const MyString& secondString)
{
	char* first = new char[firstString.size + 1];
	char* second = new char[secondString.size + 1];

	strcpy_s(first, firstString.size + 1, firstString.data);
	strcpy_s(second, secondString.size + 1, secondString.data);

	for (size_t i = 0; i < strlen(first); ++i)
	{
		if (first[i] >= 'A' && first[i] <= 'Z')
		{
			first[i] = first[i] + ('a' - 'A');
		}
	}

	for (size_t i = 0; i < strlen(second); ++i)
	{
		if (second[i] >= 'A' && second[i] <= 'Z')
		{
			second[i] = second[i] + ('a' - 'A');
		}
	}
	bool result = strcmp(first, second) < 0;

	delete[] first;
	delete[] second;
	return result;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	os << str.data;
	return os;
}