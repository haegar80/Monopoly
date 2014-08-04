#include "stdafx.h"
#include "PlaceDetails.h"

PlaceDetails::PlaceDetails(const GameMap& pc_gameMap) :
	m_gameMap(pc_gameMap)
{
}


PlaceDetails::~PlaceDetails(void)
{
	delete m_placeLabel;
	delete m_placeDetailsText;
}

void PlaceDetails::SetupUi()
{
	if (this->objectName().isEmpty()) {
		this->setObjectName(QString::fromUtf8("PlaceDetails"));
	}
	this->resize(400, 300);
	this->setWindowTitle(QString::fromUtf8("PlaceInformation"));
	
	m_placeLabel = new QLabel(this);
    m_placeLabel->setObjectName(QString::fromUtf8("placeLabel"));
    m_placeLabel->setGeometry(QRect(70, 20, 91, 31));
    m_placeDetailsText = new QTextBrowser(this);
    m_placeDetailsText->setObjectName(QString::fromUtf8("placeDetailsText"));
    m_placeDetailsText->setGeometry(QRect(10, 80, 211, 161));

    RetranslateUi();

    QMetaObject::connectSlotsByName(this);
}

void PlaceDetails::RetranslateUi()
{
    this->setWindowTitle(QApplication::translate("PlaceDetails", "PlaceDetails", 0, QApplication::UnicodeUTF8));
	m_placeDetailsText->setHtml(QApplication::translate("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Preis: Blabla</span></p></body></html>", 0, QApplication::UnicodeUTF8));
}
