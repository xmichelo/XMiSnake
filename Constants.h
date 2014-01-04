/// \file
/// \date 2014-01-01
/// \author Xavier Michelon
///
/// \brief Declaration of global constants for the application


#ifndef XMI__SNAKE__CONSTANTS__H
#define XMI__SNAKE__CONSTANTS__H


extern qint32 const kBoardWidth; ///< The width of the board, in number of cells
extern qint32 const kBoardHeight; ///< The height of the board, in number of cells
extern qint32 const kCellSize; ///< The size of a cell in pixels
extern qint32 const kTopMargin; ///< The top margin in pixels

extern qint32 const kScoreFontSize; ///< The score font size
extern QColor const kFontColor; ///< The font color

extern qint32 const kIterationDelayMs; ///< The delay between two iterations of the game (a.k.a. game speed)
extern QPoint const kSnakeInitialPosition; ///< The initial position of the snake

extern QColor const kBackgroundColor;  ///< The background color
extern QColor const kArenaBackgroundColor; ///< The arena background color
extern QColor const kSnakeColor; ///< The snake color
extern QColor const kPillColor; ///< The pill color

#endif // #ifndef XMI__SNAKE__CONSTANTS__H