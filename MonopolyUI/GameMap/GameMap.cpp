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

std::vector<Place>& GameMap::getPlaces()
{
	return m_places;
}

Place& GameMap::getPlaceBySelectionNumber(int p_selectionNumber)
{
	for(int placeIndex = 0; placeIndex < m_places.size(); placeIndex++) {
		if(p_selectionNumber == m_places[placeIndex].getSelectionNumber()) {
			return m_places[placeIndex];
		}
	}
	return m_places.front();
}

int GameMap::getSize()
{
	return m_size;
}

void GameMap::initializeMap()
{
}

void GameMap::initializePlaces()
{
	int cornerPlaces = 4; // One cornerplace = 2 * width of normal place
	int width = static_cast<int>(m_size / (((m_numberOfPlaces / 4) + cornerPlaces)));
	int height = width * 2;

	// Chur
	Place placeChur("Kornplatz", "Chur", width, height);
	placeChur.setPrice(1200);
	placeChur.setPosition(m_size - 3 * width, height);
	placeChur.setColor(50, 0, 255);
	placeChur.setMapDirection(MapDirection_Bottom);
	m_places.push_back(placeChur);

	// Schaffhausen
	Place placeSchaffhausen("Vordergasse", "Schaffhausen", width, height);
	placeSchaffhausen.setPrice(1200);
	placeSchaffhausen.setPosition(m_size - 5 * width, height);
	placeSchaffhausen.setColor(50, 0, 255);
	placeSchaffhausen.setMapDirection(MapDirection_Bottom);
	m_places.push_back(placeSchaffhausen);

	// Aarau
	Place placeAarau("Rathausplatz", "Aarau", width, height);
	placeAarau.setPrice(2000);
	placeAarau.setPosition(m_size - 8 * width, height);
	placeAarau.setColor(50, 200, 255);
	placeAarau.setMapDirection(MapDirection_Bottom);
	m_places.push_back(placeAarau);

	// Neuenburg
	Place placeNeuenburg("Place Purry", "Neuenburg", width, height);
	placeNeuenburg.setPrice(2000);
	placeNeuenburg.setPosition(m_size - 10 * width, height);
	placeNeuenburg.setColor(50, 200, 255);
	placeNeuenburg.setMapDirection(MapDirection_Bottom);
	m_places.push_back(placeNeuenburg);

	// Thun
	Place placeThun("Hauptgasse", "Thun", width, height);
	placeThun.setPrice(2400);
	placeThun.setPosition(m_size - 11 * width, height);
	placeThun.setColor(50, 200, 255);
	placeThun.setMapDirection(MapDirection_Bottom);
	m_places.push_back(placeThun);

	// Width and height are exchanged on left and right side
	// Basel
	Place placeBasel("Steinen-Vorstadt", "Basel", height, width);
	placeBasel.setPrice(2800);
	placeBasel.setPosition(m_size - 13 * width, m_size - 10 * width);
	placeBasel.setColor(150, 0, 100);
	placeBasel.setMapDirection(MapDirection_Left);
	m_places.push_back(placeBasel);
}
