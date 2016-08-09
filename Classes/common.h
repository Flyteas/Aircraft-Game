/* 通用型数据 */
#ifndef Common_H
#define Common_H
#include "cocos2d.h"
USING_NS_CC;
typedef enum Bullets_Type //子弹枚举类型
{
	Blue_Single,
	Blue_Double,
	Yellow_Single,
	Yellow_Double
}; 

typedef enum Enemy_Plane_Type //敌机枚举类型
{
	Big_Enemy_Plane,
	Middle_Enemy_Plane,
	Small_Enemy_Plane
};

typedef enum Prop_Type //道具枚举类型
{
	Bullet_Change,
	HP_Add,
	Defense_Buff,
	Enemy_Clear
};

class Props:public cocos2d::Sprite //道具类
{
public:
	static Props* PropsCreate(Prop_Type CreateType); //根据传入子弹类型创建子弹
	bool init(Prop_Type CreateType);	//初始化
	Prop_Type Type;
};

class Bullets:public cocos2d::Sprite	//子弹类
{
public:
	static Bullets* BulletsCreate(Bullets_Type CreateType,int DirectionInput); //根据传入子弹类型创建子弹
	bool init(Bullets_Type CreateType,int DirectionInput); //初始化
	int GetAttackData(); //获取子弹攻击数据
	Bullets_Type Type;
	int Direction_Type;
private:
	int Attack;
};

class Enemy_Plane:public cocos2d::Sprite //敌机类
{
public:
	int Step_Length;	//敌机飞行步长
	int Hp;	//敌机血量
	Enemy_Plane_Type Type; //敌机类型
	static Enemy_Plane* create(Enemy_Plane_Type Plane_Type);
	bool init(Enemy_Plane_Type Plane_Type);
	int hitted(Bullets* bullet); //敌机受伤
	int dead(); //敌机死亡



private:
	int Score; //击毁所得分数
	void PrepareHittedAnimation(); //预设置敌机受伤动画
	void PrepareDeadAnimation();  //预设置敌机死亡动画
};

#endif