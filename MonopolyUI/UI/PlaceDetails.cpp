#include "stdafx.h"
#include "PlaceDetails.h"

PlaceDetails::PlaceDetails(GameMap& p_gameMap) :
	m_gameMap(p_gameMap)
{
}


PlaceDetails::~PlaceDetails(void)
{
	delete m_placeLabel;
	delete m_placeDetailsText;
}

void PlaceDetails::setupUi()
{
	if (this->objectName().isEmpty()) {
		this->setObjectName(QString::fromUtf8("PlaceDetails"));
	}
	this->resize(231, 300);
	this->setWindowTitle(QString::fromUtf8("PlaceInformation"));
	this->setModal(true);

	m_placeLabel = new QLabel(this);
    m_placeLabel->setObjectName(QString::fromUtf8("placeLabel"));
    m_placeLabel->setGeometry(QRect(70, 20, 91, 31));
    m_placeDetailsText = new QTextBrowser(this);
    m_placeDetailsText->setObjectName(QString::fromUtf8("placeDetailsText"));
    m_placeDetailsText->setGeometry(QRect(10, 80, 211, 161));

	 this->setWindowTitle(QApplication::translate("PlaceDetails", "PlaceDetails", 0, QApplication::UnicodeUTF8));
	m_placeDetailsText->setHtml(QApplication::translate("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Preis: Blabla</span></p></body></html>", 0, QApplication::UnicodeUTF8));

    retranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void PlaceDetails::retranslateUi()
{
	m_placeLabel->clear();
   
}

void PlaceDetails::showDialog(uint p_selectionNumber)
{
	Place& foundPlace = m_gameMap.getPlaceBySelectionNumber(p_selectionNumber);
	m_placeLabel->setText(QString::fromUtf8(foundPlace.getCity().c_str()));
	m_placeLabel->setVisible(true);

	this->showNormal();
}
