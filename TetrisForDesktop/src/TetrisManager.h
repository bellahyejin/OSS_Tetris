#ifndef _BOARD_H
#define _BOARD_H

#include "Block.h"
#include <time.h> //// ������� �߰�

enum GameStatus{
	PLAYING, END
};

#define BOARD_ROW_SIZE 24
#define BOARD_COL_SIZE 14

typedef struct _tetrisManager{
	char board[BOARD_ROW_SIZE][BOARD_COL_SIZE];
	Block block;
	int isHoldAvailable; // if hold block is empty or hold turn is passed, this variable is true
	Block shadow;
	int deletedLineCount;
	int speedLevel;
	int score;
	int isSplashMode; //// �Ȱ� ����ü ����
	time_t randSpeedTimer; ///// ������ ���� �ð� ( 5�ʸ� ��� ���� ��� )
	int diff_speed; ////// ���� �ӵ� ( +2 �Ǵ� -2 )
}TetrisManager;

void TetrisManager_Init(TetrisManager* tetrisManager, int speedLevel);
void TetrisManager_ProcessDirection(TetrisManager* tetrisManager, int direction);
void TetrisManager_ProcessAuto(TetrisManager* tetrisManager);
void TetrisManager_ProcessDirectDown(TetrisManager* tetrisManager);
void TetrisManager_ProcessDeletingLines(TetrisManager* tetrisManager);
int TetrisManager_IsReachedToBottom(TetrisManager* tetrisManager, int blockType);
int TetrisManager_ProcessReachedCase(TetrisManager* tetrisManager);
void TetrisManager_Print(TetrisManager* tetrisManager);
void TetrisManager_PrintBoard(TetrisManager* tetrisManager);
void TetrisManager_PrintDetailInfomation(TetrisManager* tetrisManager);
DWORD TetrisManager_GetDownMilliSecond(TetrisManager* tetrisManager);
void TetrisManager_MakeHold(TetrisManager* tetrisManager);

void splash(TetrisManager* tetrisManager, int blockType, int isSplash);  //// �Ȱ� ������ �Լ�
void TetrisManager_randSpeed(TetrisManager* tetrisManager); //// ���� �ӵ� ��ȯ ������ �Լ�

#endif