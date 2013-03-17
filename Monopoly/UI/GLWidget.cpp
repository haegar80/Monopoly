#include "stdafx.h"
#include <ctime>
#include <QtGui/QMouseEvent>
#include "GLWidget.h"

GLWidget::GLWidget(MapRenderer& p_mapRenderer, QWidget* p_parent) : QGLWidget(p_parent),
	m_mapRenderer(p_mapRenderer)
{
    setMouseTracking(true);
}

GLWidget::~GLWidget(void)
{
}

void GLWidget::initializeGL() {
	QGLWidget::setAutoBufferSwap(true);
}

void GLWidget::resizeGL(int w, int h) {
	glViewport(0, 0, w, h);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho(0.0, w, h, 0.0, -1.0, 1.0);
}

void GLWidget::paintGL() {
	QGLWidget::qglClearColor(QColor(150, 200, 150));
	glClear(GL_COLOR_BUFFER_BIT);

	m_mapRenderer.render(this);

    glFlush();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {

}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
}

void GLWidget::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key_Escape:
        close();
        break;
    default:
        event->ignore();
        break;
    }
}