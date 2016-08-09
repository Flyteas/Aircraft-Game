#ifndef __MainScene_H__
#define __MainScene_H__
#include "common.h"
#include "EndScene.h"
USING_NS_CC;
class MainScene : public cocos2d::Layer //��������࣬���м̳��Ի���cocos2d::Layer
{
public:	
	MainScene();
	static cocos2d::Scene* CreateScene(int GameLevel); //������	
	static MainScene* create(int GameLevel);
	virtual bool init(int GameLevelInput);	//��ʼ��
	void update(float); 
	static int GetRand(); //���������������
private:
	int GameLevel;
	cocos2d::Sprite* UserPlane; //�û��ɻ�
	int Score_Now;
	int UserHp; //�û�Ѫ��
	float ScaleNum; //���ű���
	bool IsGamePause; //��ǰ��Ϸ�Ƿ���ͣ
	cocos2d::Point Touch_Point_Offset; //��������ɻ����ĵ��ƫ����
	cocos2d::Vector<Bullets*> Bullets_Vec; //�洢��Ч�ӵ�
	cocos2d::Vector<Enemy_Plane*> Enemy_Vec; //�洢��Ч�л�
	cocos2d::Vector<Props*> Props_Vec; //�洢��Ч����
	cocos2d::Vector<Bullets*> Enemy_Bullet_Vec; //�洢�л���Ч�ӵ�
	Bullets_Type Now_User_Bullets_Type;
	void BulletCreate(float); //�����ӵ�
	void EnemyBulletCreate(float); //�����л��ӵ�
	void CreateEnemyPlane(Enemy_Plane_Type Type); //���ݴ���ĵл����ʹ����л�
	void Small_Enemy_Plane_Create(float); //����С�л�
	void Middle_Enemy_Plane_Create(float); //�����ел�
	void Big_Enemy_Plane_Create(float); //������л�
	void CreateProp(Prop_Type CreateType,Point CreatePos); //���ݴ������ʹ�������
	void ClearAllEnemy();  //�����ǰ��Ļ�����ел������Ե�ָ������ʱ����
	void PrepareAnimation(); //Ԥ���涯����Դ
	void Clear_Del_Sprite(); //�����Ч�ӵ����л�������
	void GoToGameOver(); //��Ϸ����
	void GamePause(Ref*); //��ͣ��Ϸ
	void GameResume(Ref*); //������Ϸ
};

#endif