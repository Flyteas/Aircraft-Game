#include "common.h"
using namespace cocos2d;
Bullets* Bullets::BulletsCreate(Bullets_Type CreateType,int DirectionInput)
{
	auto bullets_create = new Bullets();
	if(bullets_create != NULL && bullets_create->init(CreateType,DirectionInput)) //��������ɹ�
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


int Bullets::GetAttackData() //��ȡ�ӵ���������
{
	return this->Attack;
}

Enemy_Plane* Enemy_Plane::create(Enemy_Plane_Type Plane_Type) //�����л�����
{
	auto enemy_create = new Enemy_Plane();
	if(enemy_create != NULL && enemy_create->init(Plane_Type)) //��������ɹ�
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
		Hp = 100; // ����Ѫ��
		Step_Length = 1; //���÷��в���
		this->Score = 5000;
		//������ӷɻ����ж���
		Big_Plane_Fly_Animation = Animation::create(); //�������ͷɻ��ķ��ж���
		Big_Plane_Fly_Animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bigplane.png"));
		Big_Plane_Fly_Animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bigplane.png"));
		Big_Plane_Fly_Animation->setDelayPerUnit(0.2f);
		Big_Plane_Fly_Animation->setLoops(-1);	//���޴���
		this->runAction(Animate::create(Big_Plane_Fly_Animation));
		break;
	case Middle_Enemy_Plane:
		InitResult = Sprite::initWithSpriteFrameName("middleplane.png");
		Hp = 60; //����HP
		Step_Length = 1; //���÷��в���
		this->Score = 2000;
		break;
	case Small_Enemy_Plane:
		InitResult = Sprite::initWithSpriteFrameName("smallenemy.png");
		Hp = 20; //����HP
		Step_Length = 2; //���÷��в���
		this->Score = 1000;
		break;
	}
	if(InitResult)
	{
	this->PrepareHittedAnimation(); //��ʼ���л����˶���
	this->PrepareDeadAnimation(); //��ʼ���л���������
	}
	return InitResult;
}

int Enemy_Plane::hitted(Bullets* bullet)  //�л�����
{
	this->Hp = this->Hp - bullet->GetAttackData(); //Ѫ������
	if(!(this->Hp > 0)) //���Ѫ��������0����ը
	{
		return this->dead();		//��ը
	}
	Animation* Hitted_Animation; //��ȡԤ���õĵл����˶���
	switch (this->Type)
	{
	case Small_Enemy_Plane: //С�л������˶���
		return 0;
		break;
	case Middle_Enemy_Plane:
		Hitted_Animation = AnimationCache::getInstance()->getAnimation("Middle_Hitted_Animation"); //���͵л����������ִӻ����л�ȡ����
		break;
	case Big_Enemy_Plane:
		Hitted_Animation = AnimationCache::getInstance()->getAnimation("Big_Hitted_Animation"); //���͵л�
		break;
	}
	this->runAction(Animate::create(Hitted_Animation));
	return 0;
}

int Enemy_Plane::dead() //�л���ը
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
		node->removeFromParentAndCleanup(true); //�Ӹ��������Ƴ�����
	});
	this->runAction(Sequence::create(Dead_Animate,Dead_Callfunc,NULL)); //��Sequenʵ�ֶ���ִ�е��Ⱥ�˳��NULL��ʾ������ֹ
	return this->Score;
}

void Enemy_Plane::PrepareHittedAnimation()  //׼���л����˶���
{
	Animation* Hitted_Animation;
	switch (this->Type)
	{
	case Small_Enemy_Plane:
		return;  //С�л������˶���
		break;
	case Middle_Enemy_Plane:
		Hitted_Animation = Animation::create();
		Hitted_Animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("middleplane.png"));
		Hitted_Animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("middleplane.png"));
		Hitted_Animation->setDelayPerUnit(0.2f);
		AnimationCache::getInstance()->addAnimation(Hitted_Animation,"Middle_Hitted_Animation");  //���涯��
		break;
	case Big_Enemy_Plane:
		Hitted_Animation = Animation::create();
		Hitted_Animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bigplane.png"));
		Hitted_Animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bigplane.png"));
		Hitted_Animation->setDelayPerUnit(0.2f);
		AnimationCache::getInstance()->addAnimation(Hitted_Animation,"Big_Hitted_Animation");  //���涯��
		break;
	}
	this->runAction(Animate::create(Hitted_Animation));
}

void Enemy_Plane::PrepareDeadAnimation() //׼���л���ը����
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
	if(Props_Create != NULL && Props_Create->init(CreateType)) //��������ɹ�
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
