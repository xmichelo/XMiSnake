/// \file
/// \date 2014-01-01
/// \author Xavier Michelon
///
/// \brief Declaration of the application main window


#include "stdafx.h"
#include "MainWindow.h"
#include "GameEngine.h"


namespace {
   qint32 const kTimerIntervalMs(20); ///< The main timer interval in milliseconds
}


//**********************************************************************************************************************
/// \param[in] parent The parent widget of the window
/// \param[in] flags The window flags
//**********************************************************************************************************************
MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
    , timer_(new QTimer(this))
{
   ui_.setupUi(this);
   GameEngine& gameEngine(getGameEngine());
   connect(&gameEngine, SIGNAL(gameStarted()), this, SLOT(onGameStarted()));
   connect(&gameEngine, SIGNAL(gameOver()), this, SLOT(onGameOver()));
   connect(&gameEngine, SIGNAL(gameWon()), this, SLOT(onGameWon()));
   connect(&gameEngine, SIGNAL(gamePaused()), this, SLOT(onGamePaused()));
   connect(&gameEngine, SIGNAL(gameResumed()), this, SLOT(onGameResumed()));
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
MainWindow::~MainWindow()
{

}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::setupTimer()
{
   connect(timer_, SIGNAL(timeout()), this, SLOT(onTimer()));
   timer_->start(kTimerIntervalMs);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onTimer()
{
   if (getGameEngine().checkAndIterate())
      ui_.glWidget->updateGL();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::keyPressEvent(QKeyEvent *event)
{
   if (event->isAutoRepeat())
   {
      event->ignore();
      return;
   }
   switch (event->key())
   {
   case Qt::Key_Up:  
      getGameEngine().setSnakeDirection(eUp);
      break;
   case Qt::Key_Down:  
      getGameEngine().setSnakeDirection(eDown);
      break;
   case Qt::Key_Left:  
      getGameEngine().setSnakeDirection(eLeft);
      break;
   case Qt::Key_Right:  
      getGameEngine().setSnakeDirection(eRight);
      break;
   case Qt::Key_Space:
      getGameEngine().startGame();
      break;
   case Qt::Key_Escape:
      this->close();
      break;
   case Qt::Key_P:
      getGameEngine().pauseResume();
      break;
   default:
      event->ignore();
      return;
   }
   event->accept();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onGameStarted()
{
   this->setupTimer();
   ui_.glWidget->updateGL();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onGameOver()
{
   timer_->stop();
   ui_.glWidget->updateGL();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onGameWon()
{
   timer_->stop();
   ui_.glWidget->updateGL();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onGamePaused()
{
   timer_->stop();
   ui_.glWidget->updateGL();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onGameResumed()
{
   this->setupTimer();
   ui_.glWidget->updateGL();
}

