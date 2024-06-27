#include "MyString.h"
#include <vector>
#include <algorithm>

int main(int argc, char* argv[])
{
	std::vector<MyString> strings;

	if (argc <= 1)
	{
		return 0;
	}

	for (int i = 1; i < argc; ++i)
	{
		strings.emplace_back(argv[i]);
	}
	std::sort(strings.begin(), strings.end());
	std::reverse(strings.begin(), strings.end());

	for (auto& string : strings)
	{
		std::cout << string << " ";
	}
	return 0;
}
