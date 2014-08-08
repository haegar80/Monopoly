#ifndef MainWindow_H
#define MainWindow_H
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class MainWindow : public QMainWindow
{
public:
	MainWindow();
	virtual ~MainWindow();

	void setupUi();
	void retranslateUi();
	QWidget* getMapWidget();

private:
    QWidget* m_centralwidget;
    QWidget* m_widget;
    QPushButton* m_quitButton;
    QMenuBar* m_menubar;
    QStatusBar* m_statusbar;
};

QT_END_NAMESPACE

#endif // MainWindow_H