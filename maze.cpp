#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

/*
0 : ��
1: ��
2: ������
3: ������
4: ��ź
5: �Ŀ�������
6: ���б� ������
7: ����������
8: ��Ȧ
*/

struct _tagPoint
{
	int x;
	int y;
};

// typedef : Ÿ���� �������ϴ� ����̴�.
typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;

typedef struct _tagPlayer
{
	_tagPoint tPos;
	bool bWallPush;
	bool bPushOnOff;
	bool bTransparency;
	int iBombPower;
}PLAYER, *PPLAYER;

void SetMaze(char Maze[21][21], PPLAYER pPlayer, PPOINT pStartPos, PPOINT pEndPos)
{
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	pPlayer->tPos = *pStartPos;


	strcpy_s(Maze[0],   "21100000000000000000");
	strcpy_s(Maze[1],   "00111111111000000000");
	strcpy_s(Maze[2],   "00100100001111111100");
	strcpy_s(Maze[3],   "00100100000000000100");
	strcpy_s(Maze[4],   "01100100000000000100");
	strcpy_s(Maze[5],   "00000111110000000100");
	strcpy_s(Maze[6],   "00000010000100111111");
	strcpy_s(Maze[7],   "00000011111100100000");
	strcpy_s(Maze[8],   "00000000000100100000");
	strcpy_s(Maze[9],   "00000000000000100000");
	strcpy_s(Maze[10], "00000111111111100000");
	strcpy_s(Maze[11], "00000100000000000000");
	strcpy_s(Maze[12], "00011111111000111110");
	strcpy_s(Maze[13], "00000000001000100010");
	strcpy_s(Maze[14], "00000000001111100010");
	strcpy_s(Maze[15], "00001111111000000000");
	strcpy_s(Maze[16], "00000000001000000000");
	strcpy_s(Maze[17], "00000000001111111100");
	strcpy_s(Maze[18], "00000000001000000100");
	strcpy_s(Maze[19], "00000000001000000113");

}

void Output(char Maze[21][21], PPLAYER pPlayer)
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{

			if (Maze[i][j] == '4')
				cout << "��";

			else if (pPlayer->tPos.x == j && pPlayer->tPos.y == i)
				cout << "��";

			else if (Maze[i][j] == '0')
				cout << "��";
			else if (Maze[i][j] == '1')
				cout << "  ";
			else if (Maze[i][j] == '2')
				cout << "��";
			else if (Maze[i][j] == '3')
				cout << "��";

			else if (Maze[i][j] == '5')
				cout << "��";
			else if (Maze[i][j] == '6')
				cout << "��";
			else if (Maze[i][j] == '7')
				cout << "��";
			
		}

		cout << "\n";
	}
	cout << endl;
	cout << endl;
	cout << "��ź�Ŀ� :  " << pPlayer->iBombPower << endl;
	cout << "����� : ";
	if (pPlayer->bTransparency)
		cout << "ON\t";
	else
		cout << "OFF\t";

	cout << "���б� : ";
	if (pPlayer->bWallPush)
	{
		cout << "����";

		if (pPlayer->bPushOnOff)
			cout << "/ON" << endl;
		else
			cout << "/OFF" << endl;
	}
	else
		cout << "�Ұ���" << endl;
}

bool AddItem(char cItemType, PPLAYER pPlayer)
{
	if (cItemType == '5')
	{
		if(pPlayer->iBombPower < 5)
			++pPlayer->iBombPower;
		return true;
	}

	else if (cItemType == '6')
	{
		pPlayer->bWallPush = true;
		pPlayer->bPushOnOff = true;
		return true;
	}
	else if (cItemType == '7')
	{
		pPlayer->bTransparency = true;
		return true;
	}

	return false;
}

void MoveUp(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y - 1 >= 0)
	{
		//������ üũ�Ѵ�.
		if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '0' &&
			Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4')
		{
			--pPlayer->tPos.y;
		}

		// ���бⰡ �����ϰ� �ٷ� ��ĭ�� ���� ���
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] == '0')
		{
			// �� �бⰡ ON ������ ���
			if (pPlayer->bPushOnOff)
			{
				// ���� ��ĭ�� 0���� ũ�ų� ���� ���� �ε����� �ִٴ� �ǹ�.
				if (pPlayer->tPos.y - 2 >= 0)
				{
					//���� ��ĭ�� ���̾�� �бⰡ �����ϴ�. �׷��Ƿ� ������ üũ�Ѵ�,
					if (Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] == '0')
					{
						if (pPlayer->bTransparency)
							--pPlayer->tPos.y;
					}

					// ���� ��� ���� �о��.
					else if (Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] = '1')
					{
						// ���� ��ĭ�� ������ �ϰ�
						Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] = '0';
						// ��ĭ�� ���̾��µ� ��� ������ش�.
						Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] = '1';
						// �÷��̾ �̵���Ų��.
						--pPlayer->tPos.y;
					}
				}

				else if (pPlayer->bTransparency)
					--pPlayer->tPos.y;
			}

			// �� �б� OFF ������ ���
			else if (pPlayer->bTransparency)
				--pPlayer->tPos.y;
		}

		else if(pPlayer->bTransparency)
				--pPlayer->tPos.y;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';	
	}
}

void MoveDown(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y + 1 < 20)
	{
		//������ üũ�Ѵ�.
		if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '0' &&
			Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4')
		{
			++pPlayer->tPos.y;
		}

		// ���бⰡ �����ϰ� �ٷ� ��ĭ�� ���� ���
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] == '0')
		{
			// �� �бⰡ ON ������ ���
			if (pPlayer->bPushOnOff)
			{
				// ���� ��ĭ�� 0���� ũ�ų� ���� ���� �ε����� �ִٴ� �ǹ�.
				if (pPlayer->tPos.y + 2 < 20)
				{
					//���� ��ĭ�� ���̾�� �бⰡ �����ϴ�. �׷��Ƿ� ������ üũ�Ѵ�,
					if (Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] == '0')
					{
						if (pPlayer->bTransparency)
							++pPlayer->tPos.y;
					}

					// ���� ��� ���� �о��.
					else if (Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] = '1')
					{
						// ���� ��ĭ�� ������ �ϰ�
						Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] = '0';
						// ��ĭ�� ���̾��µ� ��� ������ش�.
						Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] = '1';
						// �÷��̾ �̵���Ų��.
						++pPlayer->tPos.y;
					}
				}

				else if (pPlayer->bTransparency)
					++pPlayer->tPos.y;
			}

			// �� �б� OFF ������ ���
			else if (pPlayer->bTransparency)
				++pPlayer->tPos.y;
		}


		else if (pPlayer->bTransparency)
			++pPlayer->tPos.y;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveRight(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x + 1 < 20)
	{
		//������ üũ�Ѵ�.
		if (Maze[pPlayer->tPos.y][pPlayer->tPos. x+1] != '0' &&
			Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '4')
		{
			++pPlayer->tPos.x;
		}

		// ���бⰡ �����ϰ� �ٷ� ��ĭ�� ���� ���
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] == '0')
		{
			// �� �бⰡ ON ������ ���
			if (pPlayer->bPushOnOff)
			{
				// ���� ��ĭ�� 0���� ũ�ų� ���� ���� �ε����� �ִٴ� �ǹ�.
				if (pPlayer->tPos.x + 2 < 20)
				{
					//���� ��ĭ�� ���̾�� �бⰡ �����ϴ�. �׷��Ƿ� ������ üũ�Ѵ�,
					if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] == '0')
					{
						if (pPlayer->bTransparency)
							++pPlayer->tPos.x;
					}

					// ���� ��� ���� �о��.
					else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x+2] = '1')
					{
						// ���� ��ĭ�� ������ �ϰ�
						Maze[pPlayer->tPos.y][pPlayer->tPos.x+2] = '0';
						// ��ĭ�� ���̾��µ� ��� ������ش�.
						Maze[pPlayer->tPos.y ][pPlayer->tPos.x+1] = '1';
						// �÷��̾ �̵���Ų��.
						++pPlayer->tPos.x;
					}
				}

				else if (pPlayer->bTransparency)
					++pPlayer->tPos.x;
			}

			// �� �б� OFF ������ ���
			else if (pPlayer->bTransparency)
				++pPlayer->tPos.x;
		}

		else if (pPlayer->bTransparency)
			++pPlayer->tPos.x;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveLeft(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x - 1 >= 0)
	{
		//������ üũ�Ѵ�.
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '0' &&
			Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4')
		{
			--pPlayer->tPos.x;
		}
		// ���бⰡ �����ϰ� �ٷ� ��ĭ�� ���� ���
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] == '0')
		{
			// �� �бⰡ ON ������ ���
			if (pPlayer->bPushOnOff)
			{
				// ���� ��ĭ�� 0���� ũ�ų� ���� ���� �ε����� �ִٴ� �ǹ�.
				if (pPlayer->tPos.x - 2 >= 0)
				{
					//���� ��ĭ�� ���̾�� �бⰡ �����ϴ�. �׷��Ƿ� ������ üũ�Ѵ�,
					if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] == '0')
					{
						if (pPlayer->bTransparency)
							--pPlayer->tPos.x;
					}

					// ���� ��� ���� �о��.
					else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] = '1')
					{
						// ���� ��ĭ�� ������ �ϰ�
						Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] = '0';
						// ��ĭ�� ���̾��µ� ��� ������ش�.
						Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] = '1';
						// �÷��̾ �̵���Ų��.
						--pPlayer->tPos.x;
					}
				}

				else if (pPlayer->bTransparency)
					--pPlayer->tPos.x;
			}

			// �� �б� OFF ������ ���
			else if (pPlayer->bTransparency)
				--pPlayer->tPos.x;
		}

		else if (pPlayer->bTransparency)
			--pPlayer->tPos.x;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}



void MovePlayer(char Maze[21][21], PPLAYER pPlayer, char cInput)
{
	switch (cInput)
	{
	case 'w':
	case 'W':
		MoveUp(Maze, pPlayer);
		break;
	case 's':
	case 'S':
		MoveDown(Maze, pPlayer);
		break;
	case 'a':
	case 'A':
		MoveLeft(Maze, pPlayer);
		break;
	case 'd':
	case 'D':
		MoveRight(Maze, pPlayer);
		break;
	}
}

// ����Ʈ ������ const�� �����ϸ� ����Ű�� ����� ���� ������ �� ����.
void CreateBomb(char Maze[21][21], const PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount )
{
	if (*pBombCount == 5)
		return;

	else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x] == '0')
		return;

	for (int i = 0; i < *pBombCount; ++i)
	{
		if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y)
			return;
	}


	pBombArr[*pBombCount] = pPlayer->tPos;
	++(*pBombCount);


	Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '4';
}

void Fire(char Maze[21][21], PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount)
{
	for (int i = 0; i < *pBombCount; ++i)
	{
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';


		// �÷��̾ ��ź�� �¾��� �� ���������� ������.
		if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y)
		{
			pPlayer->tPos.x = 0;
			pPlayer->tPos.y = 0;
		}

		for (int j = 1; j <= pPlayer->iBombPower; ++j)
		{
			if (pBombArr[i].y - j >= 0)
			{
				if (Maze[pBombArr[i].y - j][pBombArr[i].x] == '0')
				{ 
					// ������ ��� Ȯ���� ���Ѵ�.
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (rand() % 100 < 40)					
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '5';	
						else if(iPercent < 70 )
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '6';
						else
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '7';

					}
					else
						Maze[pBombArr[i].y - j][pBombArr[i].x] = '1';
				}

				// �÷��̾ ��ź�� �¾��� �� ���������� ������.
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y - j)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}


			}

			if (pBombArr[i].y + j < 20)
			{
				if (Maze[pBombArr[i].y + j][pBombArr[i].x] == '0')
				{
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (rand() % 100 < 40)
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '5';
						else if (iPercent < 70)
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '6';
						else
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '7';

					}
					else
						Maze[pBombArr[i].y + j][pBombArr[i].x] = '1';
				}

				// �÷��̾ ��ź�� �¾��� �� ���������� ������.
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y + j)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x - j >= 0)
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x - j] == '0')
				{
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (rand() % 100 < 40)
							Maze[pBombArr[i].y][pBombArr[i].x-j] = '5';
						else if (iPercent < 70)
							Maze[pBombArr[i].y - j][pBombArr[i].x - j] = '6';
						else
							Maze[pBombArr[i].y - j][pBombArr[i].x - j] = '7';

					}
					else
						Maze[pBombArr[i].y][pBombArr[i].x - j] = '1';
				}

				// �÷��̾ ��ź�� �¾��� �� ���������� ������.
				if (pPlayer->tPos.x == pBombArr[i].x - j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x + j < 20)
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x + j] == '0')
				{
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (rand() % 100 < 40)
							Maze[pBombArr[i].y][pBombArr[i].x+j] = '5';
						else if (iPercent < 70)
							Maze[pBombArr[i].y][pBombArr[i].x+j] = '6';
						else
							Maze[pBombArr[i].y - j][pBombArr[i].x+j] = '7';

					}
					else
						Maze[pBombArr[i].y][pBombArr[i].x + j] = '1';
				}

				// �÷��̾ ��ź�� �¾��� �� ���������� ������.
				if (pPlayer->tPos.x == pBombArr[i].x + j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}
		}
	}

	*pBombCount = 0;
}

int main()
{

	srand((unsigned int)time(0));
	char strMaze[21][21] = {};


	PLAYER tPlayer = {};
	
	POINT tStartPos;
	POINT tEndPos;

	tPlayer.iBombPower = 1;

	int iBombCount = 0 ;


	POINT tBombPos[5];

	// �̷θ� �����Ѵ�.
	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);

	while (true)
	{
		system("cls");

		// �̷θ� ����Ѵ�.
		Output(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y)
		{
			cout << "�����߽��ϴ�!!"<< endl;
			break;
		}

		cout << "t : ��ź��ġ,  u : ��ź ��Ʈ���� i : ���б� ON/OFF " << endl;
		cout << "w : �� s : �Ʒ� a: ���� d: ������ q : ���� ";

		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		else if (cInput == 't' || cInput == 'T')
		{
			CreateBomb(strMaze, &tPlayer, tBombPos, &iBombCount);
			
		}

		else if (cInput == 'u' || cInput == 'U')
		{
			Fire(strMaze, &tPlayer, tBombPos, &iBombCount);
		}

		else if (cInput == 'i' | cInput == 'I')
		{
			if (tPlayer.bWallPush)
				tPlayer.bPushOnOff = !tPlayer.bPushOnOff;
		}

		else
			MovePlayer(strMaze, &tPlayer, cInput);
	}
}
