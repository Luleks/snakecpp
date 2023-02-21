#pragma once
#include "Part.h"

class Snake {
private:
	vector<Part> body;
	map<tuple<int, int>, tuple<int, int>> turns;
	int dirx;
	int diry;
	int x;
	int y;
	Part head;

public:
	Snake() {
		dirx = diry = x = y = 0;
	}
	Snake(int size) {
		body = {};
		turns = {};
		dirx = 1;
		diry = 0;
		x = rand() % size;
		y = rand() % size;
		head = Part(x, y, dirx, diry);
		body.push_back(head);
	}
	~Snake() {}
	string change_board(string board, int row_len);
	void move(int size, char dir);
	void change_dir(char dir);
	int snake_i() {
		return body[0].get_i();
	}
	int snake_j() {
		return body[0].get_j();
	}
	void add_part();
	bool has(tuple<int, int> pot_food);
};

