#include <iostream>

#define is_good(nb) !(nb % 20) && !(nb % 19) && !(nb % 18) && !(nb % 17) && !(nb % 16) && \
	!(nb % 15) && !(nb % 14) && !(nb % 13) && !(nb % 12) && !(nb % 11)

int main()
{
	uint64_t result = 20;
	while (1) {
		if (is_good(result)) {
			break;
		}
		++result;
	}
	std::cout << "The result is: " << result << std::endl;
	return 0;
}
