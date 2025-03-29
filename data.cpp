#include "chessdata.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
void initdata(chessdata* data)//��ʼ������
{
	data->num = 0;
	memset(data->ChessMap, 0, sizeof(data->ChessMap));
	if (!data)return;
	memset(data->ScoreMap, 0, sizeof(data->ScoreMap));
	data->player = true;
}
void update(chessdata* data, int row, int col)//�������ݸ���
{
	if (!data)return;
	if (data->player)
		data->ChessMap[row][col] = 1;
	else
		data->ChessMap[row][col] = -1;
	data->player = !data->player;//����
	data->num = data->num + 1;
}
void calculate_ai(chessdata* data)//λ���ֵ����
{
	if (!data)return;
	int manNum = 0;//������ɵ���
	int aiNum = 0;//ai���ɵ���
	int EmptyNum = 0;//������հ�λ����
	memset(data->ScoreMap, 0, sizeof(data->ScoreMap));//���������
	for (int row = 0; row < boardsize; row++)
	{
		for (int col = 0; col < boardsize; col++)
		{
			if (row >= 0 && col >= 0 && data->ChessMap[row][col] == 0)
			{
				//������Χ�ĸ����򣬷ֱ����������������
				int directs[4][2] = { {1,0},{1,1},{0,1},{-1,1} };
				for (int t = 0; t < 4; t++)
				{
					int x = directs[t][0];
					int y = directs[t][1];
					//����
					manNum = 0;
					aiNum = 0;
					EmptyNum = 0;
					//�Ժ�����������
					//����������i��λ������[row + i * y][col + i * x]
					for (int i = 1; i <= 4; i++)
					{
						if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->ChessMap[row + i * y][col + i * x] == 1)
						{
							manNum++;//��ҵ���
						}
						else if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->ChessMap[row + i * y][col + i * x] == 0)
						{
							EmptyNum++;
							break;//�����հ�λ�ã�ֹͣ�÷��������
						}
						else      //���߽磬�����������壬ֹͣ�÷��������
							break;
					}
					//�Ժ��巴������
					//����������i��λ������[row - i * y][col - i * x]
					for (int i = 1; i <= 4; i++)
					{
						if (row - i * y >= 0 && row - i * y < boardsize && col - i * x >= 0 && col - i * x < boardsize && data->ChessMap[row - i * y][col - i * x] == 1)
						{
							manNum++;
						}
						else if (row - i * y >= 0 && row - i * y < boardsize && col - i * x >= 0 && col - i * x < boardsize && data->ChessMap[row - i * y][col - i * x] == 0)
						{
							EmptyNum++;
							break;
						}
						else        //���߽磬������ai������
							break;
					}
					if (manNum == 1)//ɱ��
						data->ScoreMap[row][col] += 10;
					else if (manNum == 2) //ɱ��
					{
						if (EmptyNum == 1)//����
						{
							data->ScoreMap[row][col] += 30;
						}
						else if (EmptyNum == 2)//����
						{
							data->ScoreMap[row][col] += 40;
						}
					}
					else if (manNum == 3)//ɱ��
					{
						if (EmptyNum == 1)//����
							data->ScoreMap[row][col] += 60;
						else if (EmptyNum == 2)//����
							data->ScoreMap[row][col] += 200;
					}
					else if (manNum == 4)//ɱ��
						data->ScoreMap[row][col] += 20000;
					EmptyNum = 0;//����һ�����
					//�԰�����������
					for (int i = 1; i <= 4; i++)
					{
						if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->ChessMap[row + i * y][col + i * x] == -1)
						{
							aiNum++;
						}
						else if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->ChessMap[row + i * y][col + i * x] == 0)
						{
							EmptyNum++;//�հ�λ��
							break;
						}
						else
							break;
					}
					//�԰��巴������
					for (int i = 1; i <= 4; i++)
					{
						if (row - i * y >= 0 && row - i * y < boardsize && col - i * x >= 0 && col - i * x < boardsize && data->ChessMap[row - i * y][col - i * x] == -1)
						{
							aiNum++;
						}
						else if (row - i * y >= 0 && row - i * y < boardsize && col - i * x >= 0 && col - i * x < boardsize && data->ChessMap[row - i * y][col - i * x] == 0)
						{
							EmptyNum++;
							break;
						}
						else        //���߽�
							break;
					}
					if (aiNum == 0)//��ͨ����
						data->ScoreMap[row][col] += 5;
					else if (aiNum == 1)//���
						data->ScoreMap[row][col] += 10;
					else if (aiNum == 2)
					{
						if (EmptyNum == 1)//����
							data->ScoreMap[row][col] += 25;
						else if (EmptyNum == 2)//����
							data->ScoreMap[row][col] += 50;
					}
					else if (aiNum == 3)
					{
						if (EmptyNum == 1)//����
							data->ScoreMap[row][col] += 55;
						else if (EmptyNum == 2)//����
							data->ScoreMap[row][col] += 300;
					}
					else if (aiNum >= 4)//����
						data->ScoreMap[row][col] += 30000;
				}
			}
		}
	}
}
void calculate_AI(chessdata* data)//��������
{
	if (!data)return;
	int AINum = 0;//AI���ɵ���
	int aiNum = 0;//ai���ɵ���
	int EmptyNum = 0;//������հ�λ����
	memset(data->ScoreMap, 0, sizeof(data->ScoreMap));//���������
	for (int row = 0; row < boardsize; row++)
	{
		for (int col = 0; col < boardsize; col++)
		{
			if (row >= 0 && col >= 0 && data->ChessMap[row][col] == 0)
			{
				//������Χ�ĸ����򣬷ֱ����������������
				int directs[4][2] = { {1,0},{1,1},{0,1},{-1,1} };
				for (int k = 0; k < 4; k++)
				{
					int x = directs[k][0];
					int y = directs[k][1];
					//����
					AINum = 0;
					aiNum = 0;
					EmptyNum = 0;
					//�԰�����������
					for (int i = 1; i <= 4; i++)
					{
						if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->ChessMap[row + i * y][col + i * x] == -1)
						{
							aiNum++;
						}
						else if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->ChessMap[row + i * y][col + i * x] == 0)
						{
							EmptyNum++;//�հ�λ��
							break;
						}
						else
							break;
					}
					//�԰��巴������
					for (int i = 1; i <= 4; i++)
					{
						if (row - i * y >= 0 && row - i * y < boardsize && col - i * x >= 0 && col - i * x < boardsize && data->ChessMap[row - i * y][col - i * x] == -1)
						{
							aiNum++;
						}
						else if (row - i * y >= 0 && row - i * y < boardsize && col - i * x >= 0 && col - i * x < boardsize && data->ChessMap[row - i * y][col - i * x] == 0)
						{
							EmptyNum++;
							break;
						}
						else        //���߽�
							break;
					}
					if (aiNum == 0)//��ͨ����
						data->ScoreMap[row][col] += 5;
					else if (aiNum == 1)//���
						data->ScoreMap[row][col] += 15;
					else if (aiNum == 2)
					{
						if (EmptyNum == 1)//����
							data->ScoreMap[row][col] += 25;
						else if (EmptyNum == 2)//����
							data->ScoreMap[row][col] += 50;
					}
					else if (aiNum == 3)
					{
						if (EmptyNum == 1)//����
							data->ScoreMap[row][col] += 75;
						else if (EmptyNum == 2)//����
							data->ScoreMap[row][col] += 300;
					}
					else if (aiNum == 4)//����
						data->ScoreMap[row][col] += 20000;
					EmptyNum = 0;//����һ�����
					//�Ժ�����������
					//����������i��λ������[row + i * y][col + i * x]
					for (int i = 1; i <= 4; i++)
					{
						if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->ChessMap[row + i * y][col + i * x] == 1)
						{
							aiNum++;//��ҵ���
						}
						else if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->ChessMap[row + i * y][col + i * x] == 0)
						{
							EmptyNum++;
							break;//�����հ�λ�ã�ֹͣ�÷��������
						}
						else      //���߽磬�����������壬ֹͣ�÷��������
							break;
					}
					//�Ժ��巴������
					//����������i��λ������[row - i * y][col - i * x]
					for (int i = 1; i <= 4; i++)
					{
						if (row - i * y >= 0 && row - i * y < boardsize && col - i * x >= 0 && col - i * x < boardsize && data->ChessMap[row - i * y][col - i * x] == 1)
						{
							AINum++;
						}
						else if (row - i * y >= 0 && row - i * y < boardsize && col - i * x >= 0 && col - i * x < boardsize && data->ChessMap[row - i * y][col - i * x] == 0)
						{
							EmptyNum++;
							break;
						}
						else        //���߽磬������ai������
							break;
					}
					if (AINum == 0)
						data->ScoreMap[row][col] += 10;
					else if (AINum == 1)//ɱ��
						data->ScoreMap[row][col] += 100;
					else if (AINum == 2) //ɱ��
					{
						if (EmptyNum == 1)//����
						{
							data->ScoreMap[row][col] += 0;
						}
						else if (EmptyNum == 2)//����
						{
							data->ScoreMap[row][col] += 10;
						}
					}
					else if (AINum == 3)//ɱ��
					{
						if (EmptyNum == 1)//����
							data->ScoreMap[row][col] += 0;
						else if (EmptyNum == 2)//����
							data->ScoreMap[row][col] += 0;
					}
					else if (AINum >= 4)//ɱ��
						data->ScoreMap[row][col] += 30000;
				
				
				}
			}
		}
	}
}
point aiAction(chessdata* data)
{
	calculate_ai(data);//��������
	//�ҳ���������λ��
	int MaxScore = 0;
	point MaxPoint[boardsize * boardsize] = { 0 };
	int k = 0;
	for (int row = 0; row < boardsize; row++)
	{
		for (int col = 0; col < boardsize; col++)
		{
			if (data->ChessMap[row][col] == 0)//ǰ�����������Ϊ��
			{
				if (data->ScoreMap[row][col] > MaxScore)//�����ķ���������
				{
					memset(MaxPoint, 0, sizeof(MaxPoint));
					k = 0;
					MaxScore = data->ScoreMap[row][col];
					MaxPoint[k].row = row;
					MaxPoint[k].col = col;
					k++;
				}
				else if (data->ScoreMap[row][col] == MaxScore)//����ж�����ķ�������������
				{
					MaxPoint[k].row = row;
					MaxPoint[k].col = col;
					k++;
				}
			}
		}
	}
	//���ж���㣬���������
	srand((unsigned)time(0));
	int index = rand() % k;
	return MaxPoint[index];
}
point AIAction(chessdata* data)
{
	calculate_AI(data);//��������
	//�ҳ���������λ��
	int MaxScore = 0;
	point MaxPoint[boardsize * boardsize] = { 0 };
	int k = 0;
	for (int row = 0; row < boardsize; row++)
	{
		for (int col = 0; col < boardsize; col++)
		{
			if (data->ChessMap[row][col] == 0)//ǰ�����������Ϊ��
			{
				if (data->ScoreMap[row][col] > MaxScore)//�����ķ���������
				{
					memset(MaxPoint, 0, sizeof(MaxPoint));
					k = 0;
					MaxScore = data->ScoreMap[row][col];
					MaxPoint[k].row = row;
					MaxPoint[k].col = col;
					k++;
				}
				else if (data->ScoreMap[row][col] == MaxScore)//����ж�����ķ�������������
				{
					MaxPoint[k].row = row;
					MaxPoint[k].col = col;
					k++;
				}
			}
		}
	}
	//���ж���㣬���������
	srand((unsigned)time(0));
	int index = rand() % k;
	return MaxPoint[index];
}
bool win_fail(chessdata* game, int row, int col)
{
	//����б�Ĵ������ÿ����������ݵ�ǰ�����������5�����ӣ�����һ�ּ�ʤ��
	for (int i = 0; i < 5; i++)
	{   //ˮƽ����
		if (col - i >= 0 && col - i + 4 < boardsize && game->ChessMap[row][col - i] == game->ChessMap[row][col - i + 1] && game->ChessMap[row][col - i] == game->ChessMap[row][col - i + 2] && game->ChessMap[row][col - i] == game->ChessMap[row][col - i + 3] && game->ChessMap[row][col - i] == game->ChessMap[row][col - i + 4])
			return true;
	    //��ֱ������������4��
		if (row - i >= 0 && row - i + 4 < boardsize && game->ChessMap[row - i][col] == game->ChessMap[row - i + 1][col] && game->ChessMap[row - i][col] == game->ChessMap[row - i + 2][col] && game->ChessMap[row - i][col] == game->ChessMap[row - i + 3][col] && game->ChessMap[row - i][col] == game->ChessMap[row - i + 4][col])
			return true;
		//��[row+i]�У���[col-i]�е����������Ϸ�����4��������ͬʱ//"/"���
		if (row + i < boardsize && row + i - 4 >= 0 && col - i >= 0 && col - i + 4 < boardsize && game->ChessMap[row + i][col - i] == game->ChessMap[row + i - 1][col - i + 1] && game->ChessMap[row + i][col - i] == game->ChessMap[row + i - 2][col - i + 2] && game->ChessMap[row + i][col - i] == game->ChessMap[row + i - 3][col - i + 3] && game->ChessMap[row + i][col - i] == game->ChessMap[row + i - 4][col - i + 4])
			return true;
		//��[row-i]�У���[col-i]�е����������·�����4��������ͬʱ//"\"���
		if (row - i < boardsize && row - i + 4 >= 0 && col - i >= 0 && col - i + 4 < boardsize && game->ChessMap[row - i][col - i] == game->ChessMap[row - i + 1][col - i + 1] && game->ChessMap[row - i][col - i] == game->ChessMap[row - i + 2][col - i + 2] && game->ChessMap[row - i][col - i] == game->ChessMap[row - i + 3][col - i + 3] && game->ChessMap[row - i][col - i] == game->ChessMap[row - i + 4][col - i + 4])
			return true;
	}
	return false;
}
