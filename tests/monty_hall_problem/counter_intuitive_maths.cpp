#include <iostream>
#include <experimental/random>

int main () {
	uint32_t prize_door;
	uint32_t selected_door;
	uint32_t removed_door;
	uint32_t final_door;
	uint32_t other_door;
	bool change_door;
	
	uint32_t change_lost = 0;
	uint32_t change_won = 0;
	uint32_t no_change_lost = 0;
	uint32_t no_change_won = 0;
	uint32_t attempts_nb = 0;

	for (uint32_t i = 0; i < 1000000000; ++i) {
		prize_door = std::experimental::randint(1, 3);
		selected_door = std::experimental::randint(1, 3);
		if (prize_door == selected_door) {
			if (selected_door == 1) {
				removed_door = std::experimental::randint(2, 3);
				if (removed_door == 2) {
					other_door = 3;
				} else {
					other_door = 2;
				}
			} else if (selected_door == 2) {
				if (std::experimental::randint(1, 2) == 1) {
					removed_door = 1;
					other_door = 3;
				} else {
					removed_door = 3;
					other_door = 1;
				}
			} else if (selected_door == 3) {
				removed_door = std::experimental::randint(1, 2);
				if (removed_door == 1) {
					other_door = 2;
				} else {
					other_door = 1;
				}
			}
		} else {
			if (selected_door == 1) {
				if (prize_door == 2) {
					removed_door = 3;
					other_door = 2;
				} else {
					removed_door = 2;
					other_door = 3;
				}
			} else if (selected_door == 2) {
				if (prize_door == 1) {
					removed_door = 3;
					other_door = 1;
				} else {
					removed_door = 1;
					other_door = 3;
				}
			} else if (selected_door == 3) {
				if (prize_door == 2) {
					removed_door = 1;
					other_door = 2;
				} else {
					removed_door = 2;
					other_door = 1;
				}
			}
		}

		change_door = (bool)std::experimental::randint(0, 1);
		if (change_door) {
			final_door = other_door;
		} else {
			final_door = selected_door;
		}
		//std::cout << "prize_door: " << prize_door << " selected_door: " << selected_door << " removed_door: " << removed_door << " other_door: " << other_door << " change_door: " << change_door << " final_door: " << final_door << std::endl;
		if (final_door == prize_door) {
			if (change_door) {
				++change_won;
			} else {
				++no_change_won;
			}
			//std::cout << "YOU WON!!!!" << std::endl;
		} else {
			if (change_door) {
				++change_lost;
			} else {
				++no_change_lost;
			}
			//std::cout << "You've lost, sucker..." << std::endl;
		}
		++attempts_nb;
		if (removed_door == prize_door) {
			std::cout << "ERROR: removed wrong door" << std::endl;
			std::cout << "prize_door: " << prize_door << " selected_door: " << selected_door << " removed_door: " << removed_door << " other_door: " << other_door << " change_door: " << change_door << " final_door: " << final_door << std::endl;
		}
		if (removed_door == final_door) {
			std::cout << "ERROR: selected wrong door" << std::endl;
			std::cout << "prize_door: " << prize_door << " selected_door: " << selected_door << " removed_door: " << removed_door << " other_door: " << other_door << " change_door: " << change_door << " final_door: " << final_door << std::endl;
		}		
	}
	std::cout << "TOTAL ATTEMPTS:     " << attempts_nb << std::endl;
	std::cout << "Number of door changes: " << change_lost + change_won << std::endl;
	std::cout << "Times won:              " << change_won << std::endl;
	std::cout << "Times lost:             " << change_lost << std::endl;
	std::cout << "Percentage of wins when changing door: " << (double(change_won) / double(change_lost + change_won)) * 100. << std::endl;
	std::cout << "Number of door keeps:   " << no_change_lost + no_change_won << std::endl;
	std::cout << "Times won:              " << no_change_won << std::endl;
	std::cout << "Times lost:             " << no_change_lost << std::endl;
	std::cout << "Percentage of wins when NOT changing door: " << (double(no_change_won) / double(no_change_lost + no_change_won)) * 100. << std::endl;
	return 0;
}