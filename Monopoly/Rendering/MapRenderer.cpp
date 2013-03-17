#include "stdafx.h"
#include "MapRenderer.h"
#include <GL/gl.h>
#include <sstream>

MapRenderer::MapRenderer(GameMap& p_gameMap) :
	m_gameMap(p_gameMap)
{
}

MapRenderer::~MapRenderer()
{
}

void MapRenderer::render(QGLWidget* p_widget) {
	// Read Places from Gamemap
	std::vector<Place> places = m_gameMap.getPlaces();
	for(UINT32 i=0; i < places.size(); i++) {
		renderPlaceColor(places[i]);
		renderPlaceText(places[i], p_widget);
	}
}

void MapRenderer::renderPlaceColor(Place& p_place)
{
	Color color = p_place.getColor();
	glColor3ub(color.redValue, color.greenValue, color.blueValue);
	// integer precise is enough
	int height = p_place.getHeight();
	int heightColor = height / 4;
	int width = p_place.getWidth();
	int posX = p_place.getPosX();
	int posY = p_place.getPosY();
	int posYColor = posY - (3 * heightColor);

	glBegin(GL_POLYGON);
	glVertex3i(posX, posYColor, -1);
	glVertex3i(posX + width, posYColor, -1);
	glVertex3i(posX + width, posYColor - heightColor, -1);
	glVertex3i(posX, posYColor - heightColor, -1);
	glEnd();

	glColor3ub(40, 40, 40);
	glBegin(GL_LINE_LOOP);
	glVertex3i(posX, posY - height, -1);
	glVertex3i(posX, posY, -1);
	glVertex3i(posX + width, posY, -1);
	glVertex3i(posX + width, posY - height, -1);
	glEnd();
}

void MapRenderer::renderPlaceText(Place& p_place, QGLWidget* p_widget)
{
	std::string name = p_place.getCity() + " " + p_place.getName();
	int height = p_place.getHeight();
	int width = p_place.getWidth();
	int posX = p_place.getPosX();
	int posY = p_place.getPosY();
	int posYText = posY - (height / 2);
	p_widget->renderText(posX, posYText, -1, QString::fromUtf8(p_place.getCity().c_str()));
	posYText += 10;
	p_widget->renderText(posX, posYText, -1, QString::fromUtf8(p_place.getName().c_str()));
	posYText += 20;
	int price = p_place.getPrice();
	std::stringstream priceString;
    priceString << price;
	p_widget->renderText(posX, posYText, -1, QString::fromUtf8(priceString.str().c_str()));
}