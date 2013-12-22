#include "stdafx.h"
#include <ctime>
#include <QtGui/QMouseEvent>
#include <qmatrix4x4.h>
#include "GLWidget.h"
#include <gl/GLU.h>

GLWidget::GLWidget(MapRenderer& p_mapRenderer, QWidget* p_parent) : QGLWidget(p_parent),
	m_mapRenderer(p_mapRenderer),
	m_width(0.0),
	m_height(0.0),
	m_currentZoom(-2100.0),
	m_translateX(-500.0),
	m_translateY(-500.0),
	m_cameraAngleX(-30.0),
	m_cameraAngleY(0.0),
	m_cameraAngleZ(0.0),
	m_pressedXPos(0.0),
	m_pressedYPos(0.0),
	m_mousePressed(false),
	m_turnMap(false)
{
    setMouseTracking(true);
}

GLWidget::~GLWidget(void)
{
}

void GLWidget::initializeGL() 
{
	QGLWidget::setAutoBufferSwap(true);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void GLWidget::resizeGL(int w, int h)
{
	m_width = static_cast<double>(w);
	m_height = static_cast<double>(h);

	// Viewport
	glViewport(0, 0, w, h);
    
	// Projektionsmatrix
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1.0, 1.0, 10000.0);

	// ModelView matrix
	glMatrixMode(GL_MODELVIEW);
}

void GLWidget::paintGL()
{
	// Translate object coordinates to model coordinates
	QMatrix4x4 modelMatrix;
	modelMatrix.translate(m_translateX, m_translateY, m_currentZoom);

	// Viewmatrix
	QMatrix4x4 viewMatrix;
	viewMatrix.rotate(m_cameraAngleY, 0.0, 1.0, 0.0);
	viewMatrix.rotate(m_cameraAngleX, 1.0, 0.0, 0.0);
	viewMatrix.rotate(m_cameraAngleZ, 0.0, 0.0, 1.0);
	
	QMatrix4x4 modelViewMatrix = modelMatrix * viewMatrix;

    glLoadMatrixd(modelViewMatrix.data());

	QGLWidget::qglClearColor(QColor(255, 255, 255));
	glClear(GL_COLOR_BUFFER_BIT);

	m_mapRenderer.render(this);
	glFlush();
}

void GLWidget::mousePressEvent(QMouseEvent *event) 
{
	m_pressedXPos = event->x();
	m_pressedYPos = event->y();
	m_mousePressed = true;
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event) 
{
	m_mousePressed = false;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) 
{
	if(m_mousePressed && Qt::RightButton == event->buttons()) {
		double deltaX = event->x() - m_pressedXPos;
	    double deltaY = event->y() - m_pressedYPos;
		processMovingMap(deltaX, deltaY);
	}
	else { 
		if(Qt::LeftButton == event->buttons()) {
			processFindingObject(event->x(), m_height - event->y());
			if(m_mousePressed) {
				if(m_turnMap) {
					double deltaX = event->x() - m_pressedXPos;
	                double deltaY = event->y() - m_pressedYPos;
					processTurningMap(deltaX, deltaY);
					m_turnMap = false;
		        }
		    }
		}
	}
}

void GLWidget::wheelEvent(QWheelEvent *event) 
{
	if(event->delta() > 0) {
		m_currentZoom -= 200;
	}
	else {
		m_currentZoom += 200;
	}
	updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent* event) 
{
    switch(event->key()) {
    case Qt::Key_Escape:
        close();
        break;
    default:
        event->ignore();
        break;
    }
}

void GLWidget::processMovingMap(double p_xPosDelta, double p_yPosDelta) 
{
	m_translateX += getTranslateX(p_xPosDelta);
	m_translateY += getTranslateY(p_yPosDelta);

	updateGL();
}

void GLWidget::processTurningMap(double p_xPosDelta, double p_yPosDelta)
{
   m_cameraAngleZ += getAngleZChange(p_xPosDelta, p_yPosDelta); 
   updateGL();
}

void GLWidget::processFindingObject(double p_xPos, double p_yPos)
{
	int view[4];
	uint selectionBuffer[32] = {0};
	int numberOfSelectedObjects = 0;

	// For selected objects
	glSelectBuffer(32, selectionBuffer);
	glGetIntegerv(GL_VIEWPORT, view);
	glRenderMode(GL_SELECT);

	// Clearing object names for identifying objects
	glInitNames();
 	glPushName(0);

	// Backup projection matrix in order restore it after view restriction around cursor area
	glMatrixMode(GL_PROJECTION);
 	glPushMatrix();
	glLoadIdentity();
 
 	// Restrict the draw to an area around the cursor
	gluPickMatrix(p_xPos, p_yPos, 1.0, 1.0, view);
    gluPerspective(30.0, 1.0, 1.0, 10000.0); 

	// Redraw with restricted view area
	glMatrixMode(GL_MODELVIEW);
	m_mapRenderer.setSelectionMode();
	m_mapRenderer.render(this);

	// Restore projection matrix
	glMatrixMode(GL_PROJECTION);
 	glPopMatrix();

	numberOfSelectedObjects = glRenderMode(GL_RENDER);
	glMatrixMode(GL_MODELVIEW);

    std::vector<int> selectedObjects; 
	if(numberOfSelectedObjects > 0) {
		Hit* pHitArray = reinterpret_cast<Hit*>(selectionBuffer);
	    for(int i = 0; i < numberOfSelectedObjects; i++) {
			if(0 == pHitArray[i].id) {
				m_turnMap = true;
				return;
			}
			selectedObjects.push_back(pHitArray[i].id);
		}
	}
	else {
		selectedObjects.push_back(0);
	}
	m_mapRenderer.selectObjects(selectedObjects);
	updateGL();
}

double GLWidget::getTranslateX(double p_xPosDelta)
{
	double translateX = 0.0;
	if(p_xPosDelta > 0) {
		translateX += 5.0;
	}
	else {
		translateX -= 5.0;
	}
	return translateX;
}

double GLWidget::getTranslateY(double p_yPosDelta)
{
	double translateY = 0.0;
	if(p_yPosDelta > 0) {
		translateY -= 5.0;
	}
	else {
		translateY += 5.0;
	}
	return translateY;
}

double GLWidget::getAngleZChange(double p_xPosDelta, double p_yPosDelta) 
{
	double angleZChange = 0.0;
	if(p_xPosDelta < -10.0 && p_yPosDelta > 10.0) { 
		angleZChange -= 1.0; 
	}
	else if (p_xPosDelta > 10.0 && p_yPosDelta < -10.0) {
		angleZChange += 1.0;
	}
	return angleZChange;
}