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
   , direction_(eUp)
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


//**********************************************************************************************************************
/// \param[in] direction The new direction of the snake
//**********************************************************************************************************************
void Snake::setDirection(EDirection direction)
{
   direction_ = direction;
   qDebug("New snake direction: %i", direction_);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
bool Snake::move()
{
   Q_ASSERT(points_.size() > 0);
   QPoint point(points_.back());
   switch (direction_)
   {
   case eUp:
      if (point.y() <= 0)
         return false;
      point.setY(point.y() - 1);
      break;
   case eDown:
      if (point.y() >= kBoardHeigth - 1)
         return false;
      point.setY(point.y() + 1);
      break;
   case eLeft:
      if (point.x() <= 0)
         return false;
      point.setX(point.x() - 1);
      break;
   case eRight:
      if (point.x() >= kBoardWidth - 1)
         return false;
      point.setX(point.x() + 1);
      break;
   default:
      Q_ASSERT(false);
      return false;
   }
   points_.push_back(point);
   points_.pop_front();
   return true;
}
