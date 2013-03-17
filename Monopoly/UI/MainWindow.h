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

	void SetupUi();
	void RetranslateUi();
	QWidget* GetMapWidget();

private:
    QWidget* m_Centralwidget;
    QWidget* m_Widget;
    QPushButton* m_QuitButton;
    QMenuBar* m_Menubar;
    QStatusBar* m_Statusbar;
};

QT_END_NAMESPACE

#endif // MainWindow_H