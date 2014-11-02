#ifndef MapRenderer_H
#define MapRenderer_H

#include "../GameMap/GameMap.h"
#include <QtOpenGL/QGLWidget>
#include <vector>

class MapRenderer
{
public:
	MapRenderer(GameMap& p_gameMap);
	~MapRenderer();

	void render(QGLWidget* p_widget);
	void setSelectionMode();
	void selectObjects(std::vector<int>& p_selectedObjects);
	uint getTurnMapId() const {return mc_turnMapId; }
private:
	const uint mc_turnMapId;
	GameMap& m_gameMap;
	bool m_selectionMode;

	void renderMap();
	void renderPlaceContent(Place& p_place);
	void renderPlaceBorder(Place& p_place);
	void renderPlaceText(Place& p_place, QGLWidget* p_widget);
	void renderTurnMapArc();
	void renderBackgroundPolygon(int p_width, int p_height);
	void renderPlaceBottom(int p_height, int p_width, int p_posX, int p_posY);
	void renderPlaceLeft(int p_height, int p_width, int p_posX, int p_posY);
	void renderPlaceTop(int p_height, int p_width, int p_posX, int p_posY);
	void renderPlaceRight(int p_height, int p_width, int p_posX, int p_posY);
};

#endif // MapRenderer_H