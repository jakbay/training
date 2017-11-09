#include <iostream>
#include <string>
#include <algorithm>

bool is_palindrome(uint32_t number)
{
	std::string snumber = std::to_string(number);
	std::string reverseNumber(snumber);
	std::reverse(reverseNumber.begin(), reverseNumber.end());
	return snumber == reverseNumber;
}

int main ()
{
	uint32_t lhs = 999;
	uint32_t rhs;
	uint32_t product;
	uint32_t result = 0;

	while (lhs) {
		rhs = 999;
		while (rhs) {
			product = lhs * rhs;
			if (product > result && is_palindrome(product)) {
				result = product;
			}
			--rhs;
		}
		--lhs;
	}
	exit:	
	std::cout << "The result is: " << result << std::endl;
	return 0;
}
