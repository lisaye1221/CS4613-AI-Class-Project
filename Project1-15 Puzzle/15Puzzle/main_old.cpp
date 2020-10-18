
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cmath>
#include <sstream>
using namespace std;

class Board {
	friend ostream& operator<<(ostream& os, const Board& rhs) {
		// prints out board in ixj(4x4) formatting
		for (size_t i = 0; i < rhs.data.size(); i++) {
			for (size_t j = 0; j < rhs.data.size(); j++) {
				cout << rhs.data[i][j] << " ";
			}
			cout << endl;
		}
		return os;
	}
public:
	Board(vector<vector<int>> data) : data(data) {}

	// check if another board is same as this board
	bool isSameBoard(const Board& other) const {
		// goes through whole board to check each tile
		for (size_t i = 0; i < other.data.size(); i++) {
			for (size_t j = 0; j < other.data.size(); j++) {
				if (data[i][j] != other.data[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	/*
	 returns position of target number in a board
	 pair.first = row number
	 pair.second = column number
 */
	pair<size_t, size_t> getPosition(int target) const {
		pair<size_t, size_t> result(data.size(), data.size());
		for (size_t i = 0; i < data.size(); i++) {
			for (size_t j = 0; j < data.size(); j++) {
				// check if match target
				if (data[i][j] == target) {
					// record position and return
					result.first = i;
					result.second = j;
					return result;
				}
			}
		}
		return result;
	}

	// calculates and return Manhattan distance 
	int getManhattanDistance(const Board& goal) const {
		int result = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				// ignores empty tile
				if (data[i][j] != 0) {
					// finds position of num in goal state
					// converts size_t to int because subtracting
					pair<int, int> goalPos = goal.getPosition(data[i][j]);
					// adds Manhttan distance of curr tile to total Manhattan distance
					result += abs(goalPos.first - i);
					result += abs(goalPos.second - j);
				}
			}
		}
		return result;
	}

private:
	vector<vector<int>> data;
};


// data structure to hold states for graph search
class TreeNode {

public:
	TreeNode(TreeNode* parent, TreeNode* left, TreeNode* right, vector<vector<int>> data) 
		:parent(parent), left(left), right(right){

		// sets up path cost, which is just the depth
		if (parent) {
			g = parent->g + 1;
		}
		else {
			g = 0;
		}
	}

	int getG() const { return g; }

private:
	TreeNode* parent;
	TreeNode* left;
	TreeNode* right;
	Board* board;

	int g; // path cost up to this node
};


// reads in input file and translate text to initial and goal boards
void readInput(ifstream& ifs, vector<vector<int>>& initial, vector<vector<int>>& goal);
// calculates sum of manhattan distance of all tiles from curr state to goal state 
//int calcManhattanDistance(const vector<vector<int>>& curr,const vector<vector<int>>& goal);

 /*
	 returns position of target number in a board
	 pair.first = row number
	 pair.second = column number
 */
//pair<size_t, size_t> getPosition(const vector<vector<int>>& board, int target);

// takes in two boards and check whether same board
//bool isSameBoard(const vector<vector<int>>& board1,const vector<vector<int>>& board2);

// prints out board, for debug
// void printBoard(const vector<vector<int>>& board);

// runs the A* search and produce an output file
void run(const Board& initial, const Board& goal) {
	// create output file stream
	// note that if same name of file exist, will overwrite
	ofstream output("output.txt");



	output << "my text here!" << endl;
	output << "second!" << endl;




	// closing an output stream creates the file
	output.close();
}



int main() {

	bool DEBUG = true;

	// vectors to hold data
	vector<vector<int>> initialData(4, vector<int>(4, 0));
	vector<vector<int>> goalData(4, vector<int>(4, 0));
	// opens file
	ifstream input;
	string filename = "sampleInput.txt";
	input.open(filename);
	// check if file is valid
	if (!input) {
		cout << "failed to open file" << endl;
		exit(1);
	}
	// fill vector from input
	readInput(input, initialData, goalData);
	// create Board object with data
	Board initialBoard(initialData);
	Board goalBoard(goalData);

	// debug print outs
	if (DEBUG) {
		cout << "----initial board----" << endl;
		cout << initialBoard << endl;
		cout << "----goal board----" << endl;
		cout << goalBoard << endl;
		cout << "Manhttan Distance: " << initialBoard.getManhattanDistance(goalBoard) << endl;
	}

	// run the search
	//run(initialBoard, goalBoard);

	// close filestream when finished
	input.close();
	
}

void readInput(ifstream& ifs, vector<vector<int>>& initial, vector<vector<int>>& goal) {
	
	string row;
	int num;
	// fills up initial board
	for (int i = 0; i < 4; i++) {
		getline(ifs, row);
		istringstream ss(row);
		size_t j = 0;
		while (ss >> num) {
			initial[i][j] = num;
			j++;
		}
	}
	// skips empty line
	getline(ifs, row);
	// fills up goal board
	for (int i = 0; i < 4; i++) {
		getline(ifs, row);
		istringstream ss(row);
		size_t j = 0;
		while (ss >> num) {
			goal[i][j] = num;
			j++;
		}
	}
}



//int calcManhattanDistance(const vector<vector<int>>& curr, const vector<vector<int>>& goal) {
//	int result = 0;
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			// ignores empty tile
//			if (curr[i][j] != 0) {
//				// finds position of num in goal state
//				// converts size_t to int because subtracting
//				pair<int, int> goalPos = getPosition(goal, curr[i][j]);
//				// adds Manhttan distance of curr tile to total Manhattan distance
//				result += abs(goalPos.first - i);
//				result += abs(goalPos.second - j);
//			}
//		}
//	}
//	return result;
//}



//pair<size_t, size_t> getPosition(const vector<vector<int>>& board, int target) {
//	pair<size_t, size_t> result(board.size(), board.size());
//	for (size_t i = 0; i < board.size(); i++) {
//		for (size_t j = 0; j < board.size(); j++) {
//			// check if match target
//			if (board[i][j] == target) {
//				// record position and return
//				result.first = i;
//				result.second = j;
//				return result;
//			}
//		}
//	}
//	return result;
//}

//bool isSameBoard(const vector<vector<int>>& board1, const vector<vector<int>>& board2) {
//	// goes through whole board to check each tile
//	for (size_t i = 0; i < board1.size(); i++) {
//		for (size_t j = 0; j < board1.size(); j++) {
//			if (board1[i][j] != board2[i][j]) {
//				return false;
//			}
//		}
//	}
//	return true;
//}

//void printBoard(const vector<vector<int>>& board) {
//	// prints out board in ixj(4x4) formatting
//	for (size_t i = 0; i < board.size(); i++) {
//		for (size_t j = 0; j < board.size(); j++) {
//			cout << board[i][j] << " ";
//		}
//		cout << endl;
//	}
//}
