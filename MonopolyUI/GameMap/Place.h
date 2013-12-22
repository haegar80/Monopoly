#ifndef Place_H
#define Place_H

#include <string>

struct Color {
	int redValue;
	int greenValue;
	int blueValue;
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

	int getSelectionNumber();

	void setSelected(int p_selectionNumber);
	bool isSelected();

private:
	std::string m_name;
	std::string m_city;
	int m_width;
	int m_height;
	int m_positionX;
	int m_positionY;
	Color m_color;
	int m_price;
	int m_selectionNumber;
	bool m_isSelected;

	static int ms_latestSelectionNumber;
};

#endif // Place_H
