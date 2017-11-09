#include <iostream>

int main () {
	uint64_t number = 600851475143;
	uint64_t factor = 3;

	while (factor < number) {
		if (!(number % factor)) {
			number /=factor;
			std::cout << number << " " << factor << std::endl;
		}
		++factor;
	}

	std::cout << number << std::endl;
	return 0;
}
