#include "stdafx.h"
#include "Place.h"

Place::Place(std::string p_name, std::string p_city, int p_width, int p_height) :
	m_name(p_name),
	m_city(p_city),
	m_width(p_width),
	m_height(p_height)
{
}

Place::~Place()
{
}

std::string Place::getName()
{
	return m_name;
}

std::string Place::getCity()
{
	return m_city;
}

void Place::setPosition(int p_posX, int p_posY)
{
	m_positionX = p_posX;
	m_positionY = p_posY;
}

int Place::getPosX() 
{
	return m_positionX;
}

int Place::getPosY()
{
	return m_positionY;
}

void Place::setColor(int p_red, int p_green, int p_blue)
{
	m_color.redValue = p_red;
	m_color.greenValue = p_green;
	m_color.blueValue = p_blue;
}

Color Place::getColor()
{
	return m_color;
}

int Place::getPrice()
{
	return m_price;
}


void Place::setPrice(int p_price)
{
	m_price = p_price;
}

int Place::getHeight()
{
	return m_height;
}

int Place::getWidth()
{
	return m_width;
}