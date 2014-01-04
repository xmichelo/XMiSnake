/// \file
/// \date 2014-01-02
/// \author Xavier Michelon
///
/// \brief Declaration of game engine


#include "stdafx.h"
#include "GameEngine.h"
#include "Constants.h"
#include "Font.h"


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
GameEngine& getGameEngine()
{
   static GameEngine instance;
   return instance;
}


//**********************************************************************************************************************
/// \param[in] parent The parent object of the instance
//**********************************************************************************************************************
GameEngine::GameEngine(QObject* parent)
   : QObject(parent)
{
   this->reset();   
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
void GameEngine::reset()
{
   snake_.reset(kSnakeInitialPosition);
   this->generatePill();
   nextIterationTime_ = QDateTime::currentDateTime().addMSecs(kIterationDelayMs);
}

//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GameEngine::render(GlWidget& glWidget)
{
   glClearColor(kBackgroundColor.redF(), kBackgroundColor.greenF(), kBackgroundColor.blueF(), 
      kBackgroundColor.alphaF());
   glClear(GL_COLOR_BUFFER_BIT);
   snake_.render();
   pill_.render();
   glColor4ub(255, 255, 255, 255);
   QFont& font(getFont());
   font.setPointSize(32);
   glWidget.renderText(5.0 , 440.0, 0.0, QString("Score: %1").arg(this->getScore()), getFont());
//   font.setPointSize(16);
//   glWidget.renderText(445 , 440.0, 0.0, QString("Press 'Space' to start").arg(this->getScore()), getFont());

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


//**********************************************************************************************************************
/// \return The current score
//**********************************************************************************************************************
qint32 GameEngine::getScore()
{
   return snake_.getSize() - 1;
}

