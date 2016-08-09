#include "cocos2d.h"
#include "TeamScene.h"
#include "BeginScene.h"
#include "SimpleAudioEngine.h"
#include "tinyxml2\tinyxml2.h"
using namespace CocosDenshion;
Scene* TeamScene::CreateScene()
{
	auto Layer = TeamScene::create(); //创建层
	auto Scene = cocos2d::Scene::create(); //创建场景
	Scene->addChild(Layer);	//添加层到场景
	return Scene;
}

bool TeamScene::init()
{
	if(!Layer::init())   
	{        
		return false; //初始化失败  
	}
	this->Datas = this->LoadData();
	/* 设置背景图片 */
	Size VisibleSize = Director::getInstance()->getVisibleSize(); //获取可视区域大小  
	Point VisibleOrigin = Director::getInstance()->getVisibleOrigin();  //获取可视区域原点位置
	auto Background_1 = Sprite::createWithSpriteFrameName("img_bg_level_4.jpg"); //创建背景精灵
	Background_1->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT); //设置位置,左下角位置
	this->addChild(Background_1,-1,1); //添加背景
	
	/* 添加剧情label */
	DataTextLabel = Label::createWithSystemFont("", "Arial", 50); 
	DataTextLabel->setPosition(VisibleSize.width/2,VisibleSize.height*3/4);
	DataTextLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	DataTextLabel->setColor(Color3B::WHITE);
	//DataTextLabel->setScale(this->ScaleNum); //左上角分数显示 缩放
	this->addChild(DataTextLabel, 99);	
	schedule(schedule_selector(TeamScene::DataDisplay),0.2f); //逐字显示

	/* 设置背景音乐 */
	SimpleAudioEngine::getInstance()->playBackgroundMusic("res/audio/copyright.mp3", true);

	/* 返回按钮 */ 
	// 点击按钮后返回主菜单
	auto ReturnButton = Sprite::createWithSpriteFrameName("returnmenubtn.png");
	auto ReturnButton_Down = Sprite::createWithSpriteFrameName("returnmenubtn.png");
	auto MenuItemReturn = MenuItemSprite::create(ReturnButton, ReturnButton_Down,CC_CALLBACK_1(TeamScene::ReturnBegin, this));
	MenuItemReturn->setScale((VisibleSize.width/1080)*3); //设置缩放倍数
	auto MenuReturn = Menu::create(MenuItemReturn,NULL);
	MenuReturn->setPosition(VisibleSize.width/2,VisibleSize.height/4);  //按钮位置
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