#pragma once
typedef enum {
	WHITECHESS = -1,//白子
	BLACKCHESS = 1  //黑子
}chesskind;
typedef struct point {
	int row;
	int col;
}point;
const int mar_x = 40;//棋盘左边界尺寸
const int mar_y = 40;//棋盘上边界尺寸
const float blocksize = 40;//棋子大小，格子大小
const int boardsize = 15;//棋盘大小15x15
const int clickoffset = blocksize * 0.4;//鼠标点击的模糊距离上限
struct chessdata {
	int num = 0;//记录总步数
	int ChessMap[boardsize][boardsize] = { 0 };//存储当前游戏棋盘和棋子的情况，空白为0，黑子为1，白子为-1
	int ScoreMap[boardsize][boardsize] = { 0 };//存储各个点位的评分情况，作为ai下棋依据
	bool player=true;//表示下棋方，true:黑棋方，false:ai方
};
struct cunchu {
	int map[boardsize][boardsize];
	int num;
	bool player;
};
void initdata(chessdata* data);//初始化数据 
void update(chessdata* data, int row, int col);//更新游戏数据
void calculate_ai(chessdata* data);//白子ai计算位点价值
void calculate_AI(chessdata* data);//黑子AI计算位点价值
point aiAction(chessdata* data);//白子ai落子位置判断
point AIAction(chessdata* data);//黑子AI落子位置判断
bool win_fail(chessdata* game, int row, int col);//判断胜负结束
