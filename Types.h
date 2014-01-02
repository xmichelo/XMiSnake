/// \file
/// \date 2014-01-02
/// \author Xavier Michelon
///
/// \brief Declaration of data types


#ifndef XMI__SNAKE__TYPES__H
#define XMI__SNAKE__TYPES__H


#include <deque>


typedef std::deque<QPoint> DequeQPoint; ///< Declaration of deque of QPoint


//**********************************************************************************************************************
/// \brief Enumeration for direction
//**********************************************************************************************************************
enum EDirection {
   eUp      = 0, ///< Up direction
   eDown    = 1, ///< Down direction 
   eLeft    = 2, ///< Left direction
   eRight   = 3, ///< Right direction
}; 

#endif // #ifndef XMI__SNAKE__TYPES__H
