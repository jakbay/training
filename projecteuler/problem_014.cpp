#include <iostream>
#include <future>

uint64_t collatzNb(const uint64_t &seed) {
	uint64_t value = seed;
	uint64_t steps = 0;
	while (value != 1) {
		if (value % 2) {
			value *= 3;
			++value;
		} else {
			value /= 2;
		}
		++steps;
	}
	return ++steps;
}

uint64_t collatzWorker(const uint64_t begin, const uint64_t end) {
	uint64_t max = 0;
	uint64_t nb = 0;
	for (auto i = begin; i <= end; ++i) {
		uint64_t &&tmp = 0;
		if ((tmp = collatzNb(i)) > max) {
			max = tmp;
			nb = i;
		}
	}
	return nb;
}

int main()
{
	uint64_t result = collatzWorker(1, 999999);
	std::cout << "The result is: " << result << std::endl;
	return 0;
}
