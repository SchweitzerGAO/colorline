#include"chessboard.h"
#include<cstdlib>
#include<ctime>
#include<fstream>
Chessboard::Chessboard()
{
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			cb[i][j] ='0';
		}
	}
	score = 0;
}
Chessboard::~Chessboard()
{

}
void Chessboard::Initialize()
{
	int ct = 0;
	int x, y;
	char res;
	srand(time(0));
	while (ct < 7)
	{
		
		x = rand() % BOARDWIDTH;
		y = rand() % BOARDWIDTH;
		
		if (cb[x][y]!='0')
		{
			continue;
		}
		else
		{
			res = ((rand()%COLORS)+1)+'0';
			cb[x][y] = res;
			ct++;
		}
	}
	return;
}
void Chessboard::displayBoard()
{
	std::cout << "  0 1 2 3 4 5 6 7 8 \n";
	std::cout << "  - - - - - - - - - \n";
	for (int i = 0; i <BOARDWIDTH; i++)
	{
		std::cout << i << '|';
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			std::cout << cb[i][j] << ' ';
		}
		std::cout << std::endl << std::endl;
	}
	return;
}
void Chessboard::displayScore()
{
	std::cout << "×Ü·Ö:" << score << std::endl;
}
bool Chessboard::isFull()
{
	bool ret = true;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			if (cb[i][j] == '0')
			{
				ret = false;
				break;
			}
		}
	}

	return ret;
}
bool Chessboard::valid(int map[][BOARDWIDTH], int x, int y, int step)
{
	bool assist = false;
	if (x - 1 >= 0)
	{
		if (cb[x - 1][y] == '0' && map[x - 1][y] == 0)
		{
			map[x - 1][y] = step + 1;
			assist = true;
		}
	}
	if (x + 1 < BOARDWIDTH)
	{
		if (cb[x + 1][y] == '0' && map[x + 1][y] == 0)
		{
			map[x + 1][y] = step + 1;
			assist = true;
		}
	}
	if (y - 1 >= 0)
	{
		if (cb[x][y - 1] == '0' && map[x][y - 1] == 0)
		{
			map[x][y - 1] = step + 1;
			assist = true;
		}
	}
	if (y + 1 < BOARDWIDTH)
	{
		if (cb[x][y + 1] == '0' && map[x][y + 1] == 0)
		{
			map[x][y + 1] = step + 1;
			assist = true;
		}
	}
	return assist;
}
bool Chessboard::bfs(int stx,int sty,int edx,int edy)
{
	bool ret_val = true;
	int map[BOARDWIDTH][BOARDWIDTH];
	int step = 0;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			map[i][j] = 0;
		}
	}
	map[stx][sty] = -1;
	if (valid(map, stx, sty, step))
	{
		
		++step;
		while (map[edx][edy] == 0)
		{
			int inval = 0, equal = 0;
			for (int i = 0; i < BOARDWIDTH; i++)
			{
				
				for (int j = 0; j < BOARDWIDTH; j++)
				{
					if (map[i][j] == step)
					{
						++equal;
						if (!valid(map, i, j, step))
						{
							++inval;
							ret_val = false;
						}
						else
							continue;
					}
				}
			}
			if (equal == inval&&equal!=0&&inval!=0)
				break;
			else
			{
				++step;
			}
		}
		if (map[edx][edy] == 0)
		{
			ret_val = false;
		}
		else
		{
			ret_val = true;
		}
	}
	else
	{
		ret_val = false;
	}
	return ret_val;
}
int Chessboard::move(int stx, int sty, int edx, int edy)
{
	
	int ret_val;
	if (cb[edx][edy] == '0' && cb[stx][sty] != '0'&& stx >= 0 && stx < BOARDWIDTH &&sty >= 0 && sty < BOARDWIDTH &&edx >= 0 && edx < BOARDWIDTH &&edy >= 0 && edy < BOARDWIDTH)
	{
		bool b = bfs(stx, sty, edx, edy);
		if(b)
		{ 
			cb[edx][edy] = cb[stx][sty];
			cb[stx][sty] = '0';
			ret_val = 1;
		}
		else
		{
			ret_val = -4;
		}
		
	}
	else if (cb[edx][edy] != '0')
	{
		ret_val = 0;

	}
	else if (cb[stx][sty] == '0')
	{
		ret_val = -1;
	}
	else if (stx >= BOARDWIDTH || stx < 0 || sty >= BOARDWIDTH || sty < 0)
	{
		ret_val = -2;
	}
	else if (edx >= BOARDWIDTH || edx < 0 || edy >= BOARDWIDTH || edy < 0)
	{
		ret_val = -3;
	}
	

	return ret_val;
}
void Chessboard::update()
{
	int ct = 0;
	int x, y;
	char res;
	srand(time(0));
	while (ct < 3&&!isFull())
	{

		x = rand() % BOARDWIDTH;
		y = rand() % BOARDWIDTH;

		if (cb[x][y] != '0')
		{
			continue;
		}
		else
		{
			res = ((rand() % COLORS) + 1) + '0';
			cb[x][y] = res;
			ct++;
		}
	}
}
bool Chessboard::down()
{
	bool judge = false;
	
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			int k = 0;
			if (cb[i][j] == '0')
				continue;
			else
			{
				while ((cb[i + k][j] == cb[i][j])&&i+k< BOARDWIDTH&& cb[i + k][j]!='0')
				{
					same++;
					k++;
				}
				if (same >=5)
				{
					
					judge = true;
					int temp;
					for (temp = i; temp < i + same; temp++)
					{
						cb[temp][j] = '0';
					}
					score += (same  * 2);
				}
				
			}
			same = 0; //to avoid repeated accumulation after one check
		}
	}
	return judge;
}
bool Chessboard::right()
{
	bool judge = false;
	
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			int k = 0;
			if (cb[i][j] == '0')
				continue;
			else
			{
				while ((cb[i][j+k] == cb[i][j])&&j+k<BOARDWIDTH&& cb[i][j + k] !='0')
				{
					same++;
					k++;
				}
				if (same >= 5)
				{
					
					judge = true;
					int temp;
					for (temp = j; temp < j + same; temp++)
					{
						cb[i][temp] = '0';
					}
					score += (same  * 2);
					
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::rightDiag()
{
	bool judge = false;
	
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			int k = 0;
			if (cb[i][j] == '0')
				continue;
			else
			{
				while ((cb[i+k][j +k] == cb[i][j]) && j+k < BOARDWIDTH&&i+k<BOARDWIDTH&& cb[i +k][j + k]!='0')
				{
					same++;
					k++;
				}
				
				if (same >= 5)
				{
					
					judge = true;
					int temp1,temp2;
					for (temp1 = i,temp2=j;((temp1 < i + same)&&(temp2<j+same)); temp1++,temp2++)
					{
						cb[temp1][temp2] = '0';
					}
					score += (same  * 2);
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::leftDiag()
{
	bool judge = false;
	
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			int k = 0;
			if (cb[i][j] == '0')
				continue;
			else
			{
				while ((cb[i + k][j-k] == cb[i][j]) && j-k>=0 && i+k < BOARDWIDTH&& cb[i + k][j - k]!='0')
				{
					same++;
					k++;
				}
				if (same >= 5)
				{
					
					judge = true;
					int temp1, temp2;
					for (temp1 = i, temp2 = j; ((temp1 < i + same) && (temp2 > j - same)); temp1++, temp2--)
					{
						cb[temp1][temp2] = '0';
					}
					score += (same  * 2);
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::L1()               //deal with -| left cross
{
	bool judge = false;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			int k1 = 0;
			if (cb[i][j] == '0')
				continue;
			else
			{
				while (cb[i][j + k1] == cb[i][j] && j + k1 < BOARDWIDTH && cb[i][j + k1] != '0')
				{
					same++;
					k1++;
				}
				if (same >= 5)
				{
					int k2 = 0;
					while (cb[i + k2][j] == cb[i][j] && i + k2 < BOARDWIDTH && cb[i + k2][j] != '0')
					{
						same++;
						k2++;
					}
					if (same >= 10)
					{
						judge = true;
						int temp;
						for (temp = i; temp < i + k2; temp++)
						{
							cb[temp][j] = '0';
						}
						for (temp = j; temp < j + k1; temp++)
						{
							cb[i][temp] = '0';
						}
						score += ((same - 6) * 2 + 10);
					}
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::L2()               //deal with -| right cross
{
	bool judge = false;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			int k1 = 0;
			if (cb[i][j] == '0')
				continue;
			else
			{
				while (cb[i][j-k1] == cb[i][j] && j - k1 >= 0 && cb[i][j - k1] != '0')
				{
					same++;
					k1++;
				}
				if (same >= 5)
				{
					int k2 = 0;
					while (cb[i + k2][j] == cb[i][j] && i + k2 < BOARDWIDTH && cb[i + k2][j] != '0')
					{
						same++;
						k2++;
					}
					if (same >= 10)
					{
						judge = true;
						int temp;
						for (temp = i; temp < i + k2; temp++)
						{
							cb[temp][j] = '0';
						}
						for (temp = j; temp > j - k1; temp--)
						{
							cb[i][temp] = '0';
						}
						score += ((same - 6) * 2 + 10);
					}
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::L3()               //deal with |- left cross
{
	bool judge = false;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			int k1 = 0;
			if (cb[i][j] == '0')
				continue;
			else
			{
				while (cb[i][j + k1] == cb[i][j] && j + k1 < BOARDWIDTH && cb[i][j + k1] != '0')
				{
					same++;
					k1++;
				}
				if (same >= 5)
				{
					int k2 = 0;
					while (cb[i - k2][j] == cb[i][j] && i-k2 >= 0 && cb[i - k2][j] != '0')
					{
						same++;
						k2++;
					}
					if (same >= 10)
					{
						judge = true;
						int temp;
						for (temp = i; temp > i - k2; temp--)
						{
							cb[temp][j] = '0';
						}
						for (temp = j; temp > j + k1; temp++)
						{
							cb[i][temp] = '0';
						}
						score += ((same - 6) * 2 + 10);
					}
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::L4()               //deal with |- right cross
{
	bool judge = false;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			int k1 = 0;
			if (cb[i][j] == '0')
				continue;
			else
			{
				while (cb[i][j - k1] == cb[i][j] && j - k1 >= 0 && cb[i][j - k1] != '0')
				{
					same++;
					k1++;
				}
				if (same >= 5)
				{
					int k2 = 0;
					while (cb[i - k2][j] == cb[i][j] && i - k2>= 0 && cb[i - k2][j] != '0')
					{
						same++;
						k2++;
					}
					if (same >= 10)
					{
						judge = true;
						int temp;
						for (temp = i; temp > i - k2; temp--)
						{
							cb[temp][j] = '0';
						}
						for (temp = j; temp > j - k1; temp--)
						{
							cb[i][temp] = '0';
						}
						score += ((same - 6) * 2 + 10);
					}
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::L()
{
	bool ret = false;
	if (L1() || L2() || L3() || L4())
	{
		ret = true;
	}
	return ret;
}
bool Chessboard::V1()     //deal with -\ 
{
	bool judge = false;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			int k1 = 0;
			if (cb[i][j] == '0')
				continue;
			else
			{
				while (cb[i][j + k1] == cb[i][j] && j + k1 < BOARDWIDTH&&cb[i][j+k1]!='0')
				{
					same++;
					k1++;
				}
				if (same >= 5)
				{
					int k2 = 0;
					while (cb[i + k2][j + k2] == cb[i][j] && i + k2 < BOARDWIDTH && j + k2 < BOARDWIDTH
						&& cb[i + k2][j + k2] != '0')
					{
						same++;
						k2++;
					}
					if (same >= 10)
					{
						judge = true;
						
						int temp1, temp2;
						for (temp1 = j; temp1 < j + k1; temp1++)
						{
							cb[i][temp1] = '0';
						}
						for (temp1 = i, temp2 = j; (temp1 < i + k2 && temp2 < j + k2); temp1++, temp2++)
						{
							cb[temp1][temp2] = '0';
						}
						score += ((same - 6) * 2 + 10);
					}
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::V2()     //deal with -/ 
{
	bool judge = false;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			int k1 = 0;
			if (cb[i][j] == '0')
				continue;
			else
			{
				while (cb[i][j -k1] == cb[i][j] && j -k1 >= 0 && cb[i][j - k1] != '0')
				{
					same++;
					k1++;
				}
				if (same >= 5)
				{
					int k2 = 0;
					while (cb[i + k2][j - k2] == cb[i][j] && i + k2 < BOARDWIDTH && j - k2 >= 0
						&& cb[i + k2][j - k2] != '0')
					{
						same++;
						k2++;
					}
					if (same >= 10)
					{
						judge = true;

						int temp1, temp2;
						for (temp1 = j; temp1 > j - k1; temp1--)
						{
							cb[i][temp1] = '0';
						}
						for (temp1 = i, temp2 = j; (temp1 < i + k2 && temp2 > j - k2); temp1++, temp2--)
						{
							cb[temp1][temp2] = '0';
						}
						score += ((same - 6) * 2 + 10);
					}
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::V3()     //deal with /- 
{
	bool judge = false;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			int k1 = 0;
			if (cb[i][j] == '0')
				continue;
			else
			{
				while (cb[i][j + k1] == cb[i][j] && j + k1 < BOARDWIDTH && cb[i][j + k1] != '0')
				{
					same++;
					k1++;
				}
				if (same >= 5)
				{
					int k2 = 0;
					while (cb[i - k2][j + k2] == cb[i][j] && i - k2 >= 0 && j + k2 < BOARDWIDTH
						&& cb[i - k2][j + k2] != '0')
					{
						same++;
						k2++;
					}
					if (same >= 10)
					{
						judge = true;

						int temp1, temp2;
						for (temp1 = j; temp1 < j + k1; temp1++)
						{
							cb[i][temp1] = '0';
						}
						for (temp1 = i, temp2 = j; (temp1 > i - k2 && temp2 < j + k2); temp1--, temp2++)
						{
							cb[temp1][temp2] = '0';
						}
						score += ((same - 6) * 2 + 10);
					}
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::V4()     //deal with \- 
{
	bool judge = false;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			int k1 = 0;
			if (cb[i][j] == '0')
				continue;
			else
			{
				while (cb[i][j - k1] == cb[i][j] && j - k1 >= 0 && cb[i][j + k1] != '0')
				{
					same++;
					k1++;
				}
				if (same >= 5)
				{
					int k2 = 0;
					while (cb[i - k2][j - k2] == cb[i][j] && i - k2 >= 0 && j - k2 >= 0
						&& cb[i - k2][j - k2] != '0')
					{
						same++;
						k2++;
					}
					if (same >= 10)
					{
						judge = true;

						int temp1, temp2;
						for (temp1 = j; temp1 > j - k1; temp1--)
						{
							cb[i][temp1] = '0';
						}
						for (temp1 = i, temp2 = j; (temp1 > i - k2 && temp2 > j - k2); temp1--, temp2--)
						{
							cb[temp1][temp2] = '0';
						}
						score += ((same - 6) * 2 + 10);
					}
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::V5() //deal with |\ 
{
	bool judge = false;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			int k1 = 0;
			if (cb[i][j] == '0')
				continue;
			else
			{
				while (cb[i+k1][j] == cb[i][j] && i+k1 <BOARDWIDTH && cb[i+k1][j] != '0')
				{
					same++;
					k1++;
				}
				if (same >= 5)
				{
					int k2 = 0;
					while (cb[i + k2][j + k2] == cb[i][j] && i + k2 < BOARDWIDTH && j + k2 <BOARDWIDTH
						&& cb[i + k2][j + k2] != '0')
					{
						same++;
						k2++;
					}
					if (same >= 10)
					{
						judge = true;

						int temp1, temp2;
						for (temp1 = i; temp1 < i+k1; temp1++)
						{
							cb[temp1][j] = '0';
						}
						for (temp1 = i, temp2 = j; (temp1 < i + k2 && temp2 < j + k2); temp1++, temp2++)
						{
							cb[temp1][temp2] = '0';
						}
						score += ((same - 6) * 2 + 10);
					}
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::V6() //deal with /| 
{
	bool judge = false;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			int k1 = 0;
			if (cb[i][j] == '0')
				continue;
			else
			{
				while (cb[i + k1][j] == cb[i][j] && i + k1 < BOARDWIDTH && cb[i + k1][j] != '0')
				{
					same++;
					k1++;
				}
				if (same >= 5)
				{
					int k2 = 0;
					while (cb[i + k2][j - k2] == cb[i][j] && i + k2 < BOARDWIDTH && j - k2 >=0
						&& cb[i + k2][j - k2] != '0')
					{
						same++;
						k2++;
					}
					if (same >= 10)
					{
						judge = true;

						int temp1, temp2;
						for (temp1 = i; temp1 < i + k1; temp1++)
						{
							cb[temp1][j] = '0';
						}
						for (temp1 = i, temp2 = j; (temp1 < i + k2 && temp2 > j - k2); temp1++, temp2--)
						{
							cb[temp1][temp2] = '0';
						}
						score += ((same - 6) * 2 + 10);
					}
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::V7() //deal with |/
{
	bool judge = false;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			int k1 = 0;
			if (cb[i][j] == '0')
				continue;
			else
			{
				while (cb[i - k1][j] == cb[i][j] && i - k1 >=0 && cb[i - k1][j] != '0')
				{
					same++;
					k1++;
				}
				if (same >= 5)
				{
					int k2 = 0;
					while (cb[i - k2][j + k2] == cb[i][j] && i - k2 >=0 && j + k2 < BOARDWIDTH
						&& cb[i - k2][j + k2] != '0')
					{
						same++;
						k2++;
					}
					if (same >= 10)
					{
						judge = true;

						int temp1, temp2;
						for (temp1 = i; temp1 > i - k1; temp1--)
						{
							cb[temp1][j] = '0';
						}
						for (temp1 = i, temp2 = j; (temp1 > i - k2 && temp2 < j + k2); temp1--, temp2++)
						{
							cb[temp1][temp2] = '0';
						}
						score += ((same - 6) * 2 + 10);
					}
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::V8() //deal with \|
{
	bool judge = false;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			int k1 = 0;
			if (cb[i][j] == '0')
				continue;
			else
			{
				while (cb[i - k1][j] == cb[i][j] && i - k1 >= 0 && cb[i - k1][j] != '0')
				{
					same++;
					k1++;
				}
				if (same >= 5)
				{
					int k2 = 0;
					while (cb[i - k2][j - k2] == cb[i][j] && i - k2 >= 0 && j - k2 >=0
						&& cb[i - k2][j - k2] != '0')
					{
						same++;
						k2++;
					}
					if (same >= 10)
					{
						judge = true;

						int temp1, temp2;
						for (temp1 = i; temp1 > i - k1; temp1--)
						{
							cb[temp1][j] = '0';
						}
						for (temp1 = i, temp2 = j; (temp1 > i - k2 && temp2 > j - k2); temp1--, temp2--)
						{
							cb[temp1][temp2] = '0';
						}
						score += ((same - 6) * 2 + 10);
					}
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::V9()     //deal with \/, only one situation
{
	bool judge = false;
	int i = 4, j = 4;     // the middle of the board
	int same = 0;
	int temp1, temp2;
	for (temp1 = i, temp2 = j; (temp1 >= 0 && temp2 >= 0); temp1--, temp2--)
	{
		if (cb[temp1][temp2] != cb[i][j]||cb[temp1][temp2]=='0')
			break;
		else
			same++;
	}
	for (temp1 = i, temp2 = j; (temp1 >= 0 && temp2 < BOARDWIDTH); temp1--, temp2++)
	{
		if (cb[temp1][temp2] != cb[i][j])
			break;
		else
			same++;
	}
	if (same == 10) //only 1 situation! 
	{
		judge = true;
		for (temp1 = i, temp2 = j; (temp1 >= 0 && temp2 >= 0); temp1--, temp2--)
		{
			cb[temp1][temp2] = '0';
		}
		for (temp1 = i, temp2 = j; (temp1 >= 0 && temp2 < BOARDWIDTH); temp1--, temp2++)
		{
			cb[temp1][temp2] = '0';
		}
		score += 18;
	}
	return judge;
}
bool Chessboard::V10()     //deal with /\, only one situation
{
	bool judge = false;
	int i = 4, j = 4;     // the middle of the board
	int same = 0;
	int temp1, temp2;
	for (temp1 = i, temp2 = j; (temp1 < BOARDWIDTH && temp2 >= 0); temp1++, temp2--)
	{
		if (cb[temp1][temp2] != cb[i][j] || cb[temp1][temp2] == '0')
			break;
		else
			same++;
	}
	for (temp1 = i, temp2 = j; (temp1 < BOARDWIDTH && temp2 < BOARDWIDTH); temp1++, temp2++)
	{
		if (cb[temp1][temp2] != cb[i][j])
			break;
		else
			same++;
	}
	if (same == 10)//only 1 situation! 
	{
		judge = true;
		for (temp1 = i, temp2 = j; (temp1 < BOARDWIDTH && temp2 >= 0); temp1++, temp2--)
		{
			cb[temp1][temp2] = '0';
		}
		for (temp1 = i, temp2 = j; (temp1 < BOARDWIDTH && temp2 < BOARDWIDTH); temp1++, temp2++)
		{
			cb[temp1][temp2] = '0';
		}
		score += 18;
	}
	return judge;
}
bool Chessboard::V11()     //deal with >, only one situation
{
	bool judge = false;
	int i = 4, j = 4;     // the middle of the board
	int same = 0;
	int temp1, temp2;
	for (temp1 = i, temp2 = j; (temp1 >= 0 && temp2 >= 0); temp1--, temp2--)
	{
		if (cb[temp1][temp2] != cb[i][j] || cb[temp1][temp2] == '0')
			break;
		else
			same++;
	}
	for (temp1 = i, temp2 = j; (temp1 < BOARDWIDTH && temp2 >= 0); temp1--, temp2++)
	{
		if (cb[temp1][temp2] != cb[i][j])
			break;
		else
			same++;
	}
	if (same == 10)  //only 1 situation! 
	{
		judge = true;
		for (temp1 = i, temp2 = j; (temp1 >= 0 && temp2 >= 0); temp1--, temp2--)
		{
			cb[temp1][temp2] = '0';
		}
		for (temp1 = i, temp2 = j; (temp1 < BOARDWIDTH && temp2 >= 0); temp1++, temp2--)
		{
			cb[temp1][temp2] = '0';
		}
		score += 18;
	}
	return judge;
}
bool Chessboard::V12()     //deal with <, only one situation
{
	bool judge = false;
	int i = 4, j = 4;     // the middle of the board
	int same = 0;
	int temp1, temp2;
	for (temp1 = i, temp2 = j; (temp1 >= 0 && temp2 < BOARDWIDTH); temp1--, temp2++)
	{
		if (cb[temp1][temp2] != cb[i][j] || cb[temp1][temp2] == '0')
			break;
		else
			same++;
	}
	for (temp1 = i, temp2 = j; (temp1 < BOARDWIDTH && temp2 < BOARDWIDTH); temp1++, temp2++)
	{
		if (cb[temp1][temp2] != cb[i][j])
			break;
		else
			same++;
	}
	if (same == 10)  //only 1 situation! 
	{
		judge = true;
		for (temp1 = i, temp2 = j; (temp1 >= 0 && temp2 < BOARDWIDTH); temp1--, temp2++)
		{
			cb[temp1][temp2] = '0';
		}
		for (temp1 = i, temp2 = j; (temp1 < BOARDWIDTH && temp2 < BOARDWIDTH); temp1++, temp2++)
		{
			cb[temp1][temp2] = '0';
		}
		score += 18;
	}
	return judge;
}
bool Chessboard::V()
{
	bool ret = false;
	if (V1() || V2() || V3() || V4()
		|| V5() || V6() || V7() || V8()
		|| V9() || V10() || V11() || V12())
	{
		ret = true;
	}
	return ret;
}
bool Chessboard::T1()   //deal with T
{
	bool judge = false;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			if (cb[i][j] == '0')
				continue;
			else
			{
				int k1 = 0;
				while (cb[i + k1][j] == cb[i][j] && i + k1 < BOARDWIDTH && cb[i + k1][j] != '0')
				{
					same++;
					k1++;
				}
				if (same >= 5)
				{
					int k2 = 0;
					while (cb[i][j - k2] == cb[i][j] && j - k2 >= 0 && cb[i][j-k2]!='0')
					{
						same++;
						k2++;
					}
					if (same >= 7)
					{
						int k3 = 0;
						while (cb[i][j + k3] == cb[i][j] && j + k3 < BOARDWIDTH && cb[i][j + k3] != '0')
						{
							same++;
							k3++;
						}
						if (same >= 11)
						{
							judge = true;
							for (int temp = i; temp < i + k1; temp++)
							{
								cb[temp][j] = '0';
							}
							for (int temp = j; temp > j - k2; temp--)
							{
								cb[i][temp] = '0';
							}
							for (int temp = j; temp < j + k3; temp++)
							{
								cb[i][temp] = '0';
							}
							score += ((same - 7) * 2 + 10);
						}
					}
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::T2()   //deal with reserved T
{
	bool judge = false;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			if (cb[i][j] == '0')
				continue;
			else
			{
				int k1 = 0;
				while (cb[i - k1][j] == cb[i][j] && i - k1 >= 0 && cb[i - k1][j] != '0')
				{
					same++;
					k1++;
				}
				if (same >= 5)
				{
					int k2 = 0;
					while (cb[i][j - k2] == cb[i][j] && j - k2 >= 0 && cb[i][j - k2] != '0')
					{
						same++;
						k2++;
					}
					if (same >= 7)
					{
						int k3 = 0;
						while (cb[i][j + k3] == cb[i][j] && j + k3 < BOARDWIDTH && cb[i][j + k3] != '0')
						{
							same++;
							k3++;
						}
						if (same >= 11)
						{
							judge = true;
							for (int temp = i; temp > i - k1; temp--)
							{
								cb[temp][j] = '0';
							}
							for (int temp = j; temp > j - k2; temp--)
							{
								cb[i][temp] = '0';
							}
							for (int temp = j; temp < j + k3; temp++)
							{
								cb[i][temp] = '0';
							}
							score += ((same - 7) * 2 + 10);
						}
					}
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::T3()   //deal with T rotated 90 anticlockwise
{
	bool judge = false;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			if (cb[i][j] == '0')
				continue;
			else
			{
				int k1 = 0;
				while (cb[i][j+k1] == cb[i][j] && j + k1 < BOARDWIDTH && cb[i][j+k1] != '0')
				{
					same++;
					k1++;
				}
				if (same >= 5)
				{
					int k2 = 0;
					while (cb[i-k2][j] == cb[i][j] && i - k2 >= 0 && cb[i-k2][j] != '0')
					{
						same++;
						k2++;
					}
					if (same >= 7)
					{
						int k3 = 0;
						while (cb[i+k3][j] == cb[i][j] && i + k3 < BOARDWIDTH && cb[i+k3][j] != '0')
						{
							same++;
							k3++;
						}
						if (same >= 11)
						{
							judge = true;
							for (int temp = j; temp < j + k1; temp++)
							{
								cb[i][temp] = '0';
							}
							for (int temp = i; temp > i - k2; temp--)
							{
								cb[temp][j] = '0';
							}
							for (int temp = i; temp < i + k3; temp++)
							{
								cb[temp][j] = '0';
							}
							score += ((same - 7) * 2 + 10);
						}
					}
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::T4()   //deal with T rotated 90 clockwise
{
	bool judge = false;
	for (int i = 0; i < BOARDWIDTH; i++)
	{
		int same = 0;
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			if (cb[i][j] == '0')
				continue;
			else
			{
				int k1 = 0;
				while (cb[i][j - k1] == cb[i][j] && j - k1 >=0 && cb[i][j - k1] != '0')
				{
					same++;
					k1++;
				}
				if (same >= 5)
				{
					int k2 = 0;
					while (cb[i - k2][j] == cb[i][j] && i - k2 >= 0 && cb[i - k2][j] != '0')
					{
						same++;
						k2++;
					}
					if (same >= 7)
					{
						int k3 = 0;
						while (cb[i + k3][j] == cb[i][j] && i + k3 < BOARDWIDTH && cb[i + k3][j] != '0')
						{
							same++;
							k3++;
						}
						if (same >= 11)
						{
							judge = true;
							for (int temp = j; temp > j - k1; temp--)
							{
								cb[i][temp] = '0';
							}
							for (int temp = i; temp > i - k2; temp--)
							{
								cb[temp][j] = '0';
							}
							for (int temp = i; temp < i + k3; temp++)
							{
								cb[temp][j] = '0';
							}
							score += ((same - 7) * 2 + 10);
						}
					}
				}
			}
			same = 0;
		}
	}
	return judge;
}
bool Chessboard::T()
{
	bool ret=false;
	if (T1() || T2() || T3() || T4())
	{
		ret = true;
	}
	return ret;
}
bool Chessboard::canRemove()
{
	bool ret = false;
	if (L() || V() || T())
	{
		ret = true;
	}
	else if (down() || right() || rightDiag() || leftDiag())
	{
		ret = true;
	}
	return ret;
}
void Chessboard::write(std::ofstream& os, int num)
{
	os << num << " "<< score << std::endl;
}
