#ifndef __MainScene_H__
#define __MainScene_H__
#include "common.h"
#include "EndScene.h"
USING_NS_CC;
class MainScene : public cocos2d::Layer //主界面层类，公有继承自基类cocos2d::Layer
{
public:	
	MainScene();
	static cocos2d::Scene* CreateScene(int GameLevel); //创建层	
	static MainScene* create(int GameLevel);
	virtual bool init(int GameLevelInput);	//初始化
	void update(float); 
	static int GetRand(); //生成随机道具类型
private:
	int GameLevel;
	cocos2d::Sprite* UserPlane; //用户飞机
	int Score_Now;
	int UserHp; //用户血量
	float ScaleNum; //缩放倍数
	bool IsGamePause; //当前游戏是否暂停
	cocos2d::Point Touch_Point_Offset; //触摸点与飞机中心点的偏移量
	cocos2d::Vector<Bullets*> Bullets_Vec; //存储有效子弹
	cocos2d::Vector<Enemy_Plane*> Enemy_Vec; //存储有效敌机
	cocos2d::Vector<Props*> Props_Vec; //存储有效道具
	cocos2d::Vector<Bullets*> Enemy_Bullet_Vec; //存储敌机有效子弹
	Bullets_Type Now_User_Bullets_Type;
	void BulletCreate(float); //创建子弹
	void EnemyBulletCreate(float); //创建敌机子弹
	void CreateEnemyPlane(Enemy_Plane_Type Type); //根据传入的敌机类型创建敌机
	void Small_Enemy_Plane_Create(float); //创建小敌机
	void Middle_Enemy_Plane_Create(float); //创建中敌机
	void Big_Enemy_Plane_Create(float); //创建大敌机
	void CreateProp(Prop_Type CreateType,Point CreatePos); //根据传入类型创建道具
	void ClearAllEnemy();  //清除当前屏幕的所有敌机，当吃到指定道具时调用
	void PrepareAnimation(); //预缓存动画资源
	void Clear_Del_Sprite(); //清除无效子弹、敌机、道具
	void GoToGameOver(); //游戏结束
	void GamePause(Ref*); //暂停游戏
	void GameResume(Ref*); //继续游戏
};

#endif