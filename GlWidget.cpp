/// \file
/// \date 2014-01-01
/// \author Xavier Michelon
///
/// \brief Implementation of custom OpenGL widget class


#include "stdafx.h"
#include "GlWidget.h"
#include "GameEngine.h"
#include "Constants.h"


//**********************************************************************************************************************
/// \param[in] parent The parent widget
//**********************************************************************************************************************
GlWidget::GlWidget(QWidget* parent)
   : QGLWidget(QGLFormat(QGL::AlphaChannel | QGL::DoubleBuffer | QGL::Rgba), parent)
{
   this->setAutoBufferSwap(false);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
GlWidget::~GlWidget()
{

}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GlWidget::initializeGL()
{
   qDebug(__FUNCTION__"()");
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GlWidget::paintGL()
{
   gameEngine().render();
   this->swapBuffers();
}


//**********************************************************************************************************************
/// \param[in] width The width of the widget in pixels
/// \param[in] height The height of the widget in pixels
//**********************************************************************************************************************
void GlWidget::resizeGL(int width, int height)
{
   qDebug(__FUNCTION__"()");
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, kBoardWidth * kCellSize, kBoardHeigth * kCellSize, 0, -1.0, 0.0);
   glMatrixMode(GL_MODELVIEW);
}
