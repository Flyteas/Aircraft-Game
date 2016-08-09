/* Version 0.9 */
/* Flyshit 2015.8.29 */
/* Mail to: Flyshit@cqu.edu.cn */

#include "MainScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

MainScene::MainScene()
{
	/* 初始化数据 */
	Touch_Point_Offset = Point(0,0);
	this->Score_Now = 0;
	this->UserHp = 2;
	this->Now_User_Bullets_Type = Yellow_Double;  //设置子弹类型
	this->IsGamePause = false;
}

MainScene* MainScene::create(int GameLevel)
{
	auto MainScene_obj = new MainScene();
	if(MainScene_obj!=NULL&&MainScene_obj->init(GameLevel))
	{
		MainScene_obj->autorelease();
		return MainScene_obj;
	}
	delete MainScene_obj;
	MainScene_obj = NULL;
	return NULL;
}

Scene* MainScene::CreateScene(int GameLevel)	//主界面层创建函数
{
	auto Layer = MainScene::create(GameLevel); //创建层
	auto Scene = cocos2d::Scene::create(); //创建场景
	Scene->addChild(Layer);	//添加层到场景
	return Scene;
}

bool MainScene::init(int GameLevelInput)	//初始化函数
{
	if(!Layer::init())   
	{        
		return false; //初始化失败  
	}   
	this->GameLevel = GameLevelInput;
	Sprite* Background_1;
	Sprite* Background_2;

	/* 初始化难度设置 */
	switch (this->GameLevel)
	{
	case 0:
		Background_1 = Sprite::createWithSpriteFrameName("img_bg_level_3.jpg"); //创建背景精灵
		Background_2 = Sprite::createWithSpriteFrameName("img_bg_level_3.jpg");
		schedule(schedule_selector(MainScene::Small_Enemy_Plane_Create), 18, -1, 3);
		schedule(schedule_selector(MainScene::Middle_Enemy_Plane_Create), 25, -1, 6);
		schedule(schedule_selector(MainScene::Big_Enemy_Plane_Create),50, -1, 8);
		break;
	case 1:
		Background_1 = Sprite::createWithSpriteFrameName("img_bg_level_4.jpg"); //创建背景精灵
		Background_2 = Sprite::createWithSpriteFrameName("img_bg_level_4.jpg");
		schedule(schedule_selector(MainScene::Small_Enemy_Plane_Create), 10, -1, 3);
		schedule(schedule_selector(MainScene::Middle_Enemy_Plane_Create), 15, -1, 6);
		schedule(schedule_selector(MainScene::Big_Enemy_Plane_Create),25, -1, 8);
		break;
	case 2:
		Background_1 = Sprite::createWithSpriteFrameName("img_bg_level_5.jpg"); //创建背景精灵
		Background_2 = Sprite::createWithSpriteFrameName("img_bg_level_5.jpg");
		schedule(schedule_selector(MainScene::Small_Enemy_Plane_Create), 5, -1, 2);
		schedule(schedule_selector(MainScene::Middle_Enemy_Plane_Create), 10, -1, 3);
		schedule(schedule_selector(MainScene::Big_Enemy_Plane_Create),15, -1, 8);
		break;
	}
	/* 设置战斗背景 */
	Size VisibleSize = Director::getInstance()->getVisibleSize(); //获取可视区域大小  
	Point VisibleOrigin = Director::getInstance()->getVisibleOrigin();  //获取可视区域原点位置
	//auto Background_1 = Sprite::createWithSpriteFrameName("img_bg_level_4.jpg"); //创建背景精灵
	this->ScaleNum = VisibleSize.width/Background_1->getContentSize().width; //计算缩放倍数
	Background_1->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT); //设置位置,左下角位置
	Background_1->setScale(this->ScaleNum); //背景 缩放
	this->addChild(Background_1,-1,1); //添加背景
	//auto Background_2 = Sprite::createWithSpriteFrameName("img_bg_level_4.jpg");
	Background_2->getTexture()->setAliasTexParameters(); //开启抗锯齿
	Background_2->setScale(this->ScaleNum); //背景 缩放
	this->addChild(Background_2,-1,2);
	Background_2->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT); //左下角位置
	
	/* 设置用户飞机 */
	UserPlane = Sprite::createWithSpriteFrameName("userplane.png");
	UserPlane->setPosition(VisibleSize.width/2+VisibleOrigin.x,UserPlane->getContentSize().height/2); //设置用户飞机初始位置
	UserPlane->setScale(this->ScaleNum); //用户飞机 缩放
	this->addChild(UserPlane,3,3); //用户飞机精灵优先级为3，tag为3
	auto UserPlaneAnimation = Animation::create(); //创建用户飞机动画对象
	UserPlaneAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("userplane.png")); //为用户飞机动画对象添加帧
	UserPlaneAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("userplane.png"));
	UserPlaneAnimation->setDelayPerUnit(0.25); //动画刷新时间间隔
	UserPlaneAnimation->setLoops(-1); //设置动画播放次数，-1为无限次，0为不播放
	auto UserPlaneAnimate = Animate::create(UserPlaneAnimation); //根据用户飞机动画对象创建动画动作
	UserPlane->runAction(UserPlaneAnimate); //执行用户飞机动作

	/* 设置分数显示 */
	auto ScoreTextLabel = Label::createWithSystemFont("Score:", "Arial", 36);
	ScoreTextLabel->setPosition(0, VisibleSize.height-45);
	ScoreTextLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	ScoreTextLabel->setColor(Color3B::WHITE);
	ScoreTextLabel->setScale(this->ScaleNum); //左上角分数显示 缩放
	this->addChild(ScoreTextLabel, 99);	//设置字体颜色
	auto ScoreLabel = Label::createWithBMFont("fonts/font.fnt", "0");
	ScoreLabel->setPosition(ScoreTextLabel->getContentSize().width + 39, VisibleSize.height-45);
	ScoreLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	ScoreLabel->setColor(Color3B::WHITE);
	ScoreLabel->setScale(this->ScaleNum); //左上角分数显示 缩放
	this->addChild(ScoreLabel, 99, 90);

	/* 设置生命值显示 */
	auto HPTextLabel = Label::createWithSystemFont("HP:", "Arial", 40);
	HPTextLabel->setPosition(910, 0);
	HPTextLabel->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	HPTextLabel->setColor(Color3B::WHITE);
	HPTextLabel->setScale(this->ScaleNum); //右下角生命值显示 缩放
	this->addChild(HPTextLabel, 99);	//设置字体颜色
	auto HPLabel = Label::createWithBMFont("fonts/font.fnt", "0");
	HPLabel->setPosition(HPTextLabel->getContentSize().width + 950,10);
	HPLabel->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	HPLabel->setColor(Color3B::WHITE);
	HPLabel->setScale(this->ScaleNum); //右下角生命值显示 缩放
	this->addChild(HPLabel, 99, 91);

	/* 设置暂停按钮 */
	auto Pause_Button = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	auto Pause_Button_Pressed = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	auto Pause_Button_MenuItem = MenuItemSprite::create(Pause_Button, Pause_Button_Pressed, CC_CALLBACK_1(MainScene::GamePause, this));
	Pause_Button_MenuItem->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	Pause_Button_MenuItem->setPosition(0,0);
	Pause_Button_MenuItem->setTag(120);
	this->addChild(Pause_Button);

	/* 设置继续按钮 */
	auto Resume_Button = Sprite::createWithSpriteFrameName("game_resume_nor.png");
	auto Resume_Button_Pressed = Sprite::createWithSpriteFrameName("game_resume_pressed.png");
	auto Resume_Button_MenuItem = MenuItemSprite::create(Resume_Button, Resume_Button_Pressed, CC_CALLBACK_1(MainScene::GameResume, this));
	Resume_Button_MenuItem->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	Resume_Button_MenuItem->setPosition(0,0);
	Resume_Button_MenuItem->setVisible(false);
	Resume_Button_MenuItem->setTag(121);
	this->addChild(Resume_Button);

	/* 添加按钮组 */
	auto GameMenu = Menu::create(Pause_Button_MenuItem,Resume_Button_MenuItem,NULL);
	GameMenu->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	GameMenu->setPosition(0,0);
	this->addChild(GameMenu,99,119);
	/* 预缓存动画资源 */
	this->PrepareAnimation();

	/* 设置背景音乐 */
	SimpleAudioEngine::getInstance()->playBackgroundMusic("res/audio/gamebackground.mp3", true);


	/* 飞机移动 */
	auto TouchListener = EventListenerTouchOneByOne::create(); //单点触摸事件监听器
	TouchListener->onTouchBegan = [=](Touch* Touch_Obj,Event* e) //开始触摸 事件
	{
		if(!UserPlane->getBoundingBox().containsPoint(Touch_Obj->getLocation())) //判断触摸点是否位于用户飞机范围内
		{
			return false; //不在范围内，返回false，不执行接下来的事件
		}
		Touch_Point_Offset = Touch_Obj->getLocation() - UserPlane->getPosition();
		return !this->IsGamePause;
	};
	TouchListener->onTouchMoved = [=](Touch* Touch_Obj,Event* e) //触摸移动 事件
	{
		Point PlaneNowPos = Touch_Obj->getLocation() - Touch_Point_Offset; //飞机未判定边界前的位置
		Point UserPlaneNextPos; //判定边界后的位置
		UserPlaneNextPos.x = MIN(MAX(UserPlane->getContentSize().width/2,PlaneNowPos.x),VisibleSize.width + VisibleOrigin.x - UserPlane->getContentSize().width/2); //X轴边界限制
		UserPlaneNextPos.y = MIN(MAX(UserPlane->getContentSize().height/2,PlaneNowPos.y),VisibleSize.height + VisibleOrigin.y - UserPlane->getContentSize().width/2); //Y轴边界限制
		UserPlane->setPosition(UserPlaneNextPos); //移动飞机
	};
	TouchListener->onTouchEnded = [](Touch* Touch_Obj,Event* e) //触摸结束 事件
	{

	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(TouchListener,UserPlane); //将UserPlane添加到事件监控器中
	
	/* 子弹发射 */
	schedule(schedule_selector(MainScene::BulletCreate),0.2f); //子弹发射定时器
	schedule(schedule_selector(MainScene::EnemyBulletCreate),1); //敌机子弹发射定时器
	scheduleUpdate(); //帧刷新定时器
	return true;
}

void MainScene::update(float)
{
	Vector<Bullets*> Bullets_Del_Vec; //待删除子弹集合
	Vector<Bullets*> Enemy_Bullet_Del_Vec; //待删除敌机子弹集合
	Vector<Enemy_Plane*> Enemy_Del_Vec; //待删除敌机
	Vector<Props*> Props_Del_Vec; //待删除道具集合
	auto Background_1 = this->getChildByTag(1); //获取背景1
	auto Background_2 = this->getChildByTag(2); //获取背景2
	Background_1->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	Background_2->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	Background_1->setPositionY(Background_1->getPositionY()-3);  //每帧下滚3像素
	Background_2->setPositionY(Background_1->getPositionY()+Background_1->getContentSize().height); //衔接两幅背景填充黑边
	if(Background_2->getPositionY() <= 0) //背景2到达底部
	{
		Background_1->setPositionY(0); //重置背景
	}

	/* 子弹与敌机碰撞检测 */
	for(auto Bullet:Bullets_Vec)
	{	
		for(auto Enemy:Enemy_Vec)
		{
			if(Enemy->getBoundingBox().intersectsRect(Bullet->getBoundingBox()))
			{
				Bullets_Del_Vec.pushBack(Bullet);
				if(Enemy->Hp<=0)
				{
					Enemy_Del_Vec.pushBack(Enemy);
					if(Enemy->Type == Big_Enemy_Plane) //如果是大敌机，则出现道具
					{
						SimpleAudioEngine::getInstance()->playEffect("res/audio/enemy2_down.mp3", false);
						int PropType = this->GetRand()%4;
						this->CreateProp((Prop_Type)PropType,Enemy->getPosition());
					}
					else
					{
						SimpleAudioEngine::getInstance()->playEffect("res/audio/enemy1_down.mp3", false);
					}
					this->Score_Now += Enemy->hitted(Bullet);
				}
				else
				{
					Enemy->hitted(Bullet);
				}
				this->removeChild(Bullet);
			}
		}
		/* 清除一次无效敌机 */
		for(auto Enemy:Enemy_Del_Vec)
		{
			this->Enemy_Vec.eraseObject(Enemy,true);
		}
		Enemy_Del_Vec.clear();
		
	}
	/* 清除一次无效子弹 */
	for(auto Bullet:Bullets_Del_Vec)
	{
		Bullets_Vec.eraseObject(Bullet,true);
	}
	Bullets_Del_Vec.clear();

	/* 敌机子弹与用户飞机碰撞检测 */
	for(auto Enemy_Bullet:this->Enemy_Bullet_Vec)
	{
		if(Enemy_Bullet->getBoundingBox().intersectsRect(UserPlane->getBoundingBox())) //打到用户飞机
		{
			this->UserHp--;
			Enemy_Bullet_Del_Vec.pushBack(Enemy_Bullet);
			if(this->UserHp <=0)
			{
				this->GoToGameOver();
			}
			this->removeChild(Enemy_Bullet);
		}
	}

	/* 清除一次无效敌机子弹 */
	for(auto Enemy_Bullet:Enemy_Bullet_Del_Vec)
	{
		Enemy_Bullet_Vec.eraseObject(Enemy_Bullet,true);
	}
	Enemy_Bullet_Del_Vec.clear();


	/* 敌机与用户飞机碰撞检测 */
	for(auto Enemy:Enemy_Vec)
	{
		if(Enemy->getBoundingBox().intersectsRect(UserPlane->getBoundingBox()))
		{
			this->UserHp--;
			Enemy_Del_Vec.pushBack(Enemy);
			if(Enemy->Type == Big_Enemy_Plane) //如果是大敌机，则出现道具
			{
				int PropType = this->GetRand()%4;
				this->CreateProp((Prop_Type)PropType,Enemy->getPosition());
			}
			this->Score_Now += Enemy->dead();
			if(this->UserHp <=0 )
			{
				this->GoToGameOver();
			}
		}
	}

	/* 清除一次无效敌机 */
	for(auto Enemy:Enemy_Del_Vec)
	{
		this->Enemy_Vec.eraseObject(Enemy,true);
	}
	Enemy_Del_Vec.clear();

	/* 道具与用户飞机碰撞检测 */
	for(auto Prop:Props_Vec)
	{
		if(Prop->getBoundingBox().intersectsRect(UserPlane->getBoundingBox()))
		{
			switch (Prop->Type)
			{
			case Bullet_Change:
				{
					int LastType = (int)this->Now_User_Bullets_Type;
					if(LastType >= 3)
					{
						Now_User_Bullets_Type = (Bullets_Type)0;
					}
					else
					{
						Now_User_Bullets_Type = (Bullets_Type)(++LastType);
					}
					break;
				}
			case HP_Add:
				this->UserHp++;
				break;
			case Enemy_Clear:
				this->ClearAllEnemy();
				break;
			case Defense_Buff:
				this->UserHp++;  //加血加得多
				break;
			}
			Props_Del_Vec.pushBack(Prop);
			this->removeChild(Prop);
			SimpleAudioEngine::getInstance()->playEffect("res/audio/getprop.mp3", false);
		}
	}
	/* 清除一次无效道具 */
	for(auto Prop:Props_Del_Vec)
	{
		this->Props_Vec.eraseObject(Prop);
	}
	Props_Del_Vec.clear();

	/* 子弹移动 */
	for(auto Bullet:Bullets_Vec)
	{
		switch (Bullet->Direction_Type) //判断子弹飞行方向
		{
		case 0:
			Bullet->setPosition(Bullet->getPositionX() - 6,Bullet->getPositionY() + 15);
			break;
		case 1:
			Bullet->setPositionY(Bullet->getPositionY() + 15);
			break;
		case 2:
			Bullet->setPosition(Bullet->getPositionX() + 6,Bullet->getPositionY() + 15);
			break;
		}
		if(Bullet->getPositionY() >= Director::getInstance()->getVisibleSize().height + Bullet->getContentSize().height/2 || Bullet->getPositionX() <= -Bullet->getContentSize().width/2 || Bullet->getPositionX() >= Director::getInstance()->getVisibleSize().width + Bullet->getContentSize().width/2) //判断子弹是否越出边界
		{
			Bullets_Del_Vec.pushBack(Bullet); //记录待删除子弹指针
			this->removeChild(Bullet); //删除子弹
		}
	}


	/* 清除一次无效子弹 */
	for(auto Bullet:Bullets_Del_Vec)
	{
		Bullets_Vec.eraseObject(Bullet,true);
	}
	Bullets_Del_Vec.clear();

	/* 敌机子弹移动 */
	for(auto Enemy_Bullet:this->Enemy_Bullet_Vec)
	{
		Enemy_Bullet->setPositionY(Enemy_Bullet->getPositionY() - 8);
		if(Enemy_Bullet->getPositionY() <=  Enemy_Bullet->getContentSize().height/2) //判断子弹是否越出边界
		{
			Enemy_Bullet_Del_Vec.pushBack(Enemy_Bullet); //记录待删除子弹指针
			this->removeChild(Enemy_Bullet); //删除子弹
		}
	}

	/* 清除一次无效敌机子弹 */
	for(auto Enemy_Bullet:Enemy_Bullet_Del_Vec)
	{
		Enemy_Bullet_Vec.eraseObject(Enemy_Bullet,true);
	}
	Enemy_Bullet_Del_Vec.clear();

	/* 敌机移动 */
	for(auto Enemy:Enemy_Vec)
	{
		if(Enemy->Type == Big_Enemy_Plane && Enemy->getPositionY() <= (Director::getInstance()->getVisibleSize().height - Enemy->getContentSize().height/2)) //BOSS飞机平移
		{
			if(Enemy->getPositionX() <= Enemy->getContentSize().width/2 || Enemy->getPositionX() >= (Director::getInstance()->getVisibleSize().width - Enemy->getContentSize().width/2))
			{
				Enemy->Step_Length = -Enemy->Step_Length;
			}
			Enemy->setPositionX(Enemy->getPositionX() + Enemy->Step_Length);
			for(auto Enemy_Enum:Enemy_Vec) //判断移动到的位置是否有飞机，有的话就回到原位置
			{
				if(Enemy == Enemy_Enum)
				{
					continue;
				}
				if(Enemy->getBoundingBox().intersectsRect(Enemy_Enum->getBoundingBox())) //存在飞机
				{
					Enemy->setPositionX(Enemy->getPositionX() - Enemy->Step_Length);
					break;
				}
			}
			continue;
		}
		Enemy->setPositionY(Enemy->getPositionY() - Enemy->Step_Length);
		for(auto Enemy_Enum:Enemy_Vec) //判断移动到的位置是否有飞机，有的话就回到原位置
		{
			if(Enemy == Enemy_Enum)
			{
				continue;
			}
			if(Enemy->getBoundingBox().intersectsRect(Enemy_Enum->getBoundingBox())) //存在飞机
			{
				Enemy->setPositionX(Enemy->getPositionX() - Enemy->Step_Length);
				break;
			}
		}
		if(Enemy->getPositionY() <= Enemy->getContentSize().height/2)
		{
			Enemy_Del_Vec.pushBack(Enemy);
			this->removeChild(Enemy);
		}
	}

	/* 清除一次无效敌机 */
	for(auto Enemy:Enemy_Del_Vec)
	{
		this->Enemy_Vec.eraseObject(Enemy,true);
	}
	Enemy_Del_Vec.clear();

	/* 道具移动 */
	for(auto Prop:Props_Vec )
	{
		Prop->setPositionY(Prop->getPositionY() - 15);
		if(Prop->getPositionY() <= Prop->getContentSize().height/2) //出界删除
		{
			Props_Del_Vec.pushBack(Prop);
			this->removeChild(Prop);
		}
	}

	/* 清除一次无效道具 */
	for(auto Prop:Props_Del_Vec)
	{
		this->Props_Vec.eraseObject(Prop);
	}
	Props_Del_Vec.clear();


	/* 显示控件数据更新 */
	auto ScoreLabelDis = (Label *) this->getChildByTag(90);
	auto HPLabelDis = (Label *) this->getChildByTag(91);
	ScoreLabelDis->setString(StringUtils::format("%d", this->Score_Now)); //更新分数显示
	HPLabelDis->setString(StringUtils::format("%d", this->UserHp)); //更新分数显示

}

void MainScene::BulletCreate(float)
{
	auto UserPlane = this->getChildByTag(3); //获取用户飞机
	SimpleAudioEngine::getInstance()->playEffect("/res/audio/bullet.mp3",false);
	Bullets* bullet;
	switch (this->Now_User_Bullets_Type)	//根据子弹类型创建子弹
	{
	case Blue_Single: //蓝色单发
	case Yellow_Single: //黄色单发
		bullet = Bullets::BulletsCreate(Now_User_Bullets_Type,1);
		bullet->setPosition(UserPlane->getPosition().x,UserPlane->getPosition().y + UserPlane->getContentSize().height/2 + bullet->getContentSize().height/2);
		bullet->setScale(this->ScaleNum); //单发子弹 缩放
		this->addChild(bullet,2); //优先级为2
		Bullets_Vec.pushBack(bullet);
		break;
	case Blue_Double: //蓝色双发
	case Yellow_Double: //黄色双发
		bullet = Bullets::BulletsCreate(Now_User_Bullets_Type,0);
		bullet->setPosition(UserPlane->getPosition().x - UserPlane->getContentSize().width/9,UserPlane->getPosition().y + UserPlane->getContentSize().height/2 + bullet->getContentSize().height/2);
		bullet->setScale(this->ScaleNum); //双发子弹 缩放
		this->addChild(bullet,2); //优先级为2
		Bullets_Vec.pushBack(bullet);
		bullet = Bullets::BulletsCreate(this->Now_User_Bullets_Type,1);
		bullet->setPosition(UserPlane->getPosition().x,UserPlane->getPosition().y + UserPlane->getContentSize().height/2 + bullet->getContentSize().height/2);
		bullet->setScale(this->ScaleNum); //双发子弹 缩放
		this->addChild(bullet,2); //优先级为2
		Bullets_Vec.pushBack(bullet);
		bullet = Bullets::BulletsCreate(this->Now_User_Bullets_Type,2);
		bullet->setPosition(UserPlane->getPosition().x + UserPlane->getContentSize().width/9,UserPlane->getPosition().y + UserPlane->getContentSize().height/2 + bullet->getContentSize().height/2);
		bullet->setScale(this->ScaleNum); //双发子弹 缩放
		this->addChild(bullet,2); //优先级为2
		Bullets_Vec.pushBack(bullet);
		break;
	}


}

void MainScene::EnemyBulletCreate(float)
{
	for(auto Enemy:this->Enemy_Vec)
	{
		if(Enemy->Type == Big_Enemy_Plane) //大敌机有子弹
		{
			Bullets* bullet = Bullets::BulletsCreate(Blue_Single,1);
			bullet->setPosition(Enemy->getPosition().x,Enemy->getPosition().y - Enemy->getContentSize().height/2 - bullet->getContentSize().height/2);
			bullet->setScale(this->ScaleNum); //单发子弹 缩放
			this->addChild(bullet,2); //优先级为2
			Enemy_Bullet_Vec.pushBack(bullet);
		}
	}
}

void MainScene::CreateEnemyPlane(Enemy_Plane_Type Type) //根据传入敌机类型创建敌机
{
	for(auto Enemy:this->Enemy_Vec) //只允许同时出现一架BOSS敌机
	{
		if(Enemy->Type == Big_Enemy_Plane)
		{
			return;
		}
	}
	auto Enemy = Enemy_Plane::create(Type);
	float x = ( MainScene::GetRand() % (int)( Director::getInstance()->getVisibleSize().width - Enemy->getContentSize().width  + 1) )+Enemy->getContentSize().width/2;
	float y = Director::getInstance()->getVisibleSize().height + Enemy->getContentSize().height/2;
	Enemy->setPosition(x,y);
	Enemy->setScale(this->ScaleNum); //敌机 缩放
	this->addChild(Enemy,4);
	for(auto Enemy_Enum:Enemy_Vec)
	{
		if(Enemy->getBoundingBox().intersectsRect(Enemy_Enum->getBoundingBox())) //如果存在重叠
		{		
			this->removeChild(Enemy);
			return;
		}
	}
	this->Enemy_Vec.pushBack(Enemy);
}

void MainScene::Small_Enemy_Plane_Create(float)
{
	this->CreateEnemyPlane(Small_Enemy_Plane);
}

void MainScene::Middle_Enemy_Plane_Create(float)
{
	this->CreateEnemyPlane(Middle_Enemy_Plane);
}

void MainScene::Big_Enemy_Plane_Create(float)
{
	this->CreateEnemyPlane(Big_Enemy_Plane);
}

void MainScene::CreateProp(Prop_Type CreateType,Point CreatePos) //根据传入类型创建道具
{
	auto Prop_obj = Props::PropsCreate(CreateType);
	if(Prop_obj == NULL)
	{
		return;
	}
	Prop_obj->setPosition(CreatePos);
	Prop_obj->setScale(this->ScaleNum*1.5); //道具 缩放
	this->Props_Vec.pushBack(Prop_obj);
	this->addChild(Prop_obj,4);
}

void MainScene::ClearAllEnemy() //清除所有敌机
{
	Vector<Enemy_Plane*> Enemy_Del_Vec;
	for(auto Enemy:Enemy_Vec)
	{   //此处可设定某些敌机不被清除
		/*if(Enemy->Type == Big_Enemy_Plane)
		{
			continue;
		} */
		this->Score_Now += Enemy->dead();
		this->removeChild(Enemy);
		Enemy_Del_Vec.pushBack(Enemy);
	}
	
	for(auto Enemy:Enemy_Del_Vec)
	{
		Enemy_Vec.eraseObject(Enemy,true);
	}
	Enemy_Del_Vec.clear();
}

void MainScene::PrepareAnimation()
{
	/* 用户飞机爆炸动画缓存 */
	auto UserPlaneDead_Animation = Animation::create();
	for(int i=0;i<6;i++)
	{
		auto DeadSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("boom%d.png",i+1));
		UserPlaneDead_Animation->addSpriteFrame(DeadSpriteFrame);
	}
	UserPlaneDead_Animation->setDelayPerUnit(0.5f);
	AnimationCache::getInstance()->addAnimation(UserPlaneDead_Animation,"UserPlane_Dead_Animation");
}

void MainScene::GoToGameOver() //游戏结束
{
	this->unscheduleAllSelectors(); //停止所有任务器
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect("res/audio/gameover.mp3", false);
	auto UserDeadAnimation = AnimationCache::getInstance()->getAnimation("UserPlane_Dead_Animation");
	auto UserDead_Animate = Animate::create(UserDeadAnimation);
	auto UserDead_Callfunc = CallFuncN::create([=](Node* node) //回调函数
	{
		node->removeFromParentAndCleanup(true); //从父容器里移除自身
		Director::getInstance()->getRunningScene()->cleanup();
		auto EndScene_obj = EndScene::CreateScene(this->Score_Now);
		Director::getInstance()->replaceScene(EndScene_obj);
	});
	this->UserPlane->runAction(Sequence::create(UserDead_Animate,UserDead_Callfunc,NULL)); //用Sequen实现动画执行的先后顺序，NULL表示动画终止
}

int MainScene::GetRand()
{
	struct timeval now;
    gettimeofday(&now, NULL);
    unsigned rand_seed = (unsigned)(now.tv_sec*1000 + now.tv_usec/1000);
    srand(rand_seed); //初始化随机数种子
    return rand();    
}

void MainScene::GamePause(Ref*)
{
	auto GameMenu = this->getChildByTag(119);
	auto PauseItem = GameMenu->getChildByTag(120);
	auto ResumeItem = GameMenu->getChildByTag(121);
	PauseItem->setVisible(false);
	ResumeItem->setVisible(true);
	this->IsGamePause = true;	//禁用触摸
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->stopAllEffects();
	Director::getInstance()->pause();	//通过调用导演的pause来暂停游戏
}

void MainScene::GameResume(Ref*)
{
	auto GameMenu = this->getChildByTag(119);
	auto PauseItem = GameMenu->getChildByTag(120);
	auto ResumeItem = GameMenu->getChildByTag(121);
	PauseItem->setVisible(true);
	ResumeItem->setVisible(false);
	this->IsGamePause = false;	//启用触摸
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	SimpleAudioEngine::getInstance()->resumeAllEffects();
	Director::getInstance()->resume();	//通过调用导演的resume恢复游戏
}
