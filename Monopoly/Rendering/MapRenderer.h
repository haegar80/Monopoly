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
private:
	GameMap& m_gameMap;
	bool m_selectionMode;

	void renderMap();
	void renderPlaceColor(Place& p_place);
	void renderPlaceText(Place& p_place, QGLWidget* p_widget);
};

#endif // MapRenderer_H