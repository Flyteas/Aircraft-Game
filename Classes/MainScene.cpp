/* Version 0.9 */
/* Flyshit 2015.8.29 */
/* Mail to: Flyshit@cqu.edu.cn */

#include "MainScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

MainScene::MainScene()
{
	/* ��ʼ������ */
	Touch_Point_Offset = Point(0,0);
	this->Score_Now = 0;
	this->UserHp = 2;
	this->Now_User_Bullets_Type = Yellow_Double;  //�����ӵ�����
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

Scene* MainScene::CreateScene(int GameLevel)	//������㴴������
{
	auto Layer = MainScene::create(GameLevel); //������
	auto Scene = cocos2d::Scene::create(); //��������
	Scene->addChild(Layer);	//��Ӳ㵽����
	return Scene;
}

bool MainScene::init(int GameLevelInput)	//��ʼ������
{
	if(!Layer::init())   
	{        
		return false; //��ʼ��ʧ��  
	}   
	this->GameLevel = GameLevelInput;
	Sprite* Background_1;
	Sprite* Background_2;

	/* ��ʼ���Ѷ����� */
	switch (this->GameLevel)
	{
	case 0:
		Background_1 = Sprite::createWithSpriteFrameName("img_bg_level_3.jpg"); //������������
		Background_2 = Sprite::createWithSpriteFrameName("img_bg_level_3.jpg");
		schedule(schedule_selector(MainScene::Small_Enemy_Plane_Create), 18, -1, 3);
		schedule(schedule_selector(MainScene::Middle_Enemy_Plane_Create), 25, -1, 6);
		schedule(schedule_selector(MainScene::Big_Enemy_Plane_Create),50, -1, 8);
		break;
	case 1:
		Background_1 = Sprite::createWithSpriteFrameName("img_bg_level_4.jpg"); //������������
		Background_2 = Sprite::createWithSpriteFrameName("img_bg_level_4.jpg");
		schedule(schedule_selector(MainScene::Small_Enemy_Plane_Create), 10, -1, 3);
		schedule(schedule_selector(MainScene::Middle_Enemy_Plane_Create), 15, -1, 6);
		schedule(schedule_selector(MainScene::Big_Enemy_Plane_Create),25, -1, 8);
		break;
	case 2:
		Background_1 = Sprite::createWithSpriteFrameName("img_bg_level_5.jpg"); //������������
		Background_2 = Sprite::createWithSpriteFrameName("img_bg_level_5.jpg");
		schedule(schedule_selector(MainScene::Small_Enemy_Plane_Create), 5, -1, 2);
		schedule(schedule_selector(MainScene::Middle_Enemy_Plane_Create), 10, -1, 3);
		schedule(schedule_selector(MainScene::Big_Enemy_Plane_Create),15, -1, 8);
		break;
	}
	/* ����ս������ */
	Size VisibleSize = Director::getInstance()->getVisibleSize(); //��ȡ���������С  
	Point VisibleOrigin = Director::getInstance()->getVisibleOrigin();  //��ȡ��������ԭ��λ��
	//auto Background_1 = Sprite::createWithSpriteFrameName("img_bg_level_4.jpg"); //������������
	this->ScaleNum = VisibleSize.width/Background_1->getContentSize().width; //�������ű���
	Background_1->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT); //����λ��,���½�λ��
	Background_1->setScale(this->ScaleNum); //���� ����
	this->addChild(Background_1,-1,1); //��ӱ���
	//auto Background_2 = Sprite::createWithSpriteFrameName("img_bg_level_4.jpg");
	Background_2->getTexture()->setAliasTexParameters(); //���������
	Background_2->setScale(this->ScaleNum); //���� ����
	this->addChild(Background_2,-1,2);
	Background_2->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT); //���½�λ��
	
	/* �����û��ɻ� */
	UserPlane = Sprite::createWithSpriteFrameName("userplane.png");
	UserPlane->setPosition(VisibleSize.width/2+VisibleOrigin.x,UserPlane->getContentSize().height/2); //�����û��ɻ���ʼλ��
	UserPlane->setScale(this->ScaleNum); //�û��ɻ� ����
	this->addChild(UserPlane,3,3); //�û��ɻ��������ȼ�Ϊ3��tagΪ3
	auto UserPlaneAnimation = Animation::create(); //�����û��ɻ���������
	UserPlaneAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("userplane.png")); //Ϊ�û��ɻ������������֡
	UserPlaneAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("userplane.png"));
	UserPlaneAnimation->setDelayPerUnit(0.25); //����ˢ��ʱ����
	UserPlaneAnimation->setLoops(-1); //���ö������Ŵ�����-1Ϊ���޴Σ�0Ϊ������
	auto UserPlaneAnimate = Animate::create(UserPlaneAnimation); //�����û��ɻ��������󴴽���������
	UserPlane->runAction(UserPlaneAnimate); //ִ���û��ɻ�����

	/* ���÷�����ʾ */
	auto ScoreTextLabel = Label::createWithSystemFont("Score:", "Arial", 36);
	ScoreTextLabel->setPosition(0, VisibleSize.height-45);
	ScoreTextLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	ScoreTextLabel->setColor(Color3B::WHITE);
	ScoreTextLabel->setScale(this->ScaleNum); //���ϽǷ�����ʾ ����
	this->addChild(ScoreTextLabel, 99);	//����������ɫ
	auto ScoreLabel = Label::createWithBMFont("fonts/font.fnt", "0");
	ScoreLabel->setPosition(ScoreTextLabel->getContentSize().width + 39, VisibleSize.height-45);
	ScoreLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	ScoreLabel->setColor(Color3B::WHITE);
	ScoreLabel->setScale(this->ScaleNum); //���ϽǷ�����ʾ ����
	this->addChild(ScoreLabel, 99, 90);

	/* ��������ֵ��ʾ */
	auto HPTextLabel = Label::createWithSystemFont("HP:", "Arial", 40);
	HPTextLabel->setPosition(910, 0);
	HPTextLabel->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	HPTextLabel->setColor(Color3B::WHITE);
	HPTextLabel->setScale(this->ScaleNum); //���½�����ֵ��ʾ ����
	this->addChild(HPTextLabel, 99);	//����������ɫ
	auto HPLabel = Label::createWithBMFont("fonts/font.fnt", "0");
	HPLabel->setPosition(HPTextLabel->getContentSize().width + 950,10);
	HPLabel->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	HPLabel->setColor(Color3B::WHITE);
	HPLabel->setScale(this->ScaleNum); //���½�����ֵ��ʾ ����
	this->addChild(HPLabel, 99, 91);

	/* ������ͣ��ť */
	auto Pause_Button = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	auto Pause_Button_Pressed = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	auto Pause_Button_MenuItem = MenuItemSprite::create(Pause_Button, Pause_Button_Pressed, CC_CALLBACK_1(MainScene::GamePause, this));
	Pause_Button_MenuItem->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	Pause_Button_MenuItem->setPosition(0,0);
	Pause_Button_MenuItem->setTag(120);
	this->addChild(Pause_Button);

	/* ���ü�����ť */
	auto Resume_Button = Sprite::createWithSpriteFrameName("game_resume_nor.png");
	auto Resume_Button_Pressed = Sprite::createWithSpriteFrameName("game_resume_pressed.png");
	auto Resume_Button_MenuItem = MenuItemSprite::create(Resume_Button, Resume_Button_Pressed, CC_CALLBACK_1(MainScene::GameResume, this));
	Resume_Button_MenuItem->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	Resume_Button_MenuItem->setPosition(0,0);
	Resume_Button_MenuItem->setVisible(false);
	Resume_Button_MenuItem->setTag(121);
	this->addChild(Resume_Button);

	/* ��Ӱ�ť�� */
	auto GameMenu = Menu::create(Pause_Button_MenuItem,Resume_Button_MenuItem,NULL);
	GameMenu->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	GameMenu->setPosition(0,0);
	this->addChild(GameMenu,99,119);
	/* Ԥ���涯����Դ */
	this->PrepareAnimation();

	/* ���ñ������� */
	SimpleAudioEngine::getInstance()->playBackgroundMusic("res/audio/gamebackground.mp3", true);


	/* �ɻ��ƶ� */
	auto TouchListener = EventListenerTouchOneByOne::create(); //���㴥���¼�������
	TouchListener->onTouchBegan = [=](Touch* Touch_Obj,Event* e) //��ʼ���� �¼�
	{
		if(!UserPlane->getBoundingBox().containsPoint(Touch_Obj->getLocation())) //�жϴ������Ƿ�λ���û��ɻ���Χ��
		{
			return false; //���ڷ�Χ�ڣ�����false����ִ�н��������¼�
		}
		Touch_Point_Offset = Touch_Obj->getLocation() - UserPlane->getPosition();
		return !this->IsGamePause;
	};
	TouchListener->onTouchMoved = [=](Touch* Touch_Obj,Event* e) //�����ƶ� �¼�
	{
		Point PlaneNowPos = Touch_Obj->getLocation() - Touch_Point_Offset; //�ɻ�δ�ж��߽�ǰ��λ��
		Point UserPlaneNextPos; //�ж��߽���λ��
		UserPlaneNextPos.x = MIN(MAX(UserPlane->getContentSize().width/2,PlaneNowPos.x),VisibleSize.width + VisibleOrigin.x - UserPlane->getContentSize().width/2); //X��߽�����
		UserPlaneNextPos.y = MIN(MAX(UserPlane->getContentSize().height/2,PlaneNowPos.y),VisibleSize.height + VisibleOrigin.y - UserPlane->getContentSize().width/2); //Y��߽�����
		UserPlane->setPosition(UserPlaneNextPos); //�ƶ��ɻ�
	};
	TouchListener->onTouchEnded = [](Touch* Touch_Obj,Event* e) //�������� �¼�
	{

	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(TouchListener,UserPlane); //��UserPlane��ӵ��¼��������
	
	/* �ӵ����� */
	schedule(schedule_selector(MainScene::BulletCreate),0.2f); //�ӵ����䶨ʱ��
	schedule(schedule_selector(MainScene::EnemyBulletCreate),1); //�л��ӵ����䶨ʱ��
	scheduleUpdate(); //֡ˢ�¶�ʱ��
	return true;
}

void MainScene::update(float)
{
	Vector<Bullets*> Bullets_Del_Vec; //��ɾ���ӵ�����
	Vector<Bullets*> Enemy_Bullet_Del_Vec; //��ɾ���л��ӵ�����
	Vector<Enemy_Plane*> Enemy_Del_Vec; //��ɾ���л�
	Vector<Props*> Props_Del_Vec; //��ɾ�����߼���
	auto Background_1 = this->getChildByTag(1); //��ȡ����1
	auto Background_2 = this->getChildByTag(2); //��ȡ����2
	Background_1->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	Background_2->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	Background_1->setPositionY(Background_1->getPositionY()-3);  //ÿ֡�¹�3����
	Background_2->setPositionY(Background_1->getPositionY()+Background_1->getContentSize().height); //�ν������������ڱ�
	if(Background_2->getPositionY() <= 0) //����2����ײ�
	{
		Background_1->setPositionY(0); //���ñ���
	}

	/* �ӵ���л���ײ��� */
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
					if(Enemy->Type == Big_Enemy_Plane) //����Ǵ�л�������ֵ���
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
		/* ���һ����Ч�л� */
		for(auto Enemy:Enemy_Del_Vec)
		{
			this->Enemy_Vec.eraseObject(Enemy,true);
		}
		Enemy_Del_Vec.clear();
		
	}
	/* ���һ����Ч�ӵ� */
	for(auto Bullet:Bullets_Del_Vec)
	{
		Bullets_Vec.eraseObject(Bullet,true);
	}
	Bullets_Del_Vec.clear();

	/* �л��ӵ����û��ɻ���ײ��� */
	for(auto Enemy_Bullet:this->Enemy_Bullet_Vec)
	{
		if(Enemy_Bullet->getBoundingBox().intersectsRect(UserPlane->getBoundingBox())) //���û��ɻ�
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

	/* ���һ����Ч�л��ӵ� */
	for(auto Enemy_Bullet:Enemy_Bullet_Del_Vec)
	{
		Enemy_Bullet_Vec.eraseObject(Enemy_Bullet,true);
	}
	Enemy_Bullet_Del_Vec.clear();


	/* �л����û��ɻ���ײ��� */
	for(auto Enemy:Enemy_Vec)
	{
		if(Enemy->getBoundingBox().intersectsRect(UserPlane->getBoundingBox()))
		{
			this->UserHp--;
			Enemy_Del_Vec.pushBack(Enemy);
			if(Enemy->Type == Big_Enemy_Plane) //����Ǵ�л�������ֵ���
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

	/* ���һ����Ч�л� */
	for(auto Enemy:Enemy_Del_Vec)
	{
		this->Enemy_Vec.eraseObject(Enemy,true);
	}
	Enemy_Del_Vec.clear();

	/* �������û��ɻ���ײ��� */
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
				this->UserHp++;  //��Ѫ�ӵö�
				break;
			}
			Props_Del_Vec.pushBack(Prop);
			this->removeChild(Prop);
			SimpleAudioEngine::getInstance()->playEffect("res/audio/getprop.mp3", false);
		}
	}
	/* ���һ����Ч���� */
	for(auto Prop:Props_Del_Vec)
	{
		this->Props_Vec.eraseObject(Prop);
	}
	Props_Del_Vec.clear();

	/* �ӵ��ƶ� */
	for(auto Bullet:Bullets_Vec)
	{
		switch (Bullet->Direction_Type) //�ж��ӵ����з���
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
		if(Bullet->getPositionY() >= Director::getInstance()->getVisibleSize().height + Bullet->getContentSize().height/2 || Bullet->getPositionX() <= -Bullet->getContentSize().width/2 || Bullet->getPositionX() >= Director::getInstance()->getVisibleSize().width + Bullet->getContentSize().width/2) //�ж��ӵ��Ƿ�Խ���߽�
		{
			Bullets_Del_Vec.pushBack(Bullet); //��¼��ɾ���ӵ�ָ��
			this->removeChild(Bullet); //ɾ���ӵ�
		}
	}


	/* ���һ����Ч�ӵ� */
	for(auto Bullet:Bullets_Del_Vec)
	{
		Bullets_Vec.eraseObject(Bullet,true);
	}
	Bullets_Del_Vec.clear();

	/* �л��ӵ��ƶ� */
	for(auto Enemy_Bullet:this->Enemy_Bullet_Vec)
	{
		Enemy_Bullet->setPositionY(Enemy_Bullet->getPositionY() - 8);
		if(Enemy_Bullet->getPositionY() <=  Enemy_Bullet->getContentSize().height/2) //�ж��ӵ��Ƿ�Խ���߽�
		{
			Enemy_Bullet_Del_Vec.pushBack(Enemy_Bullet); //��¼��ɾ���ӵ�ָ��
			this->removeChild(Enemy_Bullet); //ɾ���ӵ�
		}
	}

	/* ���һ����Ч�л��ӵ� */
	for(auto Enemy_Bullet:Enemy_Bullet_Del_Vec)
	{
		Enemy_Bullet_Vec.eraseObject(Enemy_Bullet,true);
	}
	Enemy_Bullet_Del_Vec.clear();

	/* �л��ƶ� */
	for(auto Enemy:Enemy_Vec)
	{
		if(Enemy->Type == Big_Enemy_Plane && Enemy->getPositionY() <= (Director::getInstance()->getVisibleSize().height - Enemy->getContentSize().height/2)) //BOSS�ɻ�ƽ��
		{
			if(Enemy->getPositionX() <= Enemy->getContentSize().width/2 || Enemy->getPositionX() >= (Director::getInstance()->getVisibleSize().width - Enemy->getContentSize().width/2))
			{
				Enemy->Step_Length = -Enemy->Step_Length;
			}
			Enemy->setPositionX(Enemy->getPositionX() + Enemy->Step_Length);
			for(auto Enemy_Enum:Enemy_Vec) //�ж��ƶ�����λ���Ƿ��зɻ����еĻ��ͻص�ԭλ��
			{
				if(Enemy == Enemy_Enum)
				{
					continue;
				}
				if(Enemy->getBoundingBox().intersectsRect(Enemy_Enum->getBoundingBox())) //���ڷɻ�
				{
					Enemy->setPositionX(Enemy->getPositionX() - Enemy->Step_Length);
					break;
				}
			}
			continue;
		}
		Enemy->setPositionY(Enemy->getPositionY() - Enemy->Step_Length);
		for(auto Enemy_Enum:Enemy_Vec) //�ж��ƶ�����λ���Ƿ��зɻ����еĻ��ͻص�ԭλ��
		{
			if(Enemy == Enemy_Enum)
			{
				continue;
			}
			if(Enemy->getBoundingBox().intersectsRect(Enemy_Enum->getBoundingBox())) //���ڷɻ�
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

	/* ���һ����Ч�л� */
	for(auto Enemy:Enemy_Del_Vec)
	{
		this->Enemy_Vec.eraseObject(Enemy,true);
	}
	Enemy_Del_Vec.clear();

	/* �����ƶ� */
	for(auto Prop:Props_Vec )
	{
		Prop->setPositionY(Prop->getPositionY() - 15);
		if(Prop->getPositionY() <= Prop->getContentSize().height/2) //����ɾ��
		{
			Props_Del_Vec.pushBack(Prop);
			this->removeChild(Prop);
		}
	}

	/* ���һ����Ч���� */
	for(auto Prop:Props_Del_Vec)
	{
		this->Props_Vec.eraseObject(Prop);
	}
	Props_Del_Vec.clear();


	/* ��ʾ�ؼ����ݸ��� */
	auto ScoreLabelDis = (Label *) this->getChildByTag(90);
	auto HPLabelDis = (Label *) this->getChildByTag(91);
	ScoreLabelDis->setString(StringUtils::format("%d", this->Score_Now)); //���·�����ʾ
	HPLabelDis->setString(StringUtils::format("%d", this->UserHp)); //���·�����ʾ

}

void MainScene::BulletCreate(float)
{
	auto UserPlane = this->getChildByTag(3); //��ȡ�û��ɻ�
	SimpleAudioEngine::getInstance()->playEffect("/res/audio/bullet.mp3",false);
	Bullets* bullet;
	switch (this->Now_User_Bullets_Type)	//�����ӵ����ʹ����ӵ�
	{
	case Blue_Single: //��ɫ����
	case Yellow_Single: //��ɫ����
		bullet = Bullets::BulletsCreate(Now_User_Bullets_Type,1);
		bullet->setPosition(UserPlane->getPosition().x,UserPlane->getPosition().y + UserPlane->getContentSize().height/2 + bullet->getContentSize().height/2);
		bullet->setScale(this->ScaleNum); //�����ӵ� ����
		this->addChild(bullet,2); //���ȼ�Ϊ2
		Bullets_Vec.pushBack(bullet);
		break;
	case Blue_Double: //��ɫ˫��
	case Yellow_Double: //��ɫ˫��
		bullet = Bullets::BulletsCreate(Now_User_Bullets_Type,0);
		bullet->setPosition(UserPlane->getPosition().x - UserPlane->getContentSize().width/9,UserPlane->getPosition().y + UserPlane->getContentSize().height/2 + bullet->getContentSize().height/2);
		bullet->setScale(this->ScaleNum); //˫���ӵ� ����
		this->addChild(bullet,2); //���ȼ�Ϊ2
		Bullets_Vec.pushBack(bullet);
		bullet = Bullets::BulletsCreate(this->Now_User_Bullets_Type,1);
		bullet->setPosition(UserPlane->getPosition().x,UserPlane->getPosition().y + UserPlane->getContentSize().height/2 + bullet->getContentSize().height/2);
		bullet->setScale(this->ScaleNum); //˫���ӵ� ����
		this->addChild(bullet,2); //���ȼ�Ϊ2
		Bullets_Vec.pushBack(bullet);
		bullet = Bullets::BulletsCreate(this->Now_User_Bullets_Type,2);
		bullet->setPosition(UserPlane->getPosition().x + UserPlane->getContentSize().width/9,UserPlane->getPosition().y + UserPlane->getContentSize().height/2 + bullet->getContentSize().height/2);
		bullet->setScale(this->ScaleNum); //˫���ӵ� ����
		this->addChild(bullet,2); //���ȼ�Ϊ2
		Bullets_Vec.pushBack(bullet);
		break;
	}


}

void MainScene::EnemyBulletCreate(float)
{
	for(auto Enemy:this->Enemy_Vec)
	{
		if(Enemy->Type == Big_Enemy_Plane) //��л����ӵ�
		{
			Bullets* bullet = Bullets::BulletsCreate(Blue_Single,1);
			bullet->setPosition(Enemy->getPosition().x,Enemy->getPosition().y - Enemy->getContentSize().height/2 - bullet->getContentSize().height/2);
			bullet->setScale(this->ScaleNum); //�����ӵ� ����
			this->addChild(bullet,2); //���ȼ�Ϊ2
			Enemy_Bullet_Vec.pushBack(bullet);
		}
	}
}

void MainScene::CreateEnemyPlane(Enemy_Plane_Type Type) //���ݴ���л����ʹ����л�
{
	for(auto Enemy:this->Enemy_Vec) //ֻ����ͬʱ����һ��BOSS�л�
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
	Enemy->setScale(this->ScaleNum); //�л� ����
	this->addChild(Enemy,4);
	for(auto Enemy_Enum:Enemy_Vec)
	{
		if(Enemy->getBoundingBox().intersectsRect(Enemy_Enum->getBoundingBox())) //��������ص�
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

void MainScene::CreateProp(Prop_Type CreateType,Point CreatePos) //���ݴ������ʹ�������
{
	auto Prop_obj = Props::PropsCreate(CreateType);
	if(Prop_obj == NULL)
	{
		return;
	}
	Prop_obj->setPosition(CreatePos);
	Prop_obj->setScale(this->ScaleNum*1.5); //���� ����
	this->Props_Vec.pushBack(Prop_obj);
	this->addChild(Prop_obj,4);
}

void MainScene::ClearAllEnemy() //������ел�
{
	Vector<Enemy_Plane*> Enemy_Del_Vec;
	for(auto Enemy:Enemy_Vec)
	{   //�˴����趨ĳЩ�л��������
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
	/* �û��ɻ���ը�������� */
	auto UserPlaneDead_Animation = Animation::create();
	for(int i=0;i<6;i++)
	{
		auto DeadSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("boom%d.png",i+1));
		UserPlaneDead_Animation->addSpriteFrame(DeadSpriteFrame);
	}
	UserPlaneDead_Animation->setDelayPerUnit(0.5f);
	AnimationCache::getInstance()->addAnimation(UserPlaneDead_Animation,"UserPlane_Dead_Animation");
}

void MainScene::GoToGameOver() //��Ϸ����
{
	this->unscheduleAllSelectors(); //ֹͣ����������
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect("res/audio/gameover.mp3", false);
	auto UserDeadAnimation = AnimationCache::getInstance()->getAnimation("UserPlane_Dead_Animation");
	auto UserDead_Animate = Animate::create(UserDeadAnimation);
	auto UserDead_Callfunc = CallFuncN::create([=](Node* node) //�ص�����
	{
		node->removeFromParentAndCleanup(true); //�Ӹ��������Ƴ�����
		Director::getInstance()->getRunningScene()->cleanup();
		auto EndScene_obj = EndScene::CreateScene(this->Score_Now);
		Director::getInstance()->replaceScene(EndScene_obj);
	});
	this->UserPlane->runAction(Sequence::create(UserDead_Animate,UserDead_Callfunc,NULL)); //��Sequenʵ�ֶ���ִ�е��Ⱥ�˳��NULL��ʾ������ֹ
}

int MainScene::GetRand()
{
	struct timeval now;
    gettimeofday(&now, NULL);
    unsigned rand_seed = (unsigned)(now.tv_sec*1000 + now.tv_usec/1000);
    srand(rand_seed); //��ʼ�����������
    return rand();    
}

void MainScene::GamePause(Ref*)
{
	auto GameMenu = this->getChildByTag(119);
	auto PauseItem = GameMenu->getChildByTag(120);
	auto ResumeItem = GameMenu->getChildByTag(121);
	PauseItem->setVisible(false);
	ResumeItem->setVisible(true);
	this->IsGamePause = true;	//���ô���
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->stopAllEffects();
	Director::getInstance()->pause();	//ͨ�����õ��ݵ�pause����ͣ��Ϸ
}

void MainScene::GameResume(Ref*)
{
	auto GameMenu = this->getChildByTag(119);
	auto PauseItem = GameMenu->getChildByTag(120);
	auto ResumeItem = GameMenu->getChildByTag(121);
	PauseItem->setVisible(true);
	ResumeItem->setVisible(false);
	this->IsGamePause = false;	//���ô���
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	SimpleAudioEngine::getInstance()->resumeAllEffects();
	Director::getInstance()->resume();	//ͨ�����õ��ݵ�resume�ָ���Ϸ
}
