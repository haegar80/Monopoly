#ifndef Place_H
#define Place_H

#include <qimage.h>
#include <string>

struct Color {
	int redValue;
	int greenValue;
	int blueValue;
};

enum EMapDirection {
	MapDirection_InitialValue = 0,
    MapDirection_Bottom = 1,
	MapDirection_Left = 2,
	MapDirection_Top = 3,
	MapDirection_Right = 4
};

class Place
{
public:
	Place(std::string p_name, std::string p_city, int p_width, int p_height);
	~Place();

	std::string getName();
    std::string getCity();

	void setPosition(int p_posX, int p_posY);
	int getPosX();
	int getPosY();

	void setColor(int p_red, int p_green, int p_blue);
	Color getColor();
	
	int getPrice();
	void setPrice(int p_price);

	int getHeight();
	int getWidth();

	void setMapDirection(EMapDirection p_mapDirection);
	EMapDirection getMapDirection();

	int getSelectionNumber();

	void setSelected(int p_selectionNumber);
	bool isSelected();

	void loadImage();
	QImage getImage();

private:
	std::string m_name;
	std::string m_city;
	int m_width;
	int m_height;
	int m_positionX;
	int m_positionY;
	Color m_color;
	EMapDirection m_mapDirection;
	int m_price;
	int m_selectionNumber;
	bool m_isSelected;
	QImage m_image;

	static int ms_latestSelectionNumber;
};

#endif // Place_H
