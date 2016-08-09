#include "cocos2d.h"
#include "PlotScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "tinyxml2\tinyxml2.h"
using namespace CocosDenshion;
Scene* PlotScene::CreateScene(int GameLevel)
{
	auto Layer = PlotScene::create(GameLevel); //创建层
	auto Scene = cocos2d::Scene::create(); //创建场景
	Scene->addChild(Layer);	//添加层到场景
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
		return false; //初始化失败  
	}
	this->GameLevel = GameLevelInput;
	this->PlotsData = this->LoadPlots();
	this->LableData = this->LoadEnterLabel();
	this->IsEnterEnable = false;
	/* 设置背景图片 */
	Size VisibleSize = Director::getInstance()->getVisibleSize(); //获取可视区域大小  
	Point VisibleOrigin = Director::getInstance()->getVisibleOrigin();  //获取可视区域原点位置
	auto Background_1 = Sprite::createWithSpriteFrameName("img_bg_level_4.jpg"); //创建背景精灵
	Background_1->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT); //设置位置,左下角位置
	this->addChild(Background_1,-1,1); //添加背景
	
	/* 添加剧情label */
	PlotTextLabel = Label::createWithSystemFont("", "Arial", 50);
	PlotTextLabel->setPosition(VisibleSize.width/2,VisibleSize.height*3/4);
	PlotTextLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	PlotTextLabel->setColor(Color3B::WHITE);
	//PlotTextLabel->setScale(this->ScaleNum); // 缩放
	this->addChild(PlotTextLabel, 99);	

	/* 添加进入提示label */
	EnterTextLabel = Label::createWithSystemFont("", "Arial", 50);
	EnterTextLabel->setPosition(VisibleSize.width/2,VisibleSize.height*1/4);
	EnterTextLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	EnterTextLabel->setColor(Color3B::WHITE);
	//PlotTextLabel->setScale(this->ScaleNum); // 缩放
	this->addChild(EnterTextLabel, 98);	


	schedule(schedule_selector(PlotScene::PlotDisplay),0.1f); //逐字显示

	/* 设置背景音乐 */
	SimpleAudioEngine::getInstance()->playBackgroundMusic("res/audio/plot.mp3", true);

	/* 触屏进入战斗 */
	auto TouchListener = EventListenerTouchOneByOne::create(); //单点触摸事件监听器
	TouchListener->onTouchBegan = [=](Touch* Touch_Obj,Event* e) //开始触摸 事件
	{

		return this->IsEnterEnable; //是否剧情已经结束
	};
	TouchListener->onTouchMoved = [](Touch* Touch_Obj,Event* e) //触摸移动 事件
	{
	
	};
	TouchListener->onTouchEnded = [=](Touch* Touch_Obj,Event* e) //触摸结束 事件
	{
		this->GameBegin();
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(TouchListener,this); //将UserPlane添加到事件监控器中

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