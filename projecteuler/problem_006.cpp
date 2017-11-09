#include <iostream>
#include <cmath>

int main ()
{
	uint32_t sum = 0;
	uint32_t sumOfSquares = 0;
	uint32_t squaredSum = 0;

	for (uint32_t i = 1; i <= 100; ++i) {
		sum += i;
		sumOfSquares += std::pow(i, 2);
	}
	squaredSum = std::pow(sum, 2);
	std::cout << "The result is: " << squaredSum - sumOfSquares << std::endl;
	return 0;
}
