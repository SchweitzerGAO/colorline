#include<iostream>
#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_
const int BOARDWIDTH = 9;
const int COLORS = 7;
const int movx[] = { 1,0,-1,0 };
const int movy[] = { 0,1,0,-1 };
class Chessboard
{
private:
	char cb[BOARDWIDTH][BOARDWIDTH];
	int score;
public:
	Chessboard();
	~Chessboard();
	void Initialize();
	bool isFull();
	bool valid(int[][BOARDWIDTH], int, int, int);
	bool bfs(int,int,int,int);
	int move(int, int, int, int);
	bool down();
	bool right();
	bool rightDiag();
	bool leftDiag();
	bool L1();
	bool L2();
	bool L3();
	bool L4();
	bool L();
	bool V1();
	bool V2();
	bool V3();
	bool V4();
	bool V5();
	bool V6();
	bool V7();
	bool V8();
	bool V9();
	bool V10();
	bool V11();
	bool V12();
	bool V();
	bool T1();
	bool T2();
	bool T3();
	bool T4();
	bool T();
	bool canRemove();
	void update();
	void displayBoard();
	void displayScore();
	void write(std::ofstream&,int);
};

#endif
