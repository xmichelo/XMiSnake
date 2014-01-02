/// \file
/// \date 2014-01-02
/// \author Xavier Michelon
///
/// \brief Declaration of game engine


#ifndef XMI__SNAKE__GAME__ENGINE__H
#define XMI__SNAKE__GAME__ENGINE__H


#include "Snake.h"


//**********************************************************************************************************************
/// \brief Class representing the game engine
//**********************************************************************************************************************
class GameEngine: public QObject
{
   Q_OBJECT
public: // member functions
   ~GameEngine(); ///< Destructor
   void render(); // render the game on screen
   bool checkAndIterate(); ///< Check if it is already time for the next iteration
   void iterate(); ///< Iterate the game engine
   void setSnakeDirection(EDirection direction); ///< Set the direction of the snake

private: // member functions
   GameEngine(QObject* parent = nullptr); ///< Default constructor
   GameEngine(GameEngine const&); ///< Disabled copy-constructor
   GameEngine& operator=(GameEngine const&); ///< Disabled assignment operator


private: // friend functions
   friend GameEngine& gameEngine(); ///< Retrieve the only allowed instance of the GameEngine class

signals:
   void gameOver(); ///< Game is over
   void gameWon(); ///< Game is won

private: // data members
   Snake snake_; ///< The snake
   QDateTime nextIterationTime_; ///< The time of the next iteration
};


#endif // #ifndef XMI__SNAKE__GAME__ENGINE__H
