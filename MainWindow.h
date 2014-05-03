/// \file
/// \date 2014-01-01
/// \author Xavier Michelon
///
/// \brief Declaration of the application main window


#ifndef XMI__SNAKE__MAINWINDOW__H
#define XMI__SNAKE__MAINWINDOW__H


#include "ui_MainWindow.h"


//**********************************************************************************************************************
/// \brief The application main window
//**********************************************************************************************************************
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
   MainWindow(QWidget *parent = nullptr, Qt::WindowFlags = 0); ///< Default constructor
   ~MainWindow(); ///< Destructor

private: // data members
   MainWindow(MainWindow const&); /// Disabled copy-constructor
   MainWindow& operator=(MainWindow const&); ///< Disabled assignment operator
   void setupTimer(); ///< Setup the timer
   void keyPressEvent(QKeyEvent *event); ///< Key press event handler

private slots:
   void onTimer(); ///< Slot for the timer
   void onGameStarted(); ///< Slot for the 'game started' signal
   void onGameOver(); ///< Slot for the 'game over' signal
   void onGameWon(); ///< Slot for the 'game won' signal
   void onGamePaused(); ///< Slot for the 'game paused' signal
   void onGameResumed(); ///< Slot for the 'game resumed' signal

private:
   Ui::MainWindowClass ui_; ///< The UI for the window
   QTimer* timer_; ///< The window timer
};


#endif // #ifndef XMI__SNAKE__MAINWINDOW__H
