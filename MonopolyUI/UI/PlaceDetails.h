#ifndef PlaceDetails_H
#define PlaceDetails_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTextBrowser>
#include "../GameMap/GameMap.h"

QT_BEGIN_NAMESPACE

class PlaceDetails : public QDialog
{
public:
	PlaceDetails(GameMap& p_gameMap);
	virtual ~PlaceDetails();

	void setupUi();
	void retranslateUi();
	void showDialog(uint p_selectionNumber);

private:
	GameMap& m_gameMap;
    QLabel* m_placeLabel;
    QTextBrowser* m_placeDetailsText;
};

QT_END_NAMESPACE

#endif // PlaceDetails_H

