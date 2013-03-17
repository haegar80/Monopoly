#include "stdafx.h"
#include "GameMap.h"

GameMap::GameMap(int p_size, int p_numberOfPlaces) :
	m_size(p_size),
	m_numberOfPlaces(p_numberOfPlaces)
{
	initializePlaces();
}

GameMap::~GameMap()
{
}

std::vector<Place> GameMap::getPlaces()
{
	return m_places;
}

void GameMap::initializeMap()
{
}

void GameMap::initializePlaces()
{
	int width = m_size / ((m_numberOfPlaces / 4) + 2);
	int height = width * 2;

	// Chur
	Place placeChur("Kornplatz", "Chur", width, height);
	placeChur.setPrice(1200);
	placeChur.setPosition(m_size - 3 * width, m_size);
	placeChur.setColor(150, 0, 100);
	m_places.push_back(placeChur);
}
