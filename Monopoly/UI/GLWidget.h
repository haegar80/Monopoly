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
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
	MapRenderer& m_mapRenderer;
};

#endif // GLWidget_H