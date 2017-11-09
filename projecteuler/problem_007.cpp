#include <iostream>
#include <vector>

int main ()
{
	std::vector<uint32_t> primes{2, 3, 5, 7, 11, 13};
	uint32_t nb = 14;
	bool found;

	while (primes.size() < 10001) {
		found = false;
		for (auto i : primes) {
			if (!(nb % i)) {
				found = true;
				break;
			}
		}
		if (!found) {
			primes.push_back(nb);
		}
		nb++;
	}
	std::cout << "The result is: " << primes[10000] << std::endl;
	return 0;
}
