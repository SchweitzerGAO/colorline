#include<iostream>
#ifndef _RANK_H_
#define _RANK_H_
struct Rank
{
	int num;
	int score;
};
void read(std::ifstream&, Rank*, int);
void b_sort(Rank*, int);
void DisplayHi(Rank*,int);
void DisplayRank(Rank*, int);

#endif
