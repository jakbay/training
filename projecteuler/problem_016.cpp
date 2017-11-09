#include <iostream>
#include <string>
#include <vector>
#include <queue>

const uint64_t TWO_POW_64 = 0x8000000000000000;
const uint64_t TWO_POW_40 = 0x0000010000000000;

std::vector<std::string> values = {std::to_string(TWO_POW_64),
                                   std::to_string(TWO_POW_64),
                                   std::to_string(TWO_POW_64),
                                   std::to_string(TWO_POW_64),
                                   std::to_string(TWO_POW_64),
                                   std::to_string(TWO_POW_64),
                                   std::to_string(TWO_POW_64),
                                   std::to_string(TWO_POW_64),
                                   std::to_string(TWO_POW_64),
                                   std::to_string(TWO_POW_64),
                                   std::to_string(TWO_POW_64),
                                   std::to_string(TWO_POW_64),
                                   std::to_string(TWO_POW_64),
                                   std::to_string(TWO_POW_64),
                                   std::to_string(TWO_POW_64),
				   std::to_string(TWO_POW_40)};

std::string addNumbers(const std::string &lhs, const std::string &rhs)
{
        std::string result;
        auto itLhs = lhs.rbegin();
        auto itRhs = rhs.rbegin();
        unsigned char retenue = 0;
        bool lhsFinished = false;
        bool rhsFinished = false;

        while (!lhsFinished || !rhsFinished || retenue) {
                unsigned char &&lhsTmp = !lhsFinished ? (*itLhs - 0x30) : 0;
                unsigned char &&rhsTmp = !rhsFinished ? (*itRhs - 0x30) : 0;
                unsigned char &&sum = lhsTmp + rhsTmp;
                sum += retenue;
                result.insert(0, 1, 0x30 + (sum % 10));
                retenue = sum / 10;
                if (!lhsFinished) {
                        ++itLhs;
	        }
                if (!rhsFinished) {
                        ++itRhs;
                }
                lhsFinished = (itLhs == lhs.rend());
                rhsFinished = (itRhs == rhs.rend());
        }
        return result;
}

std::string workerAddNumbers()
{
        bool pending = true;
        std::string result = std::string("0");
        while (pending) {
                if (values.size()) {
                        std::string rhs = *(values.end() - 1);
                        values.erase(values.end() - 1);
                        std::string &&temp = addNumbers(result, rhs);
                        result = temp;
                } else {
                        pending = false;
                }
        }
        return result;
}

std::string multiplyNumbers(const std::string &lhs, const std::string &rhs)
{
        std::string result;
        auto itLhs = lhs.rbegin();
        auto itRhs = rhs.rbegin();
        unsigned char retenue = 0;
        bool lhsFinished = false;
        bool rhsFinished = false;
	uint64_t shift = 0;
	std::queue<std::string> tmpValues;
        while (!lhsFinished || !rhsFinished || retenue) {
                unsigned char &&lhsTmp = !lhsFinished ? (*itLhs - 0x30) : 0;
                unsigned char &&rhsTmp = !rhsFinished ? (*itRhs - 0x30) : 0;
                unsigned char &&mul = lhsTmp * rhsTmp;
                mul += retenue;
                result.insert(0, 1, 0x30 + (mul % 10));
                retenue = mul / 10;
                if (!lhsFinished) {
                        ++itLhs;
                }
                if (!rhsFinished) {
                        ++itRhs;
                }
                lhsFinished = (itLhs == lhs.rend());
                rhsFinished = (itRhs == rhs.rend());
        }
        return result;
}

std::string workerMultiplyNumbers()
{
        bool pending = true;
        std::string result = std::string("1");
        while (pending) {
                if (values.size()) {
	                std::string rhs = *(values.end() - 1);
	                values.erase(values.end() - 1);
                        std::string &&temp = multiplyNumbers(result, rhs);
                        result = temp;
                } else {
                        pending = false;
	        }
        }
        return result;
}

int main ()
{
	std::string result = workerMultiplyNumbers();
	std::cout << "The result is: " << result << std::endl;
	return 0;
}
