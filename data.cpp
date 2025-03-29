#include "chessdata.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
void initdata(chessdata* data)//初始化数据
{
	data->num = 0;
	memset(data->ChessMap, 0, sizeof(data->ChessMap));
	if (!data)return;
	memset(data->ScoreMap, 0, sizeof(data->ScoreMap));
	data->player = true;
}
void update(chessdata* data, int row, int col)//棋盘数据更新
{
	if (!data)return;
	if (data->player)
		data->ChessMap[row][col] = 1;
	else
		data->ChessMap[row][col] = -1;
	data->player = !data->player;//换手
	data->num = data->num + 1;
}
void calculate_ai(chessdata* data)//位点价值计算
{
	if (!data)return;
	int manNum = 0;//玩家连成的子
	int aiNum = 0;//ai连成的子
	int EmptyNum = 0;//各方向空白位个数
	memset(data->ScoreMap, 0, sizeof(data->ScoreMap));//清空评分组
	for (int row = 0; row < boardsize; row++)
	{
		for (int col = 0; col < boardsize; col++)
		{
			if (row >= 0 && col >= 0 && data->ChessMap[row][col] == 0)
			{
				//遍历周围四个方向，分别计算正反两个方向
				int directs[4][2] = { {1,0},{1,1},{0,1},{-1,1} };
				for (int t = 0; t < 4; t++)
				{
					int x = directs[t][0];
					int y = directs[t][1];
					//重置
					manNum = 0;
					aiNum = 0;
					EmptyNum = 0;
					//对黑棋正向评分
					//往这个方向第i个位置坐标[row + i * y][col + i * x]
					for (int i = 1; i <= 4; i++)
					{
						if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->ChessMap[row + i * y][col + i * x] == 1)
						{
							manNum++;//玩家的子
						}
						else if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->ChessMap[row + i * y][col + i * x] == 0)
						{
							EmptyNum++;
							break;//遇到空白位置，停止该方向的搜索
						}
						else      //出边界，或者遇到白棋，停止该方向的搜索
							break;
					}
					//对黑棋反向评分
					//往这个方向第i个位置坐标[row - i * y][col - i * x]
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
						else        //出边界，或者有ai的棋子
							break;
					}
					if (manNum == 1)//杀二
						data->ScoreMap[row][col] += 10;
					else if (manNum == 2) //杀三
					{
						if (EmptyNum == 1)//死三
						{
							data->ScoreMap[row][col] += 30;
						}
						else if (EmptyNum == 2)//活三
						{
							data->ScoreMap[row][col] += 40;
						}
					}
					else if (manNum == 3)//杀四
					{
						if (EmptyNum == 1)//死四
							data->ScoreMap[row][col] += 60;
						else if (EmptyNum == 2)//活四
							data->ScoreMap[row][col] += 200;
					}
					else if (manNum == 4)//杀五
						data->ScoreMap[row][col] += 20000;
					EmptyNum = 0;//进行一次清空
					//对白棋正向评分
					for (int i = 1; i <= 4; i++)
					{
						if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->ChessMap[row + i * y][col + i * x] == -1)
						{
							aiNum++;
						}
						else if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->ChessMap[row + i * y][col + i * x] == 0)
						{
							EmptyNum++;//空白位置
							break;
						}
						else
							break;
					}
					//对白棋反向评分
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
						else        //出边界
							break;
					}
					if (aiNum == 0)//普通下子
						data->ScoreMap[row][col] += 5;
					else if (aiNum == 1)//活二
						data->ScoreMap[row][col] += 10;
					else if (aiNum == 2)
					{
						if (EmptyNum == 1)//死三
							data->ScoreMap[row][col] += 25;
						else if (EmptyNum == 2)//活三
							data->ScoreMap[row][col] += 50;
					}
					else if (aiNum == 3)
					{
						if (EmptyNum == 1)//死四
							data->ScoreMap[row][col] += 55;
						else if (EmptyNum == 2)//活四
							data->ScoreMap[row][col] += 300;
					}
					else if (aiNum >= 4)//活五
						data->ScoreMap[row][col] += 30000;
				}
			}
		}
	}
}
void calculate_AI(chessdata* data)//算力较弱
{
	if (!data)return;
	int AINum = 0;//AI连成的子
	int aiNum = 0;//ai连成的子
	int EmptyNum = 0;//各方向空白位个数
	memset(data->ScoreMap, 0, sizeof(data->ScoreMap));//清空评分组
	for (int row = 0; row < boardsize; row++)
	{
		for (int col = 0; col < boardsize; col++)
		{
			if (row >= 0 && col >= 0 && data->ChessMap[row][col] == 0)
			{
				//遍历周围四个方向，分别计算正反两个方向
				int directs[4][2] = { {1,0},{1,1},{0,1},{-1,1} };
				for (int k = 0; k < 4; k++)
				{
					int x = directs[k][0];
					int y = directs[k][1];
					//重置
					AINum = 0;
					aiNum = 0;
					EmptyNum = 0;
					//对白棋正向评分
					for (int i = 1; i <= 4; i++)
					{
						if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->ChessMap[row + i * y][col + i * x] == -1)
						{
							aiNum++;
						}
						else if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->ChessMap[row + i * y][col + i * x] == 0)
						{
							EmptyNum++;//空白位置
							break;
						}
						else
							break;
					}
					//对白棋反向评分
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
						else        //出边界
							break;
					}
					if (aiNum == 0)//普通下子
						data->ScoreMap[row][col] += 5;
					else if (aiNum == 1)//活二
						data->ScoreMap[row][col] += 15;
					else if (aiNum == 2)
					{
						if (EmptyNum == 1)//死三
							data->ScoreMap[row][col] += 25;
						else if (EmptyNum == 2)//活三
							data->ScoreMap[row][col] += 50;
					}
					else if (aiNum == 3)
					{
						if (EmptyNum == 1)//死四
							data->ScoreMap[row][col] += 75;
						else if (EmptyNum == 2)//活四
							data->ScoreMap[row][col] += 300;
					}
					else if (aiNum == 4)//活五
						data->ScoreMap[row][col] += 20000;
					EmptyNum = 0;//进行一次清空
					//对黑棋正向评分
					//往这个方向第i个位置坐标[row + i * y][col + i * x]
					for (int i = 1; i <= 4; i++)
					{
						if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->ChessMap[row + i * y][col + i * x] == 1)
						{
							aiNum++;//玩家的子
						}
						else if (row + i * y >= 0 && row + i * y < boardsize && col + i * x >= 0 && col + i * x < boardsize && data->ChessMap[row + i * y][col + i * x] == 0)
						{
							EmptyNum++;
							break;//遇到空白位置，停止该方向的搜索
						}
						else      //出边界，或者遇到白棋，停止该方向的搜索
							break;
					}
					//对黑棋反向评分
					//往这个方向第i个位置坐标[row - i * y][col - i * x]
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
						else        //出边界，或者有ai的棋子
							break;
					}
					if (AINum == 0)
						data->ScoreMap[row][col] += 10;
					else if (AINum == 1)//杀二
						data->ScoreMap[row][col] += 100;
					else if (AINum == 2) //杀三
					{
						if (EmptyNum == 1)//死三
						{
							data->ScoreMap[row][col] += 0;
						}
						else if (EmptyNum == 2)//活三
						{
							data->ScoreMap[row][col] += 10;
						}
					}
					else if (AINum == 3)//杀四
					{
						if (EmptyNum == 1)//死四
							data->ScoreMap[row][col] += 0;
						else if (EmptyNum == 2)//活四
							data->ScoreMap[row][col] += 0;
					}
					else if (AINum >= 4)//杀五
						data->ScoreMap[row][col] += 30000;
				
				
				}
			}
		}
	}
}
point aiAction(chessdata* data)
{
	calculate_ai(data);//计算评分
	//找出分数最大的位置
	int MaxScore = 0;
	point MaxPoint[boardsize * boardsize] = { 0 };
	int k = 0;
	for (int row = 0; row < boardsize; row++)
	{
		for (int col = 0; col < boardsize; col++)
		{
			if (data->ChessMap[row][col] == 0)//前提是这个坐标为空
			{
				if (data->ScoreMap[row][col] > MaxScore)//找最大的分数和坐标
				{
					memset(MaxPoint, 0, sizeof(MaxPoint));
					k = 0;
					MaxScore = data->ScoreMap[row][col];
					MaxPoint[k].row = row;
					MaxPoint[k].col = col;
					k++;
				}
				else if (data->ScoreMap[row][col] == MaxScore)//如果有多个最大的分数，都存起来
				{
					MaxPoint[k].row = row;
					MaxPoint[k].col = col;
					k++;
				}
			}
		}
	}
	//若有多个点，则随机落子
	srand((unsigned)time(0));
	int index = rand() % k;
	return MaxPoint[index];
}
point AIAction(chessdata* data)
{
	calculate_AI(data);//计算评分
	//找出分数最大的位置
	int MaxScore = 0;
	point MaxPoint[boardsize * boardsize] = { 0 };
	int k = 0;
	for (int row = 0; row < boardsize; row++)
	{
		for (int col = 0; col < boardsize; col++)
		{
			if (data->ChessMap[row][col] == 0)//前提是这个坐标为空
			{
				if (data->ScoreMap[row][col] > MaxScore)//找最大的分数和坐标
				{
					memset(MaxPoint, 0, sizeof(MaxPoint));
					k = 0;
					MaxScore = data->ScoreMap[row][col];
					MaxPoint[k].row = row;
					MaxPoint[k].col = col;
					k++;
				}
				else if (data->ScoreMap[row][col] == MaxScore)//如果有多个最大的分数，都存起来
				{
					MaxPoint[k].row = row;
					MaxPoint[k].col = col;
					k++;
				}
			}
		}
	}
	//若有多个点，则随机落子
	srand((unsigned)time(0));
	int index = rand() % k;
	return MaxPoint[index];
}
bool win_fail(chessdata* game, int row, int col)
{
	//横竖斜四大情况，每种情况都根据当前落子往后遍历5个棋子，符合一种即胜利
	for (int i = 0; i < 5; i++)
	{   //水平方向
		if (col - i >= 0 && col - i + 4 < boardsize && game->ChessMap[row][col - i] == game->ChessMap[row][col - i + 1] && game->ChessMap[row][col - i] == game->ChessMap[row][col - i + 2] && game->ChessMap[row][col - i] == game->ChessMap[row][col - i + 3] && game->ChessMap[row][col - i] == game->ChessMap[row][col - i + 4])
			return true;
	    //竖直方向上下延伸4个
		if (row - i >= 0 && row - i + 4 < boardsize && game->ChessMap[row - i][col] == game->ChessMap[row - i + 1][col] && game->ChessMap[row - i][col] == game->ChessMap[row - i + 2][col] && game->ChessMap[row - i][col] == game->ChessMap[row - i + 3][col] && game->ChessMap[row - i][col] == game->ChessMap[row - i + 4][col])
			return true;
		//第[row+i]行，第[col-i]列的棋子与右上方连续4个棋子相同时//"/"情况
		if (row + i < boardsize && row + i - 4 >= 0 && col - i >= 0 && col - i + 4 < boardsize && game->ChessMap[row + i][col - i] == game->ChessMap[row + i - 1][col - i + 1] && game->ChessMap[row + i][col - i] == game->ChessMap[row + i - 2][col - i + 2] && game->ChessMap[row + i][col - i] == game->ChessMap[row + i - 3][col - i + 3] && game->ChessMap[row + i][col - i] == game->ChessMap[row + i - 4][col - i + 4])
			return true;
		//第[row-i]行，第[col-i]列的棋子与右下方连续4个棋子相同时//"\"情况
		if (row - i < boardsize && row - i + 4 >= 0 && col - i >= 0 && col - i + 4 < boardsize && game->ChessMap[row - i][col - i] == game->ChessMap[row - i + 1][col - i + 1] && game->ChessMap[row - i][col - i] == game->ChessMap[row - i + 2][col - i + 2] && game->ChessMap[row - i][col - i] == game->ChessMap[row - i + 3][col - i + 3] && game->ChessMap[row - i][col - i] == game->ChessMap[row - i + 4][col - i + 4])
			return true;
	}
	return false;
}
