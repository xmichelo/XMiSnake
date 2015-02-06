/// \file
/// \date 2014-01-04
/// \author Xavier Michelon
///
/// \brief Implementation of functions related to font handling


#include "stdafx.h"
#include "Font.h"
#include <stdexcept>


void initFont(); ///< Initialize the font system


namespace {
   QString const kFontResourcePath(":/MainWindow/lilGrotesk.otf"); ///< The font resource path
   QString const kFontName("LilGrotesk Bold"); ///< The font family name
}
  


//**********************************************************************************************************************
//
//**********************************************************************************************************************
void initFont()
{
   if (-1 == QFontDatabase::addApplicationFont(kFontResourcePath))
      throw std::runtime_error(QString("Unable to open font resource %1").arg(kFontResourcePath).toStdString());
}


//**********************************************************************************************************************
/// \return A reference to the application font
//**********************************************************************************************************************
QFont& getFont()
{
   static bool initialized(false);
   if (!initialized) 
   {
      initFont();
      initialized = true;
   }
   static QFont font(kFontName, 30);
   return font;
}
