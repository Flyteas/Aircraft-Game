/* ����Ļ */
#ifndef _PLOTSCENE_H_
#define _PLOTSCENE_H
USING_NS_CC;
class PlotScene:public Layer
{
public:
	static Scene* CreateScene(int GameLevel);
	virtual bool init(int GameLevel);
	void GameBegin();
	static PlotScene* create(int GameLevel);
private:
	int GameLevel;
	bool IsEnterEnable;
	Label* PlotTextLabel;
	Label* EnterTextLabel;
	std::string LoadPlots(); //�����������
	std::string LoadEnterLabel(); //�����ǩ����
	std::string PlotsData;
	std::string PlotsDataTemp;
	std::string LableData;
	std::string LableDataTemp;
	void PlotDisplay(float); //������ʾ����

};

#endif