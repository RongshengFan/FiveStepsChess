#include <stdio.h>
#include <math.h>
#include <graphics.h>//easyxͼ���ͷ�ļ�
#include <mmsystem.h>//��������ͷ�ļ�
#include <string.h>
#include <stdlib.h>
#include "chessdata.h"
#pragma comment(lib,"winmm.lib")
#define  pi 20
FILE* fp;
cunchu f[100][225];//��¼����
IMAGE blackchess;//����
IMAGE whitechess;//����
chessdata game;//��Ϸ����
int x=0;//�طŶԾ���
int sum = 0;//�Ծ���
int clickrow, clickcol;//��Ч���λ��
void jiazai();//����ҳ��
void menu();//��ҳ��˵�
void aigo();//���巽aiִ��
void AIgo();//���巽AIִ��
void mango();//���巽���ִ��
void Mango();//���巽���ִ��
void over();//��Ϸ��������
bool judge();//�ж���Ϸ�Ƿ����
void board();//��������
void pvp();//���˶�ս
void pve();//�˻���ս
void eve();//������ս
void record();//�طŵ�ѡ�����
void review();//���жԾֻط�
void save(chessdata* game);//��¼�Ծ�����
bool clickboard(MOUSEMSG msg);//�ж���Ч�������������λ��
void chessdown(int row, int col, chesskind kind);//����
bool clickboard(MOUSEMSG msg)
{
	int x = msg.x;
	int y = msg.y;
	int col = (x - mar_x) / blocksize;
	int row = (y - mar_y) / blocksize;
	int left_top_x = mar_x + blocksize * col;
	int left_top_y = mar_y + blocksize * row;
	int lenth;
	do{
		//�������Ͻǵľ���
		lenth = sqrt((x - left_top_x) * (x - left_top_x) + (y - left_top_y) * (y - left_top_y ));
		if (lenth < clickoffset) {
			clickrow = row;
			clickcol = col;
			if (game.ChessMap[clickrow][clickcol] == 0)
				return true;
			break;
		}
		//�������½ǵľ���
		lenth = sqrt((x - left_top_x - blocksize ) * (x - left_top_x - blocksize) + (y - left_top_y) * (y - left_top_y));
		if (lenth < clickoffset) {
			clickrow = row ;
			clickcol = col + 1;
			if (game.ChessMap[clickrow][clickcol] == 0)
				return true;
			break;
		}
		//�������Ͻǵľ���
		lenth = sqrt((x - left_top_x) * (x - left_top_x) + (y - left_top_y-blocksize) * (y - left_top_y-blocksize));
		if (lenth < clickoffset) {
			clickrow = row + 1;
			clickcol = col;
			if (game.ChessMap[clickrow][clickcol] == 0) 
				return true;
			break;
		}
	//�������½ǵľ���
		lenth = sqrt((x - left_top_x - blocksize) * (x - left_top_x - blocksize) + (y - left_top_y - blocksize) * (y - left_top_y - blocksize));
		if (lenth < clickoffset)
		{
			clickrow = row + 1;
			clickcol = col + 1;
			if (game.ChessMap[clickrow][clickcol] == 0)
				return true;			
			break;
		}
	} while (0);
	return false;
}
void chessdown(int row, int col, chesskind kind)
{
	mciSendString("play res/down.mp3", 0, 0, 0);
	int x = mar_x + col * blocksize - 0.5 * blocksize;
	int y = mar_y + row * blocksize - 0.5 * blocksize;
	if (kind == WHITECHESS) {
		putimage(x, y ,&whitechess);
	}
	else if(kind==BLACKCHESS)
	{
		putimage (x, y ,&blackchess);
	}
}
void jiazai()//���ؽ���
{
	initgraph(800, 670);
	IMAGE bk;
	loadimage(&bk, _T("res/bk.jpg"));
	putimage(0, 0, &bk);
	setbkmode(TRANSPARENT);//͸������
	settextstyle(180, 0, _T("�����п�"));//������ʽ
	settextcolor(YELLOW);//�����ɫ
	outtextxy(160, 180, _T("������"));//����
	solidroundrect(160, 590, 680, 650, pi, pi);//���ޱ߿�Բ�Ǿ��ΰ�ɫ������
	for (int i = 190; i <= 680; i = i + 5)
	{
		settextstyle(60, 0, _T("����"));
		setfillcolor(RGB(100, 240, 220));
		solidroundrect(300, 510, 540, 570, pi, pi);
		fillroundrect(300, 510, 540, 570, pi, pi);//���б߿�Բ�Ǿ���
		setfillcolor(RGB(100, 240, 220));
		outtextxy(330, 510, _T("������"));
		settextcolor(WHITE);//���������ɫ
		fillroundrect(160, 590, i, 650, pi, pi);//�����ȼ�����
		setfillcolor(RGB(100, 240, 220));//���ȼ�������ɫ
		if (i == 680)
		{
			setfillcolor(RGB(100, 240, 220));
			solidroundrect(300, 510, 540, 570, pi, pi);
			fillroundrect(300, 510, 540, 570, pi, pi);
			outtextxy(300, 510, _T("���سɹ�"));
			Sleep(300);
		}
		else system("cls");
	}
	Sleep(100);
}
void board()//��������
{
	initgraph(800, 800);//��������
	IMAGE bp;
	loadimage(&bp, _T("res/bp.jpg"));
	putimage(0, 0, &bp);
	setfillcolor(RGB(250, 250, 250));
	solidrectangle(20, 20, 620, 620);
	setlinecolor(BLACK);//���õ�ǰ�豸������ɫ
	for (int i = 40; i <= 600; i += 40)//������
	{
		line(i, 40, i, 600);
		line(40, i,600, i);
	}
	setbkmode(TRANSPARENT);
	roundrect(650, 200, 750, 240, pi, pi);
	roundrect(650, 320, 750, 360, pi, pi);
	roundrect(650, 440, 750, 480, pi, pi);
	settextstyle(36, 20, _T("����"));
	settextcolor(WHITE);
	outtextxy(660, 320, _T("����"));
	outtextxy(660, 440, _T("�˳�"));
}
void menu()
{
	initgraph(850, 700);
	IMAGE bg;
	loadimage(&bg, _T("res/bg.jpg"));
	putimage(0, 0, &bg);
	setbkmode(TRANSPARENT);
	roundrect(0, 200, 160, 250, pi, pi);
	roundrect(0, 300, 160, 350, pi, pi);
	roundrect(0, 400, 160, 450, pi, pi);
	roundrect(0, 500, 160, 550, pi, pi);
	roundrect(0, 600, 160, 650, pi, pi);
	settextstyle(48, 24, _T("����"));
	outtextxy(20, 200, _T("P V P"));
	outtextxy(20, 300, _T("P V E"));
	outtextxy(20, 400, _T("E V E"));
	outtextxy(20, 600, _T("EXIT>"));
	settextstyle(42, 21, _T("����"));
	outtextxy(20, 505, _T("REVIEW"));
	settextstyle(100,36, _T("�����п�"));
	outtextxy(720, 30, _T("��"));
	outtextxy(720, 150, _T("��"));
	outtextxy(720, 270, _T("��"));
	while (1) {
		MOUSEMSG m;
		m = GetMouseMsg();
		mciSendString("play res/bk.mp3", 0, 0, 0);
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (0 < m.x && m.x < 160 && m.y < 250 && 200 < m.y)
				pvp();
			else if (0 < m.x && m.x < 160 && m.y < 350 && 300 < m.y)
				pve();
			else if (0 < m.x && m.x < 160 && m.y < 450 && 400 < m.y)
				eve();
			else if (0 < m.x && m.x < 160 && m.y < 550 && 500 < m.y) {
				record();
			}
			else if (0 < m.x && m.x < 160 && m.y < 650 && 600 < m.y)
				exit(0);
			else continue;
		}
	}
}
void pve()
{
	jiazai();
	board();
	settextstyle(36, 20, _T("����"));
	outtextxy(660, 200, _T("����"));
	mciSendString("play res/start.wav", 0, 0, 0);//��ʼ��Ч
	loadimage(&blackchess, "res/black.png", blocksize, blocksize, true);
	loadimage(&whitechess, "res/white.png", blocksize, blocksize, true);
	initdata(&game);//��ʼ����Ϸģ��
	while (1)
	{
		MOUSEMSG m = GetMouseMsg();//�ȴ�����¼�
		if (m.uMsg == WM_LBUTTONDOWN)//����������
		{
			if (clickboard(m) && m.x <= 600 && m.y <= 600)
			{
				mango();//�������
				save(&game);
				if (judge())
				{
					fclose(fp);
					over();
				}
				aigo();//ai����
				save(&game);
				if (judge())
				{
					fclose(fp);
					over();
				}
			}
			if (m.x < 750 && m.x>650 && m.y < 260 && m.y>200)
			{
				game.player = false;
				aigo();
				save(&game);
			}
			if (m.x < 750 && m.x>650 && m.y < 360 && m.y>320)
			{
				pve();
			}
			if (m.x < 750 && m.x>650 && m.y < 480 && m.y>440)
			{
				menu();
			}
		}
	}
}
void pvp()
{
	jiazai();
	board();
	settextstyle(36, 20, _T("����"));
	outtextxy(660, 200, _T("����"));
	mciSendString("play res/start.wav", 0, 0, 0);//��ʼ��Ч
	loadimage(&blackchess, "res/black.png", blocksize, blocksize, true);
	loadimage(&whitechess, "res/white.png", blocksize, blocksize, true);
	initdata(&game);//��ʼ����Ϸģ��
	while (1)
	{
		MOUSEMSG m = GetMouseMsg();//�ȴ�����¼�
		if (m.uMsg == WM_LBUTTONDOWN)//����������
		{
			if (m.x < 750 && m.x>650 && m.y < 260 && m.y>200)
			{
				game.player = !game.player;
			}
			if (m.x < 750 && m.x>650 && m.y < 360 && m.y>320)
			{
				pvp();
			}
			if (m.x < 750 && m.x>650 && m.y < 480 && m.y>440)
			{
				menu();
			}
			if (clickboard(m) && m.x <= 600 && m.y <= 600)
			{
				if (game.player == true)
				{
					mango();
					save(&game);
					if (judge())
					{
						fclose(fp);
						over();
					}
					continue;
				}
				if (game.player == false)
				{
					Mango();
					save(&game);
					if (judge())
					{
						fclose(fp);
						over();
					}
				}
			}
		}
	}
}
void eve()
{
	jiazai();
	board();
	settextstyle(36, 20, _T("����"));
	outtextxy(660, 200, _T("����"));
	mciSendString("play res/start.wav", 0, 0, 0);//��ʼ��Ч
	loadimage(&blackchess, "res/black.png", blocksize, blocksize, true);
	loadimage(&whitechess, "res/white.png", blocksize, blocksize, true);
	initdata(&game);//��ʼ����Ϸģ��
	while (1)
	{
		MOUSEMSG m = GetMouseMsg();//�ȴ�����¼�
		if (m.uMsg == WM_LBUTTONDOWN)//����������
		{
			if (m.x < 750 && m.x>650 && m.y < 260 && m.y>200)
			{
				AIgo();
				save(&game);
				if (judge())
				{
					fclose(fp);
					over();
				}
				aigo();
				save(&game);
				if (judge())
				{
					fclose(fp);
					over();
				}
			}
			if (m.x < 750 && m.x>650 && m.y < 360 && m.y>320)
			{
				eve();
			}
			if (m.x < 750 && m.x>650 && m.y < 480 && m.y>440)
			{
				menu();
			}
		}
	}
}
void mango()
{
	chessdown(clickrow, clickcol, BLACKCHESS);
	update(&game, clickrow, clickcol);//������������
}
void Mango() 
{
	chessdown(clickrow, clickcol, WHITECHESS);
	update(&game, clickrow, clickcol);//������������
}
void aigo()//ai����
{
	point point = aiAction(&game);
	clickrow = point.row;
	clickcol = point.col;
	Sleep(400);//��ai��һ��
	chessdown(clickrow, clickcol, WHITECHESS);
	update(&game, clickrow, clickcol);
}
void AIgo()
{
	point point = AIAction(&game);
	clickrow = point.row;
	clickcol = point.col;
	Sleep(400);//��ai��һ��
	chessdown(clickrow, clickcol, BLACKCHESS);
	update(&game, clickrow, clickcol);
}
bool judge()//�����Ϸ�Ƿ����
{
	if (win_fail(&game, clickrow, clickcol))
	{
		Sleep(100);
		return true;
	}
	return false;
}
void over() 
{
	sum = sum + 1;
	if (sum >=100)
	{
		sum = 1;
	}
	if (game.player == false)
	{
		setbkmode(TRANSPARENT);
		settextstyle(50, 25, _T("����"));
		settextcolor(BLACK);
		outtextxy(630, 80, _T("����ʤ"));
	}
	else if (game.player == true)
	{
		setbkmode(TRANSPARENT);
		settextstyle(50, 25, _T("����"));
		settextcolor(BLACK);
		outtextxy(630, 80, _T("����ʤ"));
	}
	while (1)
	{
		MOUSEMSG m;
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x < 750 && m.x>650 && m.y < 480 && m.y>440)
				menu();
			else continue;
		}
	}
}
void save(chessdata* game)
{
	fp = fopen("res/save.txt", "w");
		f[sum+1][game->num].map[clickrow][clickcol] = game->ChessMap[clickrow][clickcol];
		f[sum + 1]->num = game->num;
		f[sum + 1]->player = game->player;
		fwrite(&f, sizeof(struct cunchu), 1, fp);
}
void record()
{
	initgraph(800, 800);
	IMAGE bp;
	loadimage(&bp, _T("res/bp.jpg"));
	putimage(0, 0, &bp);
	settextstyle(60, 25, _T("����"));
	setbkmode(TRANSPARENT);
	for (int i = 1; i <=6; i++)
	{
	    roundrect(20, i * 100, 240, i * 100 + 60, pi, pi);
		outtextxy(30, i * 100, _T("�Ͼֻط�"));
	}
	setbkmode(TRANSPARENT);
	settextstyle(36, 20, _T("����"));
	roundrect(20, 20, 140, 60, pi, pi);
	outtextxy(30, 23, _T("<BACK"));
	while (1) {
		MOUSEMSG m;
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x < 140 && 20 < m.x && m.y < 60 && 20 < m.y)
			{
				menu();
			}
			else if (m.x <240 && 20 < m.x && m.y < 160 && 100 < m.y) 
			{
				x = sum;
				review();
			}
			else if (m.x < 240 && 20 < m.x && m.y < 260 && 200 < m.y)
			{
				x = sum - 1;
				if (x >= 1)
				{
					review();
				}
				else
				{
					continue;
				}
			}
			else if (m.x < 240 && 20 < m.x && m.y < 360 && 300 < m.y)
			{
				x = sum - 2;
				if (x >= 1)
				{
					review();
				}
				else
				{
					continue;
				}
			}
			else if (m.x < 240 && 20 < m.x  && m.y < 460 && 400 < m.y)
			{
				x = sum - 3;
				if (x >= 1)
				{
					review();
				}
				else
				{
					continue;
				}
			}
			else if (m.x < 240 && 20 < m.x  && m.y < 560 && 500 < m.y)
			{
				x = sum - 4;
				if (x >= 1)
				{
					review();
				}
				else
				{
					continue;
				}
			}
			else if (m.x < 240 && 20 < m.x && m.y < 660 && 600 < m.y)
			{
				x = sum - 5;
				if (x >= 1)
				{
					review();
				}
				else
				{
					continue;
				}
			}
			
		}
	}
}
void review()
{
	board();
	fp = fopen("res/save.txt", "r");
	for (int i = 1; i <= 6; i++)
	{
		for (int row = 0; row < boardsize; row++)
		{
			for (int col = 0; col < boardsize; col++)
			{
				fread(&f, sizeof(struct cunchu), 1, fp);
			}
		}
	}
	for (int i = 1; i <= f[x]->num; i++)
	{
		for (int row = 0; row < boardsize; row++)
		{
			for (int col = boardsize-1; col >=0; col--)
			{
				if (f[x][i].map[row][col] == 1)
				{
					Sleep(400);
					chessdown(row, col, BLACKCHESS);
				}
				else if (f[x][i].map[row][col] == -1)
				{
					Sleep(400);
					chessdown(row, col, WHITECHESS);
				}
				continue;
			}
		}
	}
	if (f[x]->player == false)
	{
		setbkmode(TRANSPARENT);
		settextstyle(50, 25, _T("����"));
		settextcolor(BLACK);
		outtextxy(630, 80, _T("����ʤ"));
	}
	else if (f[x]->player == true)
	{
		setbkmode(TRANSPARENT);
		settextstyle(50, 25, _T("����"));
		settextcolor(BLACK);
		outtextxy(630, 80, _T("����ʤ"));
	}
	fclose(fp);
	while (1)
	{
		MOUSEMSG m;
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x < 750 && m.x>650 && m.y < 480 && m.y>440)
			{
				record();
			}
		}
	}
}
int main()
{
	menu();
	return 0;
}