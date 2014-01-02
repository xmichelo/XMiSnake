/// \file
/// \date 2014-01-02
/// \author Xavier Michelon
///
/// \brief Declaration of snake class


#include "stdafx.h"
#include "Snake.h"
#include "Constants.h"


void renderSnakePart(qint32 x, qint32 y); ///< Render a portion (square) of a snake


//**********************************************************************************************************************
/// \param[in] position The position of the snake part
//**********************************************************************************************************************
void renderSnakePart(QPoint const& position)
{
   qint32 const xMin((position.x() * kCellSize) + 1);
   qint32 const xMax(xMin + kCellSize - 2);
   qint32 const yMin((position.y() * kCellSize) + 1);
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
/// \param[in] position The initial position of the snake
//**********************************************************************************************************************
Snake::Snake(QPoint const& position)
   : points_(1, position)
{

}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
Snake::~Snake()
{

}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void Snake::render()
{
   glColor3ub(255, 255, 255);
   for (DequeQPoint::const_iterator it = points_.begin(); it != points_.end(); ++it)
      renderSnakePart(*it);
}
