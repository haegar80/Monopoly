#include "stdafx.h"
#include <ctime>
#include <QtGui/QMouseEvent>
#include <qmatrix4x4.h>
#include "GLWidget.h"
#include <gl/GLU.h>

GLWidget::GLWidget(MapRenderer& p_mapRenderer, PlaceDetails& p_placeDetails, QWidget* p_parent) : QGLWidget(p_parent),
	m_mapRenderer(p_mapRenderer),
	m_placeDetails(p_placeDetails),
	m_width(0.0),
	m_height(0.0),
	m_currentZoom(-2200.0),
	m_translateX(-500.0),
	m_translateY(-400.0),
	m_cameraAngleX(-30.0),
	m_cameraAngleY(0.0),
	m_cameraAngleZ(0.0),
	m_lastXPos(0.0),
	m_lastYPos(0.0),
	m_mousePressed(false),
	m_moveMap(false),
	m_turnMap(false)
{
    setMouseTracking(true);
}

GLWidget::~GLWidget(void)
{
}

void GLWidget::initializeGL() 
{
	QGLWidget::setAutoBufferSwap(false);
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
	gluPerspective(30.0, m_width / m_height, 1.0, 10000.0);

	// ModelView matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	QGLWidget::qglClearColor(QColor(100, 100, 100, 0));
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	m_mapRenderer.render(this);
	QGLWidget::swapBuffers();
}

void GLWidget::mousePressEvent(QMouseEvent *event) 
{
	m_mousePressed = true;
	if(Qt::RightButton == event->buttons()) {
		m_moveMap = true;
	}
	processFindingObject(event->x(), m_height - event->y());
	m_lastXPos = event->x();
	m_lastYPos = event->y();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event) 
{
	m_mousePressed = false;
	m_moveMap = false;
	m_turnMap = false;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) 
{
	int currentXPos = event->x();
	int currentYPos = event->y();
	if(!m_mousePressed) {
		return;
	}
	if(Qt::LeftButton == event->buttons()) {
		processFindingObject(currentXPos, m_height - currentYPos);
	}
	else if(Qt::RightButton == event->buttons()) {
		double deltaX = currentXPos - m_lastXPos;
		double deltaY = currentYPos - m_lastYPos;
	
	    if(m_moveMap && m_turnMap) {
			processTurningMap(deltaX, deltaY);
		}
		else if(m_moveMap && !m_turnMap) {
			processMovingMap(deltaX, deltaY);
		}
	}
    m_lastXPos = currentXPos;
	m_lastYPos = currentYPos;
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
	m_translateX += p_xPosDelta;
	m_translateY -= p_yPosDelta;

	updateGL();
}

void GLWidget::processTurningMap(double p_xPosDelta, double p_yPosDelta)
{
	m_cameraAngleZ += getAngleZChange(p_xPosDelta, p_yPosDelta);

	if(m_cameraAngleZ > 360.0) {
		m_cameraAngleZ -= 360.0;
	}
	if(m_cameraAngleZ < 0) {
		m_cameraAngleZ += 360.0;
	}
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
	gluPickMatrix(p_xPos, p_yPos, 10.0, 10.0, view);
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
			if(m_mapRenderer.getTurnMapId() == pHitArray[i].id && m_moveMap) {
				m_turnMap = true;
				return;
			}
			selectedObjects.push_back(pHitArray[i].id);
		}
	}
	else {
		selectedObjects.push_back(0);
	}

	if(m_moveMap) {
		return;
	}
	m_mapRenderer.selectObjects(selectedObjects);
	updateGL();

	int selectionNumber = selectedObjects.front();
	if(0 != selectionNumber && m_mapRenderer.getTurnMapId() != selectionNumber) {
		showPlaceDetailsWidget(selectionNumber);
	}
}

void GLWidget::showPlaceDetailsWidget(int p_selectionNumber)
{
	m_placeDetails.retranslateUi();
	m_placeDetails.showDialog(p_selectionNumber);
}

double GLWidget::getAngleZChange(double p_xPosDelta, double p_yPosDelta) 
{
	if(!validateAngleZChange(p_xPosDelta, p_yPosDelta)) {
		return 0.0;
	}
	
	bool turnClockWise = true;
	if(m_cameraAngleZ >= 0 && m_cameraAngleZ < 45.0) {
		if(p_yPosDelta < 0.0) {
			turnClockWise = false;
		}
	}
	if(m_cameraAngleZ >= 45 && m_cameraAngleZ < 90.0) {
		if(p_xPosDelta < 0.0) {
			turnClockWise = false;
		}
	}
	if(m_cameraAngleZ >= 90.0 && m_cameraAngleZ < 135.0) {
		if(p_xPosDelta < 0.0) {
			turnClockWise = false;
		}
	}
	if(m_cameraAngleZ >= 135.0 && m_cameraAngleZ < 180.0) {
		if(p_yPosDelta > 0.0) {
			turnClockWise = false;
		}
	}
	if(m_cameraAngleZ >= 180.0 && m_cameraAngleZ < 225.0) {
		if(p_yPosDelta > 0.0) {
			turnClockWise = false;
		}
	}
	if(m_cameraAngleZ >= 225.0 && m_cameraAngleZ < 270.0) {
		if(p_xPosDelta > 0.0) {
			turnClockWise = false;
		}
	}
	if(m_cameraAngleZ >= 270.0 && m_cameraAngleZ < 315.0) {
		if(p_xPosDelta > 0.0) {
			turnClockWise = false;
		}
	}
	if(m_cameraAngleZ >= 315.0) {
		if(p_yPosDelta < 0.0) {
			turnClockWise = false;
		}
	}

	double deltaAngleZ = 0.0;
	if(turnClockWise) {
		deltaAngleZ -= 1.0;
	}
	else {
		deltaAngleZ += 1.0;
	}
	return deltaAngleZ;
}

bool GLWidget::validateAngleZChange(double p_xPosDelta, double p_yPosDelta)
{
	if((p_xPosDelta <= 0.9 && p_xPosDelta >= -0.9) && (p_yPosDelta <= 0.9 && p_yPosDelta >= -0.9)) {
		return false;
	}
	
	return true;
}