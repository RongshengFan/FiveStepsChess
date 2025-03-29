#pragma once
typedef enum {
	WHITECHESS = -1,//����
	BLACKCHESS = 1  //����
}chesskind;
typedef struct point {
	int row;
	int col;
}point;
const int mar_x = 40;//������߽�ߴ�
const int mar_y = 40;//�����ϱ߽�ߴ�
const float blocksize = 40;//���Ӵ�С�����Ӵ�С
const int boardsize = 15;//���̴�С15x15
const int clickoffset = blocksize * 0.4;//�������ģ����������
struct chessdata {
	int num = 0;//��¼�ܲ���
	int ChessMap[boardsize][boardsize] = { 0 };//�洢��ǰ��Ϸ���̺����ӵ�������հ�Ϊ0������Ϊ1������Ϊ-1
	int ScoreMap[boardsize][boardsize] = { 0 };//�洢������λ�������������Ϊai��������
	bool player=true;//��ʾ���巽��true:���巽��false:ai��
};
struct cunchu {
	int map[boardsize][boardsize];
	int num;
	bool player;
};
void initdata(chessdata* data);//��ʼ������ 
void update(chessdata* data, int row, int col);//������Ϸ����
void calculate_ai(chessdata* data);//����ai����λ���ֵ
void calculate_AI(chessdata* data);//����AI����λ���ֵ
point aiAction(chessdata* data);//����ai����λ���ж�
point AIAction(chessdata* data);//����AI����λ���ж�
bool win_fail(chessdata* game, int row, int col);//�ж�ʤ������
