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
   this->setupTimer();
   connect(&(getGameEngine()), SIGNAL(gameOver()), this, SLOT(onGameOver()));
   connect(&(getGameEngine()), SIGNAL(gameWon()), this, SLOT(onGameWon()));
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
   default:
      event->ignore();
      return;
   }
   event->accept();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onGameOver()
{
   timer_->stop();
   GameEngine& engine(getGameEngine());
   QMessageBox::information(this, "Game Over", QString("Game Over!\n\nYour score: %1").arg(engine.getScore()));
   engine.reset();
   this->setupTimer();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onGameWon()
{
   timer_->stop();
   GameEngine& engine(getGameEngine());
   QMessageBox::information(this, "Game Over", QString("Game Over!\n\nYour score: %1").arg(engine.getScore()));
   engine.reset();
   this->setupTimer();
}

