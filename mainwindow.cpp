/// \file
/// \date 2014-01-01
/// \author Xavier Michelon
///
/// \brief Declaration of the application main window


#include "stdafx.h"
#include "MainWindow.h"


//**********************************************************************************************************************
/// \param[in] parent The parent widget of the window
/// \param[in] flags The window flags
//**********************************************************************************************************************
MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
   ui_.setupUi(this);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
MainWindow::~MainWindow()
{

}
