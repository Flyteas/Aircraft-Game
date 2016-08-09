#include "BeginScene.h"
#include "PlotScene.h"
#include "TeamScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
Scene* BeginScene::CreateScene()
{
	auto Layer = BeginScene::create(); //创建层
	auto Scene = cocos2d::Scene::create(); //创建场景
	Scene->addChild(Layer);	//添加层到场景
	return Scene;
}

bool BeginScene::init()
{
	bool Result;
	if(!Layer::init())   
	{        
		return false; //初始化失败  
	}
	Result = LoadGameRes(); //载入资源文件
	if(!Result) //载入失败
	{
		return false;
	}
	/* 设置背景图片 */
	Size VisibleSize = Director::getInstance()->getVisibleSize(); //获取可视区域大小  
	Point VisibleOrigin = Director::getInstance()->getVisibleOrigin();  //获取可视区域原点位置
	auto Background_1 = Sprite::createWithSpriteFrameName("img_bg_level_4.jpg"); //创建背景精灵
	Background_1->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT); //设置位置,左下角位置
	Background_1->setScale(VisibleSize.width/Background_1->getContentSize().width);
	this->addChild(Background_1,-1,1); //添加背景

	/* 难度按钮 */ 
	// 点击按钮后转跳到剧情幕
	// 简单模式
	auto Level_0_Button = Sprite::createWithSpriteFrameName("level_0.png");
	auto Level_0_Button_Down = Sprite::createWithSpriteFrameName("level_0.png");
	auto MenuItemLevel_0_ = MenuItemSprite::create(Level_0_Button, Level_0_Button_Down,CC_CALLBACK_1(BeginScene::GoToPlot_Level_0, this));
	MenuItemLevel_0_->setScale((VisibleSize.width/1080)*3); //设置缩放倍数
	auto MenuLevel_0_ = Menu::create(MenuItemLevel_0_,NULL);
	MenuLevel_0_->setPosition(VisibleSize.width/2,VisibleSize.height*5/7);  //按钮位置
	this->addChild(MenuLevel_0_);
	//进阶模式
	auto Level_1_Button = Sprite::createWithSpriteFrameName("level_1.png");
	auto Level_1_Button_Down = Sprite::createWithSpriteFrameName("level_1.png");
	auto MenuItemLevel_1_ = MenuItemSprite::create(Level_1_Button, Level_1_Button_Down,CC_CALLBACK_1(BeginScene::GoToPlot_Level_1, this));
	MenuItemLevel_1_->setScale((VisibleSize.width/1080)*3); //设置缩放倍数
	auto MenuLevel_1_ = Menu::create(MenuItemLevel_1_,NULL);
	MenuLevel_1_->setPosition(VisibleSize.width/2,VisibleSize.height*4/7);  //按钮位置
	this->addChild(MenuLevel_1_);
	//地狱模式
	auto Level_2_Button = Sprite::createWithSpriteFrameName("level_2.png");
	auto Level_2_Button_Down = Sprite::createWithSpriteFrameName("level_2.png");
	auto MenuItemLevel_2_ = MenuItemSprite::create(Level_2_Button, Level_2_Button_Down,CC_CALLBACK_1(BeginScene::GoToPlot_Level_2, this));
	MenuItemLevel_2_->setScale((VisibleSize.width/1080)*3); //设置缩放倍数
	auto MenuLevel_2_ = Menu::create(MenuItemLevel_2_,NULL);
	MenuLevel_2_->setPosition(VisibleSize.width/2,VisibleSize.height*3/7);  //按钮位置
	this->addChild(MenuLevel_2_);

	/* 团队信息 */
	//点击按钮后显示制作团队
	 auto DisplayTeamButton = Sprite::createWithSpriteFrameName("teambtn.png");
	auto DisplayTeamButton_Down = Sprite::createWithSpriteFrameName("teambtn.png");
	auto MenuItemDisplayTeam = MenuItemSprite::create(DisplayTeamButton, DisplayTeamButton_Down,CC_CALLBACK_1(BeginScene::DisplayTeam, this));
	MenuItemDisplayTeam->setScale((VisibleSize.width/1080)*3); //设置缩放倍数
	auto MenuDisplayTeam = Menu::create(MenuItemDisplayTeam,NULL);
	MenuDisplayTeam->setPosition(VisibleSize.width/2,VisibleSize.height*2/7); //按钮位置
	this->addChild(MenuDisplayTeam);

	/* 设置背景音乐 */
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("res/audio/begin.mp3", true);
	
	return true;
}

bool BeginScene::LoadGameRes() //载入资源
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/backgroung1.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/plane.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/others.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/btn.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/shoot.plist");

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("res/audio/begin.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("res/audio/plot.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("res/audio/gamebackground.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("res/audio/ending.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("res/audio/copyright.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/audio/bullet.mp3");		
	SimpleAudioEngine::getInstance()->preloadEffect("res/audio/enemy1_down.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/audio/enemy2_down.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/audio/getprop.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/audio/gameover.mp3");
	return true;
}

void BeginScene::GoToPlot_Level_0(Ref*)
{
	GameLevel = 0;
	auto PlotScene_obj = PlotScene::CreateScene(GameLevel);//PlotScene::CreateScene();
	Director::getInstance()->replaceScene(PlotScene_obj);
}

void BeginScene::GoToPlot_Level_1(Ref*)
{
	GameLevel = 1;
	auto PlotScene_obj = PlotScene::CreateScene(GameLevel);//PlotScene::CreateScene();
	Director::getInstance()->replaceScene(PlotScene_obj);
}

void BeginScene::GoToPlot_Level_2(Ref*)
{
	GameLevel = 2;
	auto PlotScene_obj = PlotScene::CreateScene(GameLevel);//PlotScene::CreateScene();
	Director::getInstance()->replaceScene(PlotScene_obj);
}

void BeginScene::DisplayTeam(Ref*)
{
	auto TeamScene_obj = TeamScene::CreateScene();//PlotScene::CreateScene();
	Director::getInstance()->replaceScene(TeamScene_obj);
}