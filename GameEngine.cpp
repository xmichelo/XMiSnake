/// \file
/// \date 2014-01-02
/// \author Xavier Michelon
///
/// \brief Declaration of game engine


#include "stdafx.h"
#include "GameEngine.h"
#include "Constants.h"


namespace {
   qint32 kIterationDelayMs(200);
}

//**********************************************************************************************************************
// 
//**********************************************************************************************************************
GameEngine& gameEngine()
{
   static GameEngine instance;
   return instance;
}


//**********************************************************************************************************************
/// \param[in] parent The parent object of the instance
//**********************************************************************************************************************
GameEngine::GameEngine(QObject* parent)
   : QObject(parent)
   , snake_(QPoint(10, 10))
   , nextIterationTime_(QDateTime::currentDateTime().addMSecs(kIterationDelayMs))
{
   this->generatePill();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
GameEngine::~GameEngine()
{

}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GameEngine::render()
{
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);
   snake_.render();
   pill_.render();
}


//**********************************************************************************************************************
/// \return true if and only if the game was iterated
//**********************************************************************************************************************
bool GameEngine::checkAndIterate()
{
   QDateTime const currentTime(QDateTime::currentDateTime());
   if (currentTime < nextIterationTime_)
      return false;
   this->iterate();
   do
   {
      nextIterationTime_ = nextIterationTime_.addMSecs(kIterationDelayMs);
   } while (nextIterationTime_ <= currentTime);
   return true;
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GameEngine::iterate()
{
   if (!snake_.move())
   {
      emit gameOver();
      return;
   }
   if (pill_.position_ == snake_.getHeadPosition())
   {
      if ((kBoardWidth * kBoardWidth)  - 1 == snake_.getSize())
      {
         emit gameWon();
         return;
      }
      snake_.markForGrowth();
      this->generatePill();
   }
}


//**********************************************************************************************************************
/// \param[in] direction The new direction of the snake
//**********************************************************************************************************************
void GameEngine::setSnakeDirection(EDirection direction)
{
   snake_.setDirection(direction);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GameEngine::generatePill()
{
   while (true)
   {
      QPoint p= QPoint(qrand() % kBoardWidth, qrand() % kBoardHeigth);
      if (!snake_.isOverPoint(p))
      {
         pill_.setPosition(p);
         return;
      }
   }
}
