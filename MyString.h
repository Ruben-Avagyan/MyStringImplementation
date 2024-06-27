#pragma once
#include <cstdio>
#include <cstring>
#include <iostream>

// Class for managing dynamic strings
class MyString
{
	char* data{nullptr};
	size_t size{0};

public:
	//Default constructor
	MyString() : data(nullptr), size(0) {}

	// Constructor from C-style string
	MyString(const char* cString);

	// Copy constructor
	MyString(const MyString& string);

	// Move constructor
	MyString(MyString&& string) noexcept;

	//Destructor
	~MyString() { delete[] data; }

	//Addition assignment operators
	MyString& operator+=(const MyString& string); 
	MyString& operator+=(const char* cString);

	//Assignment operators
	MyString& operator=(const MyString& string);
	MyString& operator=(MyString&& string) noexcept;
	MyString& operator=(const char* cString);

private:
	// Helper function for copying a string
	void copyString(const char* cString);

	// Helper function for invalidating the object
	void invalidate();

	//Friend functions for concatenation
	friend MyString operator+(const MyString& firstString, const MyString& secondString);
	friend MyString operator+(const MyString& firstString, const char* cString);
	friend MyString operator+(const char* cString, const MyString& secondString);

	// Friend function for output
	friend std::ostream& operator<<(std::ostream& os, const MyString& str);

	// Friend function for comparison
	friend bool operator<(const MyString& firstString, const MyString& secondString);
};