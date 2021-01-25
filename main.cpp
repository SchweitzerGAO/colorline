#include"chessboard.h"
#include"rank.h"
#include<cstdlib>
#include<fstream>
using namespace std;
void DisplayMenu();
void RunGame(Chessboard& game);
void update_num(ifstream& is, int& temp);
void in_num(ofstream& os, const int temp);
int main()
{
	DisplayMenu();
	Chessboard game;
	int temp;
	char option;
	ifstream is;
	ofstream os;
	cin >> option;
	switch (option)
	{
	case 'a':
	{
		is.open("num.TXT", ios::in);
		update_num(is, temp);
		os.open("num.TXT", ios::out);
		in_num(os, temp);
		ofstream fout;
		fout.open("scores.txt", ios::out | ios::app);
		cout << "Game No: " << temp << endl;
		RunGame(game);
		game.write(fout, temp);
		fout.close();
		is.close();
		os.close();
		break;
	}
	case 'b':
	{
		is.open("num.TXT", ios::in);
		is >> temp;
		is.close();
		if (temp == 0)
		{
			is.open("num.TXT", ios::in);
			update_num(is, temp);
			os.open("num.TXT", ios::out);
			in_num(os, temp);
			cout << "还没有进行过游戏，来一局吧！\n";
			ofstream fout;
			fout.open("scores.txt", ios::out | ios::app);
			cout << "Game No: " << temp<< endl;
			RunGame(game);
			game.write(fout, temp);
			fout.close();
			is.close();
			os.close();
		}
		else
		{
			ifstream ifs;
			ifs.open("scores.txt", ios::in);
			Rank* pr = new Rank[temp];
			read(ifs, pr, temp);
			DisplayHi(pr, temp);
			ifs.close();
			delete[]pr;
		}
		break;
	}
	case 'c':
	{
		is.open("num.TXT", ios::in);
		is >> temp;
		is.close();
		if (temp == 0)
		{
			is.open("num.TXT", ios::in);
			update_num(is, temp);
			os.open("num.TXT", ios::out);
			in_num(os, temp);
			cout << "还没有进行过游戏，来一局吧！\n";
			ofstream fout;
			fout.open("scores.txt", ios::out | ios::app);
			cout << "Game No: " << temp<< endl;
			RunGame(game);
			game.write(fout, temp);
			fout.close();
		}
		else
		{
			ifstream ifs;
			ifs.open("scores.txt", ios::in);
			Rank* pr = new Rank[temp];
			read(ifs, pr, temp);
			DisplayRank(pr, temp);
			ifs.close();
			delete[]pr;
		}
		break;
	}
	default:
	{
		cout << "无效选项！\n";
		break;
	}
	}
	system("pause");
	return 0;
}
	
	

void DisplayMenu()
{
	cout << "欢迎来到“五子连珠”\n";
	cout << "请选择一个操作：\n";
	cout << "a) 开始游戏\n" << "b) 查看最高分\n" << "c) 查看排行榜\n>>>";
}
void RunGame(Chessboard& game)
{
	game.Initialize();
	game.displayBoard();
	game.displayScore();
	while (!game.isFull())
	{
		int stx, sty, edx, edy, n;
		cout << "请输入起点坐标：（输入q以退出,不要点窗口的退出键！）\n>>>";
		if (!(cin >> stx))
		{
			cout << "游戏结束\n";
			game.displayScore();
			return;
		}
		else
		{
			cin >> sty;
			cout << "请输入终点坐标：\n>>>";
			cin >> edx >> edy;
		}
		n = game.move(stx, sty, edx, edy);
		while (n != 1)
		{
			if (n == 0)
			{
				cout << "终点已被占用，请重新选择：\n>>>";
				cin >> edx >> edy;
				n = game.move(stx, sty, edx, edy);
			}
			else if (n == -1)
			{
				cout << "起点位置为空，请重新选择：\n>>>";
				cin >> stx >> sty;
				n = game.move(stx, sty, edx, edy);
			}
			else if (n == -2)
			{
				cout << "无效起点坐标！请重新输入起点坐标：\n>>>";
				cin >> stx >> sty;
				n = game.move(stx, sty, edx, edy);
			}
			else if (n == -3)
			{
				cout << "无效终点坐标！请重新输入终点坐标：\n>>>";
				cin >> edx >> edy;
				n = game.move(stx, sty, edx, edy);
			}
			else if (n == -4)
			{
				cout << "无有效路径！请重新输入起点、终点坐标：\n>>>";
				cout << "请输入起点坐标：\n>>>";
				cin >> stx >> sty;
				cout << "请输入终点坐标：\n>>>";
				cin >> edx >> edy;
				n = game.move(stx, sty, edx, edy);
			}
		}
		if (!(game.canRemove()))
		{
			game.update();
			if (game.canRemove())//judge again after update
			{
				cout << "幸运！随机生成助您得分！\n";// if can be removed after random update
			}
		}
		system("cls");// clear previous output to maintain one chessboard
		game.displayBoard();
		game.displayScore();
	}
	cout << "棋盘已满，游戏结束。\n";
	game.displayScore();
}
void update_num(ifstream& is,int& temp)
{
	is >> temp;
	temp++;
	
}
void in_num(ofstream& os, const int temp)
{
	os << temp;
}