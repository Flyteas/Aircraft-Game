/* ��Ϸ��ʼĻ */
#ifndef _BEGIN_SCENE_H_
#define _BEGIN_SCENE_H_
#include "cocos2d.h"
#include "MainScene.h"

USING_NS_CC;
class BeginScene : public Layer //��ʼ������
{
public:
	static Scene* CreateScene();
	virtual bool init();
	bool LoadGameRes();  //����������Ϸ�������ƵͼƬ��Դ�ļ�
	void DisplayTeam(Ref*);  //��ʾ�����Ŷ���Ϣ
	void GoToPlot_Level_0(Ref*);	//�������
	void GoToPlot_Level_1(Ref*);	//�������
	void GoToPlot_Level_2(Ref*);	//�������
	CREATE_FUNC(BeginScene);
private:
	int GameLevel; //��Ϸ�Ѷ�
};


#endif