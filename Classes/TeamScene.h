/* 团队幕 */
#ifndef _TEAMSCENE_H_
#define _TEAMSCENE_H_
USING_NS_CC;
class TeamScene:public Layer
{
public:
	static Scene* CreateScene();
	virtual bool init();
	void ReturnBegin(Ref*); //返回初始幕
	CREATE_FUNC(TeamScene);
private:
	Label* DataTextLabel;
	std::string LoadData(); //载入文字
	std::string Datas;
	std::string DatasTemp;
	void DataDisplay(float); //逐字显示

};

#endif