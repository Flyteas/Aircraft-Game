#include "common.h"
using namespace cocos2d;
Bullets* Bullets::BulletsCreate(Bullets_Type CreateType,int DirectionInput)
{
	auto bullets_create = new Bullets();
	if(bullets_create != NULL && bullets_create->init(CreateType,DirectionInput)) //如果创建成功
	{
		bullets_create->autorelease();
		return bullets_create;
	}
	else
	{
		delete bullets_create;
		bullets_create = NULL;
		return bullets_create;
	}
}

bool Bullets::init(Bullets_Type CreateType,int DirectionInput)
{
	this->Type = CreateType;
	this->Direction_Type = DirectionInput;
	bool InitResult;
	switch (this->Type)
	{
	case Yellow_Single:
		this->Attack = 1;
		InitResult = Sprite::initWithSpriteFrameName("bigyellowbullet_1.png");
		break;
	case Yellow_Double:
		this->Attack = 2;
		InitResult = Sprite::initWithSpriteFrameName(StringUtils::format("smallyellowbullet_%d.png",this->Direction_Type));
		break;
	case Blue_Single:
		this->Attack = 3;
		InitResult = Sprite::initWithSpriteFrameName("smallbulebullet_1.png");
		break;
	case Blue_Double:
		this->Attack = 4;
		InitResult = Sprite::initWithSpriteFrameName(StringUtils::format("smallbulebullet_%d.png",this->Direction_Type));
		break;
	}
	return InitResult;
}


int Bullets::GetAttackData() //获取子弹攻击数据
{
	return this->Attack;
}

Enemy_Plane* Enemy_Plane::create(Enemy_Plane_Type Plane_Type) //创建敌机对象
{
	auto enemy_create = new Enemy_Plane();
	if(enemy_create != NULL && enemy_create->init(Plane_Type)) //如果创建成功
	{
		enemy_create->autorelease();
		return enemy_create;
	}
	else
	{
		delete enemy_create;
		enemy_create = NULL;
		return enemy_create;
	}
}

bool Enemy_Plane::init(Enemy_Plane_Type Plane_Type)
{
	this->Type = Plane_Type;
	bool InitResult;
	Animation* Big_Plane_Fly_Animation;
	switch (this->Type)
	{
	case Big_Enemy_Plane:
		InitResult = Sprite::initWithSpriteFrameName("bigplane.png");
		Hp = 100; // 设置血量
		Step_Length = 1; //设置飞行步长
		this->Score = 5000;
		//下面添加飞机飞行动画
		Big_Plane_Fly_Animation = Animation::create(); //创建大型飞机的飞行动画
		Big_Plane_Fly_Animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bigplane.png"));
		Big_Plane_Fly_Animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bigplane.png"));
		Big_Plane_Fly_Animation->setDelayPerUnit(0.2f);
		Big_Plane_Fly_Animation->setLoops(-1);	//无限次数
		this->runAction(Animate::create(Big_Plane_Fly_Animation));
		break;
	case Middle_Enemy_Plane:
		InitResult = Sprite::initWithSpriteFrameName("middleplane.png");
		Hp = 60; //设置HP
		Step_Length = 1; //设置飞行步长
		this->Score = 2000;
		break;
	case Small_Enemy_Plane:
		InitResult = Sprite::initWithSpriteFrameName("smallenemy.png");
		Hp = 20; //设置HP
		Step_Length = 2; //设置飞行步长
		this->Score = 1000;
		break;
	}
	if(InitResult)
	{
	this->PrepareHittedAnimation(); //初始化敌机受伤动画
	this->PrepareDeadAnimation(); //初始化敌机死亡动画
	}
	return InitResult;
}

int Enemy_Plane::hitted(Bullets* bullet)  //敌机受伤
{
	this->Hp = this->Hp - bullet->GetAttackData(); //血量减少
	if(!(this->Hp > 0)) //如果血量不大于0，则爆炸
	{
		return this->dead();		//爆炸
	}
	Animation* Hitted_Animation; //获取预设置的敌机受伤动画
	switch (this->Type)
	{
	case Small_Enemy_Plane: //小敌机无受伤动画
		return 0;
		break;
	case Middle_Enemy_Plane:
		Hitted_Animation = AnimationCache::getInstance()->getAnimation("Middle_Hitted_Animation"); //中型敌机，根据名字从缓存中获取动画
		break;
	case Big_Enemy_Plane:
		Hitted_Animation = AnimationCache::getInstance()->getAnimation("Big_Hitted_Animation"); //大型敌机
		break;
	}
	this->runAction(Animate::create(Hitted_Animation));
	return 0;
}

int Enemy_Plane::dead() //敌机爆炸
{
	Animation* Dead_Animation;
	Animate* Dead_Animate;
	switch (this->Type)
	{
	case Small_Enemy_Plane:
		Dead_Animation = AnimationCache::getInstance()->getAnimation("Small_Dead_Animation");
		break;
	case Middle_Enemy_Plane:
		Dead_Animation = AnimationCache::getInstance()->getAnimation("Middle_Dead_Animation");
		break;
	case Big_Enemy_Plane:
		Dead_Animation = AnimationCache::getInstance()->getAnimation("Big_Dead_Animation");
		break;
	}
	Dead_Animate = Animate::create(Dead_Animation);
	auto Dead_Callfunc = CallFuncN::create([](Node* node)
	{
		node->removeFromParentAndCleanup(true); //从父容器里移除自身
	});
	this->runAction(Sequence::create(Dead_Animate,Dead_Callfunc,NULL)); //用Sequen实现动画执行的先后顺序，NULL表示动画终止
	return this->Score;
}

void Enemy_Plane::PrepareHittedAnimation()  //准备敌机受伤动画
{
	Animation* Hitted_Animation;
	switch (this->Type)
	{
	case Small_Enemy_Plane:
		return;  //小敌机无受伤动画
		break;
	case Middle_Enemy_Plane:
		Hitted_Animation = Animation::create();
		Hitted_Animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("middleplane.png"));
		Hitted_Animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("middleplane.png"));
		Hitted_Animation->setDelayPerUnit(0.2f);
		AnimationCache::getInstance()->addAnimation(Hitted_Animation,"Middle_Hitted_Animation");  //缓存动画
		break;
	case Big_Enemy_Plane:
		Hitted_Animation = Animation::create();
		Hitted_Animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bigplane.png"));
		Hitted_Animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bigplane.png"));
		Hitted_Animation->setDelayPerUnit(0.2f);
		AnimationCache::getInstance()->addAnimation(Hitted_Animation,"Big_Hitted_Animation");  //缓存动画
		break;
	}
	this->runAction(Animate::create(Hitted_Animation));
}

void Enemy_Plane::PrepareDeadAnimation() //准备敌机爆炸动画
{
	Animation* Dead_Animation = Animation::create();
	switch (this->Type)
	{
	case Small_Enemy_Plane:
		for(int i=0;i<6;i++)
		{
			auto DeadSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("boom%d.png",i+1));
			Dead_Animation->addSpriteFrame(DeadSpriteFrame);
		}
		Dead_Animation->setDelayPerUnit(0.2f);
		AnimationCache::getInstance()->addAnimation(Dead_Animation,"Small_Dead_Animation");
		break;
	case Middle_Enemy_Plane:
		for(int i=0;i<6;i++)
		{
			auto DeadSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("boom%d.png",i+1));
			Dead_Animation->addSpriteFrame(DeadSpriteFrame);
		}
		Dead_Animation->setDelayPerUnit(0.2f);
		AnimationCache::getInstance()->addAnimation(Dead_Animation,"Middle_Dead_Animation");
		break;
	case Big_Enemy_Plane:
		for(int i=0;i<7;i++)
		{
			auto DeadSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("bossboom%d.png",i+1));
			Dead_Animation->addSpriteFrame(DeadSpriteFrame);
		}
		Dead_Animation->setDelayPerUnit(0.2f);
		AnimationCache::getInstance()->addAnimation(Dead_Animation,"Big_Dead_Animation");
		break;
	}
}


Props* Props::PropsCreate(Prop_Type CreateType)
{
	auto Props_Create = new Props();
	if(Props_Create != NULL && Props_Create->init(CreateType)) //如果创建成功
	{
		Props_Create->autorelease();
		return Props_Create;
	}
	else
	{
		delete Props_Create;
		Props_Create = NULL;
		return Props_Create;
	}
}

bool Props::init(Prop_Type CreateType)
{
	this->Type = CreateType;
	bool InitResult;
	switch (this->Type)
	{
	case Bullet_Change:
		InitResult = Sprite::initWithSpriteFrameName("bulletchange.png");
		break;
	case HP_Add:
		InitResult = Sprite::initWithSpriteFrameName("hpadd.png");
		break;
	case Defense_Buff:
		//InitResult = Sprite::initWithSpriteFrameName("restart.png");
		InitResult = Sprite::initWithSpriteFrameName("hpadd.png");
		break;
	case Enemy_Clear:
		InitResult = Sprite::initWithSpriteFrameName("bomb.png");
		break;
	}
	return InitResult;
}
