#ifndef _TETRIS_VIEW_H
#define _TETRIS_VIEW_H

#include "TetrisManager.h"
#include "RankingManager.h"

typedef struct _tetrisView{
	TetrisManager tetrisManager;
	RankingManager rankingManager;
	int level;
	int mainMenu;
	int pauseMenu;
	int endMenu;
}TetrisView;

void TetrisView_Bgm(TetrisView* tetrisView, int mode);
void TetrisView_StartGame(TetrisView* tetrisView);
void TetrisView_ProcessGame(TetrisView* tetrisView, int processType, int direction, int isSplash); //// isSplash 매개변수 추가
void TetrisView_PauseGame(TetrisView* tetrisView);
void TetrisView_EndGame(TetrisView* tetrisView);
void TetrisView_ShowRanking(TetrisView* tetrisView);
void TetrisView_AddRanking(TetrisView* tetrisView);
void TetrisView_ShowSetting(TetrisView* tetrisView);
void TetrisView_ProcessMainMenu(TetrisView* tetrisView);
void TetrisView_ProcessPauseMenu(TetrisView* tetrisView);
void TetrisView_ProcessEndMenu(TetrisView* tetrisView);

//make temporarily for calling from main function
DWORD TetrisView_GetDownMilliSecond(TetrisView* tetrisView);
void TetrisView_MakeHold(TetrisView* tetrisView);

/*void TetrisView_Item_RemoveOneRow(TetrisView* tetrisView);	//아이템1 : 한 줄 제거
void TetrisView_Item_RemoveTwoRow(TetrisView* tetrisView);	//아이템2 : 두 줄 제거
void TetrisView_Item_RemoveAllRow(TetrisView* tetrisView);	//아이템3 : 전체 줄 제거*/
void TetrisView_ChangeNextBlock(TetrisView* tetrisView);//다음블럭과 다다음블럭 바꾸기

int level_scanf(int x, int y); // 레벨 입력받는 함수

#endif