/// \file
/// \date 2014-01-02
/// \author Xavier Michelon
///
/// \brief Declaration of game engine


#ifndef XMI__SNAKE__GAME__ENGINE__H
#define XMI__SNAKE__GAME__ENGINE__H


#include "Snake.h"
#include "Pill.h"
#include "GlWidget.h"


//**********************************************************************************************************************
/// \brief Class representing the game engine
//**********************************************************************************************************************
class GameEngine: public QObject
{
   Q_OBJECT
public: // member functions
   ~GameEngine(); ///< Destructor
   void reset(); ///< Reset the game
   void render(GlWidget& glWidget); ///< render the game on screen
   bool checkAndIterate(); ///< Check if it is already time for the next iteration
   void iterate(); ///< Iterate the game engine
   void setSnakeDirection(EDirection direction); ///< Set the direction of the snake
   void generatePill(); ///< Generate a new pill a a random available position
   qint32 getScore() const; ///< retrieve the score
   void setArenaViewportAndProjection(GlWidget& glWidget) const; ///< set the OpenGL viewport and project matrix
   void setFullWindowViewportAndProjection(GlWidget& glWidget) const; ///< Set the openGL viewport and projection for full window rendering
   void renderArenaBackground(GlWidget& glWidget) const; ///< Render the background of the arena
   void renderScoreString(GlWidget& glWidget) const; ///< Render the score string

private: // member functions
   GameEngine(QObject* parent = nullptr); ///< Default constructor
   GameEngine(GameEngine const&); ///< Disabled copy-constructor
   GameEngine& operator=(GameEngine const&); ///< Disabled assignment operator

private: // friend functions
   friend GameEngine& getGameEngine(); ///< Retrieve the only allowed instance of the GameEngine class

signals:
   void gameOver(); ///< Game is over
   void gameWon(); ///< Game is won

private: // data members
   Snake snake_; ///< The snake
   QDateTime nextIterationTime_; ///< The time of the next iteration
   Pill pill_; ///< The position of the pill
   qint32 score_; ///< The game score
};


#endif // #ifndef XMI__SNAKE__GAME__ENGINE__H
