#ifndef _ENDSCENE_H_
#define _ENDSCENE_H_
#include "common.h"
#include "MainScene.h"
USING_NS_CC;
class EndScene:public Layer
{
public:
	static EndScene* create(int Score_Input);
	static Scene* CreateScene(int Score_Input);
	bool init(int Score_Input);
	void RestartGame(Ref*); //重新开始游戏
private:
	int Final_Score;
	int ScoreList[4];
};

#endif
