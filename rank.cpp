#include"rank.h"
#include<fstream>
void read(std::ifstream& is,Rank* pr,int n)
{
	for (int i = 0; i < n; i++)
	{

		is >> pr[i].num >> pr[i].score;
	}
}
void b_sort(Rank* pr, int n)
{
	for (int i = 0; i < n; i++)
	{
		Rank temp;
		for (int j = 0; j < n - i - 1; j++)
		{
			if (pr[j].score <= pr[j + 1].score)
			{
				temp = pr[j];
				pr[j] = pr[j + 1];
				pr[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		Rank temp;
		for (int j = 0; j < n - i - 1; j++)
		{
			if (pr[j].score == pr[j + 1].score)
			{
				if (pr[j].num >= pr[j + 1].num)
				{
					temp = pr[j];
					pr[j] = pr[j + 1];
					pr[j + 1] = temp;
				}
				
			}
		}
	}
}
void DisplayHi(Rank* pr, int n)
{
	int max = pr[0].score,maxNo=0;
	for (int i = 1; i < n; i++)
	{
		if (pr[i].score > max)
		{
			max = pr[i].score;
			maxNo = i;
		}
	}
	std::cout << "最高分：" << "Game No." << maxNo+1 << ' ' << pr[maxNo].score<<std::endl;
}
void DisplayRank(Rank* pr, int n)
{
	using std::cout;
	cout.setf(std::ios::left);
	cout << "名次\t分数\t编号\t\n";
	b_sort(pr, n);
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << "\t" << pr[i].score << "\t" << pr[i].num<<std::endl;
	}
}