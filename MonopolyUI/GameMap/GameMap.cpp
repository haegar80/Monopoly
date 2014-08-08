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
	for(UINT16 placeIndex = 0; placeIndex < m_places.size(); placeIndex++) {
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
	int width = m_size / ((m_numberOfPlaces / 4) + 2);
	int height = width * 2;

	// Chur
	Place placeChur("Kornplatz", "Chur", width, height);
	placeChur.setPrice(1200);
	placeChur.setPosition(m_size - 3 * width, height);
	placeChur.setColor(150, 0, 100);
	m_places.push_back(placeChur);

	// Schaffhausen
	Place placeSchaffhausen("Vordergasse", "Schaffhausen", width, height);
	placeSchaffhausen.setPrice(1200);
	placeSchaffhausen.setPosition(m_size - 5 * width, height);
	placeSchaffhausen.setColor(150, 0, 100);
	m_places.push_back(placeSchaffhausen);

	// Aarau
	Place placeAarau("Rathausplatz", "Aarau", width, height);
	placeAarau.setPrice(2000);
	placeAarau.setPosition(m_size - 8 * width, height);
	placeAarau.setColor(50, 0, 255);
	m_places.push_back(placeAarau);

	// Neuenburg
	Place placeNeuenburg("Place Purry", "Neuenburg", width, height);
	placeNeuenburg.setPrice(2000);
	placeNeuenburg.setPosition(m_size - 9 * width, height);
	placeNeuenburg.setColor(50, 0, 255);
	m_places.push_back(placeNeuenburg);
}
