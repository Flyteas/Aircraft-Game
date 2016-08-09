#include "cocos2d.h"
#include "TeamScene.h"
#include "BeginScene.h"
#include "SimpleAudioEngine.h"
#include "tinyxml2\tinyxml2.h"
using namespace CocosDenshion;
Scene* TeamScene::CreateScene()
{
	auto Layer = TeamScene::create(); //������
	auto Scene = cocos2d::Scene::create(); //��������
	Scene->addChild(Layer);	//��Ӳ㵽����
	return Scene;
}

bool TeamScene::init()
{
	if(!Layer::init())   
	{        
		return false; //��ʼ��ʧ��  
	}
	this->Datas = this->LoadData();
	/* ���ñ���ͼƬ */
	Size VisibleSize = Director::getInstance()->getVisibleSize(); //��ȡ���������С  
	Point VisibleOrigin = Director::getInstance()->getVisibleOrigin();  //��ȡ��������ԭ��λ��
	auto Background_1 = Sprite::createWithSpriteFrameName("img_bg_level_4.jpg"); //������������
	Background_1->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT); //����λ��,���½�λ��
	this->addChild(Background_1,-1,1); //��ӱ���
	
	/* ��Ӿ���label */
	DataTextLabel = Label::createWithSystemFont("", "Arial", 50); 
	DataTextLabel->setPosition(VisibleSize.width/2,VisibleSize.height*3/4);
	DataTextLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	DataTextLabel->setColor(Color3B::WHITE);
	//DataTextLabel->setScale(this->ScaleNum); //���ϽǷ�����ʾ ����
	this->addChild(DataTextLabel, 99);	
	schedule(schedule_selector(TeamScene::DataDisplay),0.2f); //������ʾ

	/* ���ñ������� */
	SimpleAudioEngine::getInstance()->playBackgroundMusic("res/audio/copyright.mp3", true);

	/* ���ذ�ť */ 
	// �����ť�󷵻����˵�
	auto ReturnButton = Sprite::createWithSpriteFrameName("returnmenubtn.png");
	auto ReturnButton_Down = Sprite::createWithSpriteFrameName("returnmenubtn.png");
	auto MenuItemReturn = MenuItemSprite::create(ReturnButton, ReturnButton_Down,CC_CALLBACK_1(TeamScene::ReturnBegin, this));
	MenuItemReturn->setScale((VisibleSize.width/1080)*3); //�������ű���
	auto MenuReturn = Menu::create(MenuItemReturn,NULL);
	MenuReturn->setPosition(VisibleSize.width/2,VisibleSize.height/4);  //��ťλ��
	this->addChild(MenuReturn);



	return true;
}

void TeamScene::ReturnBegin(Ref*)
{
	auto BeginScene_obj = BeginScene::CreateScene();
	Director::getInstance()->replaceScene(BeginScene_obj);
}

std::string TeamScene::LoadData()
{
	auto doc =new tinyxml2::XMLDocument();
	doc->Parse(FileUtils::getInstance()->getStringFromFile("res/team.xml").c_str()); 
	auto root=doc->RootElement();
	std::string str;
	for (auto e=root->FirstChildElement(); e; e=e->NextSiblingElement()) 
	{
		for (auto attr=e->FirstAttribute(); attr; attr=attr->Next()) 
		{
			str+=attr->Value();
		}
	}
	return str;
}

void TeamScene::DataDisplay(float)
{
	if(this->DatasTemp.length() >= this->Datas.length())
	{
		return;
	}
	this->DatasTemp = this->Datas.substr(0,DatasTemp.length()+2);
	DataTextLabel->setString(this->DatasTemp);
}