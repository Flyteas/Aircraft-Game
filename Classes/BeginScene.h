/* 游戏开始幕 */
#ifndef _BEGIN_SCENE_H_
#define _BEGIN_SCENE_H_
#include "cocos2d.h"
#include "MainScene.h"

USING_NS_CC;
class BeginScene : public Layer //开始界面类
{
public:
	static Scene* CreateScene();
	virtual bool init();
	bool LoadGameRes();  //载入整个游戏所需的音频图片资源文件
	void DisplayTeam(Ref*);  //显示开发团队信息
	void GoToPlot_Level_0(Ref*);	//进入剧情
	void GoToPlot_Level_1(Ref*);	//进入剧情
	void GoToPlot_Level_2(Ref*);	//进入剧情
	CREATE_FUNC(BeginScene);
private:
	int GameLevel; //游戏难度
};


#endif