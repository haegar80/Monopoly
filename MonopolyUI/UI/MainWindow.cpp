#include "stdafx.h"
#include "MainWindow.h"

MainWindow::MainWindow(void)
{
}


MainWindow::~MainWindow(void)
{
}

void MainWindow::SetupUi()
{
	if (this->objectName().isEmpty()) {
		this->setObjectName(QString::fromUtf8("MainWindow"));
	}
    this->resize(1024, 1024);
    m_Centralwidget = new QWidget(this);
    m_Centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
	m_Centralwidget->setStyleSheet("background:rgb(50,50,50)");
    m_Widget = new QWidget(m_Centralwidget);
    m_Widget->setObjectName(QString::fromUtf8("widget"));
    m_Widget->setGeometry(QRect(146, 12, 1024, 1024));
    m_Widget->setAutoFillBackground(true);

    m_QuitButton = new QPushButton(m_Centralwidget);
    m_QuitButton->setObjectName(QString::fromUtf8("quitButton"));
    m_QuitButton->setGeometry(QRect(20, 1000, 75, 23));
    this->setCentralWidget(m_Centralwidget);
    m_Menubar = new QMenuBar(this);
    m_Menubar->setObjectName(QString::fromUtf8("menubar"));
    m_Menubar->setGeometry(QRect(0, 0, 800, 21));
    this->setMenuBar(m_Menubar);
	this->setWindowState(Qt::WindowFullScreen);

    RetranslateUi();
    QObject::connect(m_QuitButton, SIGNAL(pressed()), this, SLOT(close()));

    QMetaObject::connectSlotsByName(this);
}

void MainWindow::RetranslateUi()
{
    this->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    m_QuitButton->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
}

QWidget* MainWindow::GetMapWidget()
{
	return m_Widget;
}