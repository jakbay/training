#include <iostream>
#include <vector>
#include <cmath>

int main ()
{
	std::vector<uint64_t> primes{2};
	uint64_t nb = 3;
	bool found;
	uint64_t result = 2;

	while (nb < 2000000) {
		found = false;
		for (auto i : primes) {
			if (i > std::sqrt(nb)) {
				break;
			}
			if (!(nb % i)) {
				found = true;
				break;
			}
		}
		if (!found) {
			primes.push_back(nb);
			result += nb;
		}
		++nb;
	}
	std::cout << "The result is: " << result << std::endl;
	return 0;
}
