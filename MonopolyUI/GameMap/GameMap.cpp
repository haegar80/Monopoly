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

	// Bottom
	Place placeChur("Kornplatz", "Chur", width, height);
	placeChur.setPrice(60);
	placeChur.setPosition(m_size - 3 * width, height);
	placeChur.setColor(50, 0, 255);
	placeChur.setMapDirection(MapDirection_Bottom);
	placeChur.loadImage();
	m_places.push_back(placeChur);

	Place placeSchaffhausen("Vordergasse", "Schaffhausen", width, height);
	placeSchaffhausen.setPrice(60);
	placeSchaffhausen.setPosition(m_size - 5 * width, height);
	placeSchaffhausen.setColor(50, 0, 255);
	placeSchaffhausen.setMapDirection(MapDirection_Bottom);
	placeSchaffhausen.loadImage();
	m_places.push_back(placeSchaffhausen);

	Place placeAarau("Rathausplatz", "Aarau", width, height);
	placeAarau.setPrice(100);
	placeAarau.setPosition(m_size - 8 * width, height);
	placeAarau.setColor(50, 200, 255);
	placeAarau.setMapDirection(MapDirection_Bottom);
	placeAarau.loadImage();
	m_places.push_back(placeAarau);

	Place placeNeuenburg("Place Purry", "Neuenburg", width, height);
	placeNeuenburg.setPrice(100);
	placeNeuenburg.setPosition(m_size - 10 * width, height);
	placeNeuenburg.setColor(50, 200, 255);
	placeNeuenburg.setMapDirection(MapDirection_Bottom);
	placeNeuenburg.loadImage();
	m_places.push_back(placeNeuenburg);

	Place placeThun("Hauptgasse", "Thun", width, height);
	placeThun.setPrice(120);
	placeThun.setPosition(m_size - 11 * width, height);
	placeThun.setColor(50, 200, 255);
	placeThun.setMapDirection(MapDirection_Bottom);
	placeThun.loadImage();
	m_places.push_back(placeThun);

	// Left
	// Width and height are exchanged on left and right side
	Place placeBasel("Steinen-Vorstadt", "Basel", height, width);
	placeBasel.setPrice(140);
	placeBasel.setPosition(m_size - 13 * width, m_size - 10 * width);
	placeBasel.setColor(150, 0, 100);
	placeBasel.setMapDirection(MapDirection_Left);
	placeBasel.loadImage();
	m_places.push_back(placeBasel);

	Place placeSolothurn("Hauptgasse", "Solothurn", height, width);
	placeSolothurn.setPrice(140);
	placeSolothurn.setPosition(m_size - 13 * width, m_size - 8 * width);
	placeSolothurn.setColor(150, 0, 100);
	placeSolothurn.setMapDirection(MapDirection_Left);
	placeSolothurn.loadImage();
	m_places.push_back(placeSolothurn);

	Place placeLugano("Via Nassa", "Lugano", height, width);
	placeLugano.setPrice(160);
	placeLugano.setPosition(m_size - 13 * width, m_size - 7 * width);
	placeLugano.setColor(150, 0, 100);
	placeLugano.setMapDirection(MapDirection_Left);
	placeLugano.loadImage();
	m_places.push_back(placeLugano);

	Place placeBiel("Nidaugasse", "Biel", height, width);
	placeBiel.setPrice(180);
	placeBiel.setPosition(m_size - 13 * width, m_size - 5 * width);
	placeBiel.setColor(150, 0, 100);
	placeBiel.setMapDirection(MapDirection_Left);
	placeBiel.loadImage();
	m_places.push_back(placeBiel);

	Place placeFreiburg("Bahnhofstrasse", "Freiburg", height, width);
	placeFreiburg.setPrice(180);
	placeFreiburg.setPosition(m_size - 13 * width, m_size - 3 * width);
	placeFreiburg.setColor(150, 0, 100);
	placeFreiburg.setMapDirection(MapDirection_Left);
	placeFreiburg.loadImage();
	m_places.push_back(placeFreiburg);

	Place placeLaChauxDeFonds("Av. L.-Robert", "La Chaux-de-Fonds", height, width);
	placeLaChauxDeFonds.setPrice(200);
	placeLaChauxDeFonds.setPosition(m_size - 13 * width, m_size - 2 * width);
	placeLaChauxDeFonds.setColor(150, 0, 100);
	placeLaChauxDeFonds.setMapDirection(MapDirection_Left);
	placeLaChauxDeFonds.loadImage();
	m_places.push_back(placeLaChauxDeFonds);
}
