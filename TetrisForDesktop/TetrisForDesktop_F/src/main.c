#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "Constant.h"
#include "TetrisView.h"
#include <time.h> ////������� �߰�
#include <stdlib.h> ////������� �߰�

int main(int argc, char* argv[]){
	TetrisView tetrisView;
	int processType;
	int direction;
	DWORD tickCount;
	int isSetMainMenu = False;

	time_t splashTimer = 0; //// �Ȱ� ������ ���� �ð� ( 5�ʸ� �����ϱ� ���� ��� )
	time_t curTimer = 0; //// ����ð�
	time_t gameStartTimer = 0;//// ���ӽ��۽ð��� ����
	
	int splashOnFlag = 0; //// �Ȱ� ���� �� �ٽ� ���� ���� 
	int isSplash = 0; //// 0 : ����, 1 : �Ȱ�, 2 : ������ ����

	do{
		TetrisView_ProcessMainMenu(&tetrisView);
		switch (tetrisView.mainMenu){
		case START_MAIN_MENU:
			TetrisView_StartGame(&tetrisView);
			tickCount = GetTickCount();
			gameStartTimer = time(NULL); //// ���� ���� �ð� ����( ���� : �� )
			tetrisView.tetrisManager.randSpeedTimer = 0; //// ��������� ���� �ʱ�ȭ
			
			while (True){
				processType = AUTO;
				direction = DOWN;
				isSetMainMenu = False;
				while (True){
					//// ���� �ð� ����( ���� : �� )
					curTimer = time(NULL);

					//// ����ð��� ���� ���� �� 60�ʰ� ���� �ð��̸� �Ȱ� �̺�Ʈ ����
					if (curTimer - gameStartTimer > 60 && splashOnFlag == 0 )
					{
						splashTimer = time(NULL);
						isSplash = 1;
						tetrisView.tetrisManager.isSplashMode = 1;
						splashOnFlag = 1;
					}
					//// splash �� 5�ʰ� �������� ���󺹱�
					if (splashTimer != 0 && curTimer - splashTimer >= 5)
					{
						isSplash = 0;
						splashTimer = 0;
						tetrisView.tetrisManager.isSplashMode = 0;
					}

					if (GetTickCount() - tickCount > TetrisView_GetDownMilliSecond(&tetrisView)){
						processType = AUTO;
						direction = DOWN;
						tickCount = GetTickCount();
						break;
					}
					if (_kbhit()){
						int key = _getch();
						if (key == 0xE0 && _kbhit()){
							key = _getch();
							if (key == UP_KEY_CODE){
								processType = DIRECTION;
								direction = UP;
								break;
							}
							if (key == DOWN_KEY_CODE){
								processType = DIRECTION;
								direction = DOWN;
								tickCount = GetTickCount();
								break;
							}
							if (key == LEFT_KEY_CODE){
								processType = DIRECTION;
								direction = LEFT;
								break;
							}
							if (key == RIGHT_KEY_CODE){
								processType = DIRECTION;
								direction = RIGHT;
								break;
							}
						}
						else{
							if (key == SPACE_BAR_KEY_CODE){
								processType = DIRECT_DOWN;
								tickCount = GetTickCount();
								break;
							}
							if (key == ESC_KEY_CODE){
								TetrisView_PauseGame(&tetrisView);
								if (tetrisView.pauseMenu == MAIN_MENU_PAUSE_MENU){
									isSetMainMenu = True;
									break;
								}
								processType = AUTO;
								tickCount = GetTickCount();
								break;
							}
							if (key == L_KEY_CODE){
								TetrisView_MakeHold(&tetrisView);
							}
						}
					}
				}

				//for selecting main menu at pause menu
				if (isSetMainMenu){
					break;
				}
				TetrisView_ProcessGame(&tetrisView, processType, direction, isSplash); //// isSplash �Ű����� �߰�
				if (tetrisView.endMenu == RANKING_END_MENU){
					TetrisView_AddRanking(&tetrisView);
					TetrisView_ShowRanking(&tetrisView);
					break;
				}
				else if (tetrisView.endMenu == MAIN_MENU_END_MENU){
					break;
				}
				else if (tetrisView.endMenu == EXIT_END_MENU){
					tetrisView.mainMenu = EXIT_MAIN_MENU;
					break;
				}
			}
			break;
		case RANKING_MAIN_MENU:
			TetrisView_ShowRanking(&tetrisView);
			break;
		case SETTING_MAIN_MENU:
			TetrisView_ShowSetting(&tetrisView);
			break;
		}

	} while (tetrisView.mainMenu != EXIT_MAIN_MENU);
	return 0;
}