/* �Ŷ�Ļ */
#ifndef _TEAMSCENE_H_
#define _TEAMSCENE_H_
USING_NS_CC;
class TeamScene:public Layer
{
public:
	static Scene* CreateScene();
	virtual bool init();
	void ReturnBegin(Ref*); //���س�ʼĻ
	CREATE_FUNC(TeamScene);
private:
	Label* DataTextLabel;
	std::string LoadData(); //��������
	std::string Datas;
	std::string DatasTemp;
	void DataDisplay(float); //������ʾ

};

#endif