#pragma once
#include <fstream>
#include <strstream>
#include "Snake.h"

class Board {
private:
	Snake snake;
	int size;
	string board;
	string original_board;
	void create_board(int size);
	Part food;
	int one_field;
	int row_len;
	int score;

public:
	Board(int board_size) {
		size = board_size;
		snake = Snake(size);
		one_field = 8;
		row_len = one_field * size + 2;
		score = 0;
		board = "";
		food = Part(rand() % size, rand() % size, 0, 0);
		create_board(size);
		original_board = board;
		update_board(' ');
	}
	~Board() {}
	
	void update_board(char dir);
	void regenerate_food();

	friend ostream& operator<<(ostream& out, const Board& board);
};

void Board::create_board(int size) {
	for (int i = 0; i < size; i++) {
		board += " _______";
	}
	board += "\n";
	for (int j = 0; j < size; j++) {
		for (int j = 0; j < 2; j++) {
			for (int i = 0; i < size; i++) {
				board += "|       ";
			}
			board += "|\n";
		}
		for (int i = 0; i < size; i++) {
			board += "|_______";
		}
		board += "|\n";
	}
}

void Board::update_board(char dir) {
	snake.move(size, dir);

	if (snake.snake_i() == food.get_i() and snake.snake_j() == food.get_j()) {
		score += 1;
		regenerate_food();
		snake.add_part();
	}

	board = original_board;
	board = snake.change_board(board, row_len);

	board[(1 + 3 * food.get_i()) * row_len + (3 + 8 * food.get_j())] = '_';
	board[(2 + 3 * food.get_i()) * row_len + (2 + 8 * food.get_j())] = '|';
	board[(2 + 3 * food.get_i()) * row_len + (3 + 8 * food.get_j())] = '_';
	board[(2 + 3 * food.get_i()) * row_len + (4 + 8 * food.get_j())] = '|';
}

void Board::regenerate_food() {
	int i = rand() % size;
	int j = rand() % size;
	if (snake.has(make_tuple(i, j))) {
		regenerate_food();
		return;
	}
	food.set_i(i);
	food.set_j(j);
}

ostream& operator<<(ostream& out, const Board& board) {
	out << board.board << endl;
	out << "W/A/S/D" << endl << "Score: " << board.score << endl;
	return out;
}