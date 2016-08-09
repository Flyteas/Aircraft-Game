#include "EndScene.h"
#include "BeginScene.h"
#include "SimpleAudioEngine.h"
#include <algorithm>
using namespace CocosDenshion;
USING_NS_CC;
EndScene* EndScene::create(int Score_Input)
{
	auto EndScene_obj = new EndScene();
	if(EndScene_obj!=NULL&&EndScene_obj->init(Score_Input))
	{
		EndScene_obj->autorelease();
		return EndScene_obj;
	}
	delete EndScene_obj;
	EndScene_obj = NULL;
	return NULL;
}

Scene* EndScene::CreateScene(int Score_Input)
{
	auto Layer_obj = EndScene::create(Score_Input);
	auto Scene_obj = Scene::create();
	Scene_obj->addChild(Layer_obj);
	return Scene_obj;
}

bool EndScene::init(int Score_Input)
{
	if(!Layer::init())   
	{        
		return false; //��ʼ��ʧ��  
	}
	this->Final_Score = Score_Input;
	/* ���뱳��ͼƬ */
	Size VisibleSize = Director::getInstance()->getVisibleSize(); //��ȡ���������С  
	auto Background_1 = Sprite::createWithSpriteFrameName("img_bg_level_2.jpg"); //������������
	Background_1->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT); //����λ��,���½�λ��
	Background_1->setScale(VisibleSize.width/Background_1->getContentSize().width);
	this->addChild(Background_1,-1,1); //��ӱ���



	/* ���÷�����ʾ */
	auto ScoreTextLabel = Label::createWithSystemFont("Game Score", "Arial", 36); 
	ScoreTextLabel->setPosition(VisibleSize.width/2,VisibleSize.height*6/7);
	ScoreTextLabel->setColor(Color3B::WHITE);
	ScoreTextLabel->setScale((VisibleSize.width/1080)*2.5); //����
	this->addChild(ScoreTextLabel, 99);
	auto ScoreLabel = Label::createWithBMFont("fonts/font.fnt", "0");
	ScoreLabel->setPosition(ScoreTextLabel->getPositionX(), VisibleSize.height*6/7-100);
	ScoreLabel->setColor(Color3B::WHITE);
	ScoreLabel->setScale((VisibleSize.width/1080)*2.5); //����
	ScoreLabel->setString(StringUtils::format("%d", Final_Score));
	this->addChild(ScoreLabel, 99, 89);
	auto RankTextLabel = Label::createWithSystemFont("Score Rank", "Arial", 36); 
	RankTextLabel->setPosition(VisibleSize.width/2,VisibleSize.height*6/7-300);
	RankTextLabel->setColor(Color3B(120, 120, 120));
	RankTextLabel->setScale((VisibleSize.width/1080)*2.5); //����
	this->addChild(RankTextLabel, 99);
	
	//�������ļ��ж�ȡǰ�����÷֣����û���򷵻�Ĭ��ֵ0
	int Score_1st,Score_2nd,Score_3rd;
	Score_1st = UserDefault::getInstance()->getIntegerForKey("Score_1st");
	Score_2nd = UserDefault::getInstance()->getIntegerForKey("Score_2nd");
	Score_3rd = UserDefault::getInstance()->getIntegerForKey("Score_3rd");

	auto Score_History_Label_1 = Label::createWithBMFont("fonts/font.fnt","");
	Score_History_Label_1->setScale((VisibleSize.width/1080)*4);
	Score_History_Label_1->setPosition(Director::getInstance()->getVisibleSize().width/2, VisibleSize.height*6/10+50);
	this->addChild(Score_History_Label_1);
	Score_History_Label_1->setColor(Color3B(120, 120, 120));

	auto Score_History_Label_2 = Label::createWithBMFont("fonts/font.fnt","");
	Score_History_Label_2->setScale((VisibleSize.width/1080)*2);
	Score_History_Label_2->setPosition(Director::getInstance()->getVisibleSize().width/2, VisibleSize.height*5/10+100);
	this->addChild(Score_History_Label_2);
	Score_History_Label_2->setColor(Color3B(120, 120, 120));

	auto Score_History_Label_3 = Label::createWithBMFont("fonts/font.fnt","");
	Score_History_Label_3->setScale((VisibleSize.width/1080)*4);
	Score_History_Label_3->setPosition(Director::getInstance()->getVisibleSize().width/2, VisibleSize.height*4/10+200);
	this->addChild(Score_History_Label_3);
	Score_History_Label_3->setColor(Color3B(120, 120, 120));

	ScoreList[0] = Score_1st;
	ScoreList[1] = Score_2nd;
	ScoreList[2] = Score_3rd;
	ScoreList[3] = Score_Input;
	//��ScoreList�еķ������н�������
	int ex;
	for (int i = 0; i < 4; i++)  
    {  
		for (int j = i + 1; j < 4; j++)  
		{  
			if (ScoreList[i]<ScoreList[j])  
				{  
					ex=ScoreList[i];
				    ScoreList[i]=ScoreList[j];
					ScoreList[j]=ex; 
                }  
		}  
	}  

	//д���ļ�
	UserDefault::getInstance()->setIntegerForKey("Score_1st",ScoreList[0]);
	UserDefault::getInstance()->setIntegerForKey("Score_2nd",ScoreList[1]);
	UserDefault::getInstance()->setIntegerForKey("Score_3rd",ScoreList[2]);
	Score_History_Label_1->setString(StringUtils::format("%d", ScoreList[0]));
	Score_History_Label_2->setString(StringUtils::format("%d",ScoreList[1]));
	Score_History_Label_3->setString(StringUtils::format("%d", ScoreList[2]));
	auto scaleIn = ScaleTo::create(0.5f, 1.3f);
	auto scaleOut = ScaleTo::create(0.5f, 1.3f);
	Score_History_Label_1->runAction(Sequence::create(scaleIn, scaleOut, NULL));
	Score_History_Label_2->runAction(Sequence::create(scaleIn, scaleOut, NULL));
	Score_History_Label_3->runAction(Sequence::create(scaleIn, scaleOut, NULL));


	/* ���¿�ʼ��ť */
	auto RestartButton = Sprite::createWithSpriteFrameName("restartbtn.png");
	auto RestartButton_Down = Sprite::createWithSpriteFrameName("restartbtn.png");
	auto MenuItemRestart = MenuItemSprite::create(RestartButton, RestartButton_Down,CC_CALLBACK_1(EndScene::RestartGame, this));
	MenuItemRestart->setScale((VisibleSize.width/1080)*3); //�������ű���
	auto MenuRestart = Menu::create(MenuItemRestart,NULL);
	MenuRestart->setPosition(VisibleSize.width/2,VisibleSize.height*2/7);  //��ťλ��
	this->addChild(MenuRestart);

	/* ���ñ������� */
	SimpleAudioEngine::getInstance()->playBackgroundMusic("res/audio/ending.mp3", true);

	return true;
}


void EndScene::RestartGame(Ref*)
{
	auto MainScene_obj = BeginScene::CreateScene();
	Director::getInstance()->replaceScene(MainScene_obj);
}