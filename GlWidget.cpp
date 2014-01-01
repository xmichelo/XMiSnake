/// \file
/// \date 2014-01-01
/// \author Xavier Michelon
///
/// \brief Implementation of custom OpenGL widget class


#include "stdafx.h"
#include "GlWidget.h"
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
void drawCell(qint32 x, qint32 y)
{
   qint32 const xMin((x * kCellSize) + 1);
   qint32 const xMax(xMin + kCellSize - 2);
   qint32 const yMin((y * kCellSize) + 1);
   qint32 const yMax(yMin + kCellSize - 2);
   glColor3ub(255, 255, 255);
   glBegin(GL_QUADS);
   glVertex2i(xMin, yMin);
   glVertex2i(xMax, yMin);
   glVertex2i(xMax, yMax);
   glVertex2i(xMin, yMax);
   glEnd();
}

//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GlWidget::paintGL()
{
   qDebug(__FUNCTION__"()");
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
   for (qint32 y = 0; y < kBoardHeigth; ++y)
      for (qint32 x = 0; x < kBoardWidth; ++x)
         drawCell(x, y);
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
