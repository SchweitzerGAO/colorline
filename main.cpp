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
			cout << "��û�н��й���Ϸ����һ�ְɣ�\n";
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
			cout << "��û�н��й���Ϸ����һ�ְɣ�\n";
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
		cout << "��Чѡ�\n";
		break;
	}
	}
	system("pause");
	return 0;
}
	
	

void DisplayMenu()
{
	cout << "��ӭ�������������顱\n";
	cout << "��ѡ��һ��������\n";
	cout << "a) ��ʼ��Ϸ\n" << "b) �鿴��߷�\n" << "c) �鿴���а�\n>>>";
}
void RunGame(Chessboard& game)
{
	game.Initialize();
	game.displayBoard();
	game.displayScore();
	while (!game.isFull())
	{
		int stx, sty, edx, edy, n;
		cout << "������������꣺������q���˳�,��Ҫ�㴰�ڵ��˳�������\n>>>";
		if (!(cin >> stx))
		{
			cout << "��Ϸ����\n";
			game.displayScore();
			return;
		}
		else
		{
			cin >> sty;
			cout << "�������յ����꣺\n>>>";
			cin >> edx >> edy;
		}
		n = game.move(stx, sty, edx, edy);
		while (n != 1)
		{
			if (n == 0)
			{
				cout << "�յ��ѱ�ռ�ã�������ѡ��\n>>>";
				cin >> edx >> edy;
				n = game.move(stx, sty, edx, edy);
			}
			else if (n == -1)
			{
				cout << "���λ��Ϊ�գ�������ѡ��\n>>>";
				cin >> stx >> sty;
				n = game.move(stx, sty, edx, edy);
			}
			else if (n == -2)
			{
				cout << "��Ч������꣡����������������꣺\n>>>";
				cin >> stx >> sty;
				n = game.move(stx, sty, edx, edy);
			}
			else if (n == -3)
			{
				cout << "��Ч�յ����꣡�����������յ����꣺\n>>>";
				cin >> edx >> edy;
				n = game.move(stx, sty, edx, edy);
			}
			else if (n == -4)
			{
				cout << "����Ч·����������������㡢�յ����꣺\n>>>";
				cout << "������������꣺\n>>>";
				cin >> stx >> sty;
				cout << "�������յ����꣺\n>>>";
				cin >> edx >> edy;
				n = game.move(stx, sty, edx, edy);
			}
		}
		if (!(game.canRemove()))
		{
			game.update();
			if (game.canRemove())//judge again after update
			{
				cout << "���ˣ�������������÷֣�\n";// if can be removed after random update
			}
		}
		system("cls");// clear previous output to maintain one chessboard
		game.displayBoard();
		game.displayScore();
	}
	cout << "������������Ϸ������\n";
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