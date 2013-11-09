#ifndef GameMap_H
#define GameMap_H

#include "Place.h"
#include <vector>

class GameMap
{
public:
	GameMap(int p_size, int p_numberOfPlaces);
	~GameMap();

	std::vector<Place>& getPlaces();
	int getSize();

private:
	int m_size;
	int m_numberOfPlaces;
	std::vector<Place> m_places;

    void initializeMap();
	void initializePlaces();
};

#endif // GameMap_H
