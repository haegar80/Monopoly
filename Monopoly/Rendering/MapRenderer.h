#ifndef MapRenderer_H
#define MapRenderer_H

#include "../GameMap/GameMap.h"
#include <QtOpenGL/QGLWidget>

class MapRenderer
{
public:
	MapRenderer(GameMap& p_gameMap);
	~MapRenderer();

	void render(QGLWidget* p_widget);

private:
	GameMap& m_gameMap;

	void renderPlaceColor(Place& p_place);
	void renderPlaceText(Place& p_place, QGLWidget* p_widget);
};

#endif // MapRenderer_H