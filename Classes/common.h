/* ͨ�������� */
#ifndef Common_H
#define Common_H
#include "cocos2d.h"
USING_NS_CC;
typedef enum Bullets_Type //�ӵ�ö������
{
	Blue_Single,
	Blue_Double,
	Yellow_Single,
	Yellow_Double
}; 

typedef enum Enemy_Plane_Type //�л�ö������
{
	Big_Enemy_Plane,
	Middle_Enemy_Plane,
	Small_Enemy_Plane
};

typedef enum Prop_Type //����ö������
{
	Bullet_Change,
	HP_Add,
	Defense_Buff,
	Enemy_Clear
};

class Props:public cocos2d::Sprite //������
{
public:
	static Props* PropsCreate(Prop_Type CreateType); //���ݴ����ӵ����ʹ����ӵ�
	bool init(Prop_Type CreateType);	//��ʼ��
	Prop_Type Type;
};

class Bullets:public cocos2d::Sprite	//�ӵ���
{
public:
	static Bullets* BulletsCreate(Bullets_Type CreateType,int DirectionInput); //���ݴ����ӵ����ʹ����ӵ�
	bool init(Bullets_Type CreateType,int DirectionInput); //��ʼ��
	int GetAttackData(); //��ȡ�ӵ���������
	Bullets_Type Type;
	int Direction_Type;
private:
	int Attack;
};

class Enemy_Plane:public cocos2d::Sprite //�л���
{
public:
	int Step_Length;	//�л����в���
	int Hp;	//�л�Ѫ��
	Enemy_Plane_Type Type; //�л�����
	static Enemy_Plane* create(Enemy_Plane_Type Plane_Type);
	bool init(Enemy_Plane_Type Plane_Type);
	int hitted(Bullets* bullet); //�л�����
	int dead(); //�л�����



private:
	int Score; //�������÷���
	void PrepareHittedAnimation(); //Ԥ���õл����˶���
	void PrepareDeadAnimation();  //Ԥ���õл���������
};

#endif