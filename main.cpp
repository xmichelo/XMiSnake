/// \file
/// \date 2014-01-01
/// \author Xavier Michelon
///
/// \brief Implementation of program entry 


#include "stdafx.h"
#include "MainWindow.h"
#include <QtGui/QApplication>


//**********************************************************************************************************************
/// \param[in] argc The number of command line arguments
/// \param[in] argv The list of command line arguments
/// \return The return code for the application
//**********************************************************************************************************************
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(quint32(QDateTime::currentMSecsSinceEpoch()));
    MainWindow w;
    w.show();
    return a.exec();
}
