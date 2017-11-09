#include <iostream>

int main()
{
	unsigned first = 1;
	unsigned second = 2;
	unsigned third;
	unsigned result = 2;

	while ((third = first + second) < 4000000) {
		std::cout << first << " " << second << std::endl;
		third = first + second;
		if (!(third % 2)) {
			result += third;
		}
		first = second;
		second = third;
	}
	std::cout << "Result: " << result << std::endl;
	return 0;
}


