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
   gameEngine().checkAndIterate();
}
