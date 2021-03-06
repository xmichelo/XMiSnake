/// \file
/// \date 2014-01-02
/// \author Xavier Michelon
///
/// \brief Declaration of snake class


#include "stdafx.h"
#include "Snake.h"
#include "Constants.h"
#include <utility>


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
   , direction_(1, eUp)
   , markedForGrowth_(false)
{

}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
Snake::Snake(Snake const& ref)
   : points_(ref.points_)
   , direction_(ref.direction_)
   , markedForGrowth_(ref.markedForGrowth_)
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
Snake& Snake::operator=(Snake& ref)
{
   this->swap(ref);
   return *this;
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void Snake::swap(Snake& ref)
{
   points_.swap(ref.points_);
   direction_.swap(ref.direction_);
   std::swap(markedForGrowth_, ref.markedForGrowth_);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void Snake::reset(QPoint const& position)
{
   Snake snake(position);
   this->swap(snake);
}

//**********************************************************************************************************************
/// \param[in] glWidget The OpenGL widget
//**********************************************************************************************************************
void Snake::render(GlWidget& glWidget)
{
   glWidget.qglColor(kSnakeColor);
   for (DequeQPoint::const_iterator it = points_.begin(); it != points_.end(); ++it)
      renderSnakePart(*it);
}


//**********************************************************************************************************************
/// \param[in] direction The new direction of the snake
//**********************************************************************************************************************
void Snake::addNextDirection(EDirection direction)
{
   if (direction != direction_.back())
      direction_.push_back(direction);
}


//**********************************************************************************************************************
/// A move is successful if the snake does not go out of the board and does not bite itself.
///
/// \return true if and only if the move was successful 
//**********************************************************************************************************************
bool Snake::move()
{
   Q_ASSERT(points_.size() > 0);
   QPoint point(points_.back());
   if (direction_.size() > 1)
      direction_.pop_front();
   switch (direction_.front())
   {
   case eUp:
      if (point.y() <= 0)
         return false;
      point.setY(point.y() - 1);
      break;
   case eDown:
      if (point.y() >= kBoardHeight - 1)
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
   if (this->isOverPoint(point))
      return false; // snake bites itself
   points_.push_back(point);
   if (!markedForGrowth_)
      points_.pop_front();
   markedForGrowth_ = false;
   return true;
}


//**********************************************************************************************************************
/// \param[in] point The point
/// \return true if the snake is over the given point
//**********************************************************************************************************************
bool Snake::isOverPoint(QPoint const point) const
{
   for (DequeQPoint::const_iterator it = points_.begin(); it != points_.end(); ++it)
      if (point == *it)
         return true;
   return false;
}


//**********************************************************************************************************************
/// \return The position of the snake's head
//**********************************************************************************************************************
QPoint Snake::getHeadPosition() const
{
   Q_ASSERT(points_.size() > 0);
   return points_.back();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void Snake::markForGrowth()
{
   markedForGrowth_ = true;
}


//**********************************************************************************************************************
/// \return The size of the snake
//**********************************************************************************************************************
qint32 Snake::getSize() const
{
   return points_.size();
}

