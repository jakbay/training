#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <cmath>

std::queue<uint64_t> triangleNbs;
std::queue<uint64_t> results;
bool found = false;
std::mutex sync;
std::mutex sync2;
#define DIVISORS 500

void triangleNumbersGiver(void)
{
	uint64_t step = 1;
	uint64_t triangleNb;
	while (!found) {
		triangleNb = 0;
		for (auto i = 1; i <= step; ++i) {
			triangleNb += i;
		}
		sync.lock();
		triangleNbs.push(triangleNb);
		sync.unlock();
		++step;
	}
}

void triangleNumbersEater(void) {
	uint64_t triangleNb = 0;
	uint64_t divisorsNb = 0;
	uint64_t ceiling;
	while (!found && divisorsNb <= DIVISORS) {
		divisorsNb = 0;
		sync.lock();
		if (!triangleNbs.size()) {
			sync.unlock();
			continue;
		}
		triangleNb = triangleNbs.front();
		triangleNbs.pop();
		sync.unlock();
		ceiling = std::sqrt(triangleNb);
		for (auto i = 1; i <= ceiling; ++i) {
			if (!(triangleNb % i)) {
				++divisorsNb;
			}
		}
		divisorsNb *= 2;
	}
	sync2.lock();
	if (divisorsNb > DIVISORS) {
		found = true;
		results.push(triangleNb);
	}
	sync2.unlock();
}

int main ()
{
	uint64_t result;
	std::thread giver(triangleNumbersGiver);
	std::thread eater1(triangleNumbersEater);
	std::thread eater2(triangleNumbersEater);
	std::thread eater3(triangleNumbersEater);
	std::thread eater4(triangleNumbersEater);
	std::thread eater5(triangleNumbersEater);
	std::thread eater6(triangleNumbersEater);
	std::thread eater7(triangleNumbersEater);
	giver.join();
	eater1.join();
	eater2.join();
	eater3.join();
	eater4.join();
	eater5.join();
	eater6.join();
	eater7.join();

	if (results.size()) {
		result = results.front();
		results.pop();
	}
	while (results.size()) {
		if (result > results.front()) {
			result = results.front();
		}
		results.pop();
	} 

	std::cout << "The result is: " << result << std::endl;
	return 0;
}
