/// \file
/// \date 2014-01-01
/// \author Xavier Michelon
///
/// \brief Declaration of global constants for the application


#include "stdafx.h"
#include "Constants.h"


qint32 const kBoardWidth(20); 
qint32 const kBoardHeigth(14);
qint32 const kCellSize(32);

qint32 const kIterationDelayMs(100); ///< The delay between two iterations of the game (a.k.a. game speed)
QPoint const kSnakeInitialPosition(10, 10); ///< The initial position of the snake

QColor const kBackgroundColor(207, 207, 207);
QColor const kSnakeColor(167, 167, 167);
QColor const kPillColor(97, 97, 97);
