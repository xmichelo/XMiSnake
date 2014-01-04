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
   score_ = 0;
}

//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GameEngine::render(GlWidget& glWidget)
{
   glWidget.qglClearColor(kBackgroundColor);
   glClear(GL_COLOR_BUFFER_BIT);
   this->setArenaViewportAndProjection(glWidget);
   this->renderArenaBackground(glWidget);
   snake_.render(glWidget);
   pill_.render(glWidget);
   this->setFullWindowViewportAndProjection(glWidget);
   this->renderScoreString(glWidget);
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
      ++score_;
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
      QPoint p= QPoint(qrand() % kBoardWidth, qrand() % kBoardHeight);
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
qint32 GameEngine::getScore() const
{
   return score_;
}


//**********************************************************************************************************************
/// \param[in] glWidget The OpenGL widget
//**********************************************************************************************************************
void GameEngine::setArenaViewportAndProjection(GlWidget& glWidget) const
{
   qint32 const arenaWidth(kBoardWidth * kCellSize);
   qint32 const arenaHeight(kBoardHeight * kCellSize);
   qint32 const xMargin((glWidget.width() - arenaWidth) / 2);
   glViewport(xMargin, glWidget.height() - kTopMargin - arenaHeight, arenaWidth, arenaHeight);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, arenaWidth, arenaHeight, 0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}


//**********************************************************************************************************************
/// \param[in] glWidget The OpenGL widget
//**********************************************************************************************************************
void GameEngine::setFullWindowViewportAndProjection(GlWidget& glWidget) const
{
   qint32 const width(glWidget.width());
   qint32 const height(glWidget.height());
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, width, height, 0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}


//**********************************************************************************************************************
/// \param[in] glWidget The OpenGL widget
//**********************************************************************************************************************
void GameEngine::renderArenaBackground(GlWidget& glWidget) const
{
   qint32 const arenaWidth(kBoardWidth * kCellSize);
   qint32 const arenaHeight(kBoardHeight * kCellSize);
   glWidget.qglColor(kArenaBackgroundColor);
   glBegin(GL_QUADS);
   glVertex2i(0, 0);
   glVertex2i(arenaWidth, 0);
   glVertex2i(arenaWidth, arenaHeight);
   glVertex2i(0, arenaHeight);
   glEnd();
}


//**********************************************************************************************************************
/// \param[in] glWidget The OpenGL widget
//**********************************************************************************************************************
void GameEngine::renderScoreString(GlWidget& glWidget) const
{
   glWidget.qglColor(kFontColor);
   QFont& font(getFont());
   font.setPointSize(kScoreFontSize);
   QFontMetrics metrics(font);
   qint32 const xPos((glWidget.width() - (kBoardWidth * kCellSize)) / 2);
   qint32 const yPos(kTopMargin + (kBoardHeight * kCellSize) + metrics.lineSpacing() - metrics.descent());
   glWidget.renderText(xPos , yPos, 0.0, QString("Score: %1").arg(this->getScore()), getFont());
}

