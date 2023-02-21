#include "Board.h"
#include <thread>
#include <chrono>
#include <atomic>
using namespace std;
	
void handle_input(atomic<char>& buf) {
	char buffer;
	while (buf.load()) {
		cin >> buffer;
		buf.store(buffer);
	}
}

int main() {
	srand(time(0));
	Board* b = new Board(10);
	atomic<char> buf(' ');
	thread t(handle_input, ref(buf));
	bool run = true;
	char dir = ' ';
	while (run) {
		char dir = buf.load();
		if (dir == 'x' or dir == 'X')
			run = false;

		b->update_board(dir);
		cout << *b;
		this_thread::sleep_for(chrono::milliseconds(500));
		system("cls");

	}
	cout << "ende";

	delete b;
	return 0;
}