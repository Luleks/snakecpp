#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
using namespace std;

class Part {
private:
	int j;
	int i;
	int dirj;
	int diri;
public:
	Part() {
		j = i = dirj = diri = 0;
	}
	Part(int j0, int i0, int dirj_start, int diri_start) {
		j = j0;
		i = i0;
		dirj = dirj_start;
		diri = diri_start;
	}
	~Part() {}

	void move() {
		j += dirj;
		i += diri;
	}

	void change_dirj(int new_dirj) {
		dirj = new_dirj;
	}

	void change_diri(int new_diri) {
		diri = new_diri;
	}

	void set_i(int new_i) {
		i = new_i;
	}

	void set_j(int new_j) {
		j = new_j;
	}

	int get_i() {
		return i;
	}

	int get_j() {
		return j;
	}

	int get_dirj() {
		return dirj;
	}

	int get_diri() {
		return diri;
	}

	tuple<int, int> get_pos() {
		return make_tuple(i, j);
	}

	tuple<int, int> get_dir() {
		return make_tuple(diri, dirj);
	}
};

