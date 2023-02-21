#include "Snake.h"

string Snake::change_board(string board, int row_len) {
	for (auto iter = body.begin(); iter != body.end(); ++iter) {
		tuple<int, int> pos = iter->get_pos();
		board[(1 + 3 * get<0>(pos)) * row_len + (3 + 8 * get<1>(pos))] = '_';
		board[(2 + 3 * get<0>(pos)) * row_len + (2 + 8 * get<1>(pos))] = '|';
		board[(2 + 3 * get<0>(pos)) * row_len + (3 + 8 * get<1>(pos))] = '_';
		board[(2 + 3 * get<0>(pos)) * row_len + (4 + 8 * get<1>(pos))] = '|';
	}
	return board;
}

void Snake::move(int size, char dir) {
	change_dir(dir);

	for (auto iter = body.begin(); iter != body.end(); ++iter) {
		tuple<int, int> pos = iter->get_pos();
		if (turns.find(pos) != turns.end()) {
			iter->change_diri(get<0>(turns.find(pos)->second));
			iter->change_dirj(get<1>(turns.find(pos)->second));
			if (iter == body.end() - 1)
				turns.erase(pos);
		}
	}

	for (auto iter = body.begin(); iter != body.end(); ++iter) {
		iter->move();
		tuple<int, int> pos = iter->get_pos();
		if (get<0>(pos) >= size)
			iter->set_i(0);
		else if (get<0>(pos) < 0)
			iter->set_i(size - 1);
		else if (get<1>(pos) >= size)
			iter->set_j(0);
		else if (get<1>(pos) < 0)
			iter->set_j(size - 1);
	}
}

void Snake::change_dir(char dir) {
	if (dir == 'w' and body[0].get_diri() != 1) {
		body[0].change_dirj(0);
		body[0].change_diri(-1);
		turns.insert(pair<tuple<int, int>, tuple<int, int>>(body[0].get_pos(), body[0].get_dir()));
		//turns[body[0].get_pos()] = body[0].get_dir();
	}
	else if (dir == 's' and body[0].get_diri() != -1) {
		body[0].change_dirj(0);
		body[0].change_diri(1);
		turns.insert(pair<tuple<int, int>, tuple<int, int>>(body[0].get_pos(), body[0].get_dir()));
		//turns[body[0].get_pos()] = body[0].get_dir();
	}
	else if (dir == 'd' and body[0].get_dirj() != -1) {
		body[0].change_dirj(1);
		body[0].change_diri(0);
		turns.insert(pair<tuple<int, int>, tuple<int, int>>(body[0].get_pos(), body[0].get_dir()));
		//turns[body[0].get_pos()] = body[0].get_dir();
	}
	else if (dir == 'a' and body[0].get_dirj() != 1) {
		body[0].change_dirj(-1);
		body[0].change_diri(0);
		turns.insert(pair<tuple<int, int>, tuple<int, int>>(body[0].get_pos(), body[0].get_dir()));
		//turns[body[0].get_pos()] = body[0].get_dir();
	}
}

bool Snake::has(tuple<int, int> pot_food) {
	for (auto iter = body.begin(); iter != body.end(); ++iter) {
		if (iter->get_pos() == pot_food)
			return true;
	}
	return false;
}

void Snake::add_part() {
	Part last_segment = body[body.size() - 1];
	if (last_segment.get_diri() == 1)
		body.push_back(Part(last_segment.get_j(), last_segment.get_i() - 1, last_segment.get_dirj(), last_segment.get_diri()));
	else if (last_segment.get_diri() == -1)
		body.push_back(Part(last_segment.get_j(), last_segment.get_i() + 1, last_segment.get_dirj(), last_segment.get_diri()));
	else if (last_segment.get_dirj() == 1)
		body.push_back(Part(last_segment.get_j() - 1, last_segment.get_i(), last_segment.get_dirj(), last_segment.get_diri()));
	else if (last_segment.get_dirj() == -1)
		body.push_back(Part(last_segment.get_j() + 1, last_segment.get_i(), last_segment.get_dirj(), last_segment.get_diri()));
}