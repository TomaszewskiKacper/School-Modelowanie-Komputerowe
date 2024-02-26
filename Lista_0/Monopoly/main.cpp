#include <random>
#include <iostream>
#include <fstream>
#include <string>


int roll() {//trow 2 dices, [2;12]
	//return (rand() % 6 + 1) + (rand() % 6 + 1);
	return (rand() % 6 + 1);
}

void play(int rolls_n, std::string name) {//graj

	int rolls = rolls_n;
	int board[40] = { 0 };	//plansza
	int roll_count[12] = { 0 };
	int curr = 0;	//current position

	while (rolls) {
		board[curr]++;	//increment current position
		int n_roll = roll();
		curr += n_roll;	//move forward by the value of 2 dice
		roll_count[n_roll - 1]++;	//save roll for other plot

		if (curr >= 40)	//if end of board, go to the start
			curr -= 40;
		rolls--;
	}

	std::ofstream file("../Monopoly_graphing/" + name+".txt");
	if (file.is_open()) {
		for (int el : board)
			file << el * 100.0f / rolls_n << " ";	//pass board values into file
		file << "\n";
		for (int el : roll_count)
			file << el << " ";	//pass roll values into file
	}
	file.close();
}

void play_2(int rolls_n, std::string name) {//graj with jail

	int rolls = rolls_n;
	int board[40] = { 0 };	//plansza
	int roll_count[12] = { 0 };
	int curr = 0;	//current position

	while (rolls) {
		board[curr]++;	//increment current position
		int n_roll = roll();
		curr += n_roll;	//move forward by the value of 2 dice
		roll_count[n_roll - 1]++;	//save roll for other plot

		if (curr >= 40)	//if end of board, go to the start
			curr -= 40;
		if (curr == 29)
			curr = 9;
		rolls--;
	}

	std::ofstream file("../Monopoly_graphing/" + name + ".txt");
	if (file.is_open()) {
		for (int el : board)
			file << el*100.0f/rolls_n << " ";	//pass board values into file
		file << "\n";
		for (int el : roll_count)
			file << el << " ";	//pass roll values into file
	}
	file.close();
}

int main() {

	play(100, "monopol_100");
	play(1000000, "monopol_1000000");
	play_2(100, "monopol_jail_100");
	play_2(1000000, "monopol_jail_1000000");





	return 0;
}