#ifndef GLWidget_H
#define GLWidget_H
#include <QtOpenGL/QGLWidget>
#include "../Rendering/MapRenderer.h"

class GLWidget : public QGLWidget
{
public:
	GLWidget(MapRenderer& p_mapRenderer, QWidget* p_parent = NULL);
	virtual ~GLWidget();
protected:
	void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
	void wheelEvent(QWheelEvent *event);
private:
	struct Hit 
	{
		int id_count, zmin, zmax, id;
	};
	MapRenderer& m_mapRenderer;
	double m_width;
	double m_height;
	double m_currentZoom;
	double m_translateX;
	double m_translateY;
	double m_cameraAngleX;
	double m_cameraAngleY;
	double m_cameraAngleZ;
	double m_lastXPos;
	double m_lastYPos;
	bool m_mousePressed;
	bool m_moveMap;
	bool m_turnMap;

	void processMovingMap(double p_xPosDelta, double p_yPosDelta);
	void processTurningMap(double p_xPosDelta, double p_yPosDelta);
	void processFindingObject(double p_xPos, double p_yPos);

	double getAngleZChange(double p_xPosDelta, double p_yPosDelta);
	bool validateAngleZChange(double p_xPosDelta, double p_yPosDelta);
};

#endif // GLWidget_H