#include <iostream>

int main()
{
	int result = 0;
	for (int i = 1; i < 1000; ++i) {
		if (!(i % 3) || !(i % 5)) {
			result += i;
		}
	}
	std::cout << "Result: " << result << std::endl;
	return 0;
}

