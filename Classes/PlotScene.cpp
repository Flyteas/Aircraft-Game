#include "cocos2d.h"
#include "PlotScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "tinyxml2\tinyxml2.h"
using namespace CocosDenshion;
Scene* PlotScene::CreateScene(int GameLevel)
{
	auto Layer = PlotScene::create(GameLevel); //������
	auto Scene = cocos2d::Scene::create(); //��������
	Scene->addChild(Layer);	//��Ӳ㵽����
	return Scene;
}

PlotScene* PlotScene::create(int GameLevel)
{
	auto PlotScene_obj = new PlotScene();
	if(PlotScene_obj!=NULL&&PlotScene_obj->init(GameLevel))
	{
		PlotScene_obj->autorelease();
		return PlotScene_obj;
	}
	delete PlotScene_obj;
	PlotScene_obj = NULL;
	return NULL;
}

bool PlotScene::init(int GameLevelInput)
{
	if(!Layer::init())   
	{        
		return false; //��ʼ��ʧ��  
	}
	this->GameLevel = GameLevelInput;
	this->PlotsData = this->LoadPlots();
	this->LableData = this->LoadEnterLabel();
	this->IsEnterEnable = false;
	/* ���ñ���ͼƬ */
	Size VisibleSize = Director::getInstance()->getVisibleSize(); //��ȡ���������С  
	Point VisibleOrigin = Director::getInstance()->getVisibleOrigin();  //��ȡ��������ԭ��λ��
	auto Background_1 = Sprite::createWithSpriteFrameName("img_bg_level_4.jpg"); //������������
	Background_1->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT); //����λ��,���½�λ��
	this->addChild(Background_1,-1,1); //��ӱ���
	
	/* ��Ӿ���label */
	PlotTextLabel = Label::createWithSystemFont("", "Arial", 50);
	PlotTextLabel->setPosition(VisibleSize.width/2,VisibleSize.height*3/4);
	PlotTextLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	PlotTextLabel->setColor(Color3B::WHITE);
	//PlotTextLabel->setScale(this->ScaleNum); // ����
	this->addChild(PlotTextLabel, 99);	

	/* ��ӽ�����ʾlabel */
	EnterTextLabel = Label::createWithSystemFont("", "Arial", 50);
	EnterTextLabel->setPosition(VisibleSize.width/2,VisibleSize.height*1/4);
	EnterTextLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	EnterTextLabel->setColor(Color3B::WHITE);
	//PlotTextLabel->setScale(this->ScaleNum); // ����
	this->addChild(EnterTextLabel, 98);	


	schedule(schedule_selector(PlotScene::PlotDisplay),0.1f); //������ʾ

	/* ���ñ������� */
	SimpleAudioEngine::getInstance()->playBackgroundMusic("res/audio/plot.mp3", true);

	/* ��������ս�� */
	auto TouchListener = EventListenerTouchOneByOne::create(); //���㴥���¼�������
	TouchListener->onTouchBegan = [=](Touch* Touch_Obj,Event* e) //��ʼ���� �¼�
	{

		return this->IsEnterEnable; //�Ƿ�����Ѿ�����
	};
	TouchListener->onTouchMoved = [](Touch* Touch_Obj,Event* e) //�����ƶ� �¼�
	{
	
	};
	TouchListener->onTouchEnded = [=](Touch* Touch_Obj,Event* e) //�������� �¼�
	{
		this->GameBegin();
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(TouchListener,this); //��UserPlane��ӵ��¼��������

	return true;
}

void PlotScene::GameBegin()
{
	auto GameScene_obj = MainScene::CreateScene(this->GameLevel);
	Director::getInstance()->replaceScene(GameScene_obj);
}

std::string PlotScene::LoadPlots()
{
	auto doc =new tinyxml2::XMLDocument();
	doc->Parse(FileUtils::getInstance()->getStringFromFile("res/data.xml").c_str()); 
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

std::string PlotScene::LoadEnterLabel()
{
	auto doc =new tinyxml2::XMLDocument();
	doc->Parse(FileUtils::getInstance()->getStringFromFile("res/labeldata.xml").c_str()); 
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

void PlotScene::PlotDisplay(float)
{
	if(this->PlotsDataTemp.length() >= this->PlotsData.length())
	{
		if(this->LableDataTemp.length() >= this->LableData.length())
		{
			this->IsEnterEnable =true;
			this->LableDataTemp.clear();
		}
		else
		{
			this->LableDataTemp = this->LableData.substr(0,LableDataTemp.length()+1);
			EnterTextLabel->setString(this->LableDataTemp);
		}
		return;
	}
	this->PlotsDataTemp = this->PlotsData.substr(0,PlotsDataTemp.length()+2);
	PlotTextLabel->setString(this->PlotsDataTemp);
}