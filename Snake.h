/// \file
/// \date 2014-01-02
/// \author Xavier Michelon
///
/// \brief Declaration of snake class


#ifndef XMI__SNAKE__SNAKE__H
#define XMI__SNAKE__SNAKE__H


#include "GlWidget.h"
#include <deque>
#include <Types.h>


//**********************************************************************************************************************
/// \brief A class representing a snake
//**********************************************************************************************************************
class Snake
{
public: // member functions
   Snake(QPoint const& position = QPoint(0, 0)); ///< Default constructor
   Snake(Snake const& ref); ///< Copy-constructor
   ~Snake(); ///< Destructor
   Snake& operator=(Snake& ref); ///< Assignment operator
   void swap(Snake& ref); ///< Swap the snake with another one
   void reset(QPoint const& position); ///< Reset the snake
   void render(GlWidget& glWidget); ///< Render the snake on screen
   void addNextDirection(EDirection direction); ///< Set the direction of the snake
   bool move(); ///< move the snake in the current direction
   bool isOverPoint(QPoint const point) const; ///< Test if the snake is over a given point
   QPoint getHeadPosition() const; ///< Retrieve the position of the snake's head
   void markForGrowth(); ///< Mark the snake for growth
   qint32 getSize() const; ///< Return the size of the snake

private: // member functions


private: // data members
   DequeQPoint points_; ///< The list of point representing the snake
   std::deque<EDirection> direction_; ///< The direction of the snake
   bool markedForGrowth_; ///< Is the snake marked for growth
};


#endif // #ifndef XMI__SNAKE__SNAKE__H
