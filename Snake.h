/// \file
/// \date 2014-01-02
/// \author Xavier Michelon
///
/// \brief Declaration of snake class


#ifndef XMI__SNAKE__SNAKE__H
#define XMI__SNAKE__SNAKE__H


#include <deque>
#include <Types.h>


//**********************************************************************************************************************
/// \brief A class representing a snake
//**********************************************************************************************************************
class Snake
{
public: // member functions
   Snake(QPoint const& position); ///< Default constructor
   ~Snake(); ///< Destructor
   void render(); ///< Render the snake on screen
   void setDirection(EDirection direction); ///< Set the direction of the snake
   bool move(); ///< move the snake in the current direction
   bool isOverPoint(QPoint const point) const; ///< Test if the snake is over a given point
   QPoint getHeadPosition() const; ///< Retrieve the position of the snake's head
   void markForGrowth(); ///< Mark the snake for growth

private: // member functions

   Snake(Snake const&); ///< Disabled copy-constructor
   Snake& operator=(Snake const&); ///< Disabled assignment operator

private: // data members
   DequeQPoint points_; ///< The list of point representing the snake
   EDirection direction_; ///< The direction of the snake
   bool markedForGrowth_; ///< Is the snake marked for growth
};


#endif // #ifndef XMI__SNAKE__SNAKE__H
