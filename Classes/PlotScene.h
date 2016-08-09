/* 剧情幕 */
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
	std::string LoadPlots(); //载入剧情文字
	std::string LoadEnterLabel(); //载入标签文字
	std::string PlotsData;
	std::string PlotsDataTemp;
	std::string LableData;
	std::string LableDataTemp;
	void PlotDisplay(float); //逐字显示剧情

};

#endif