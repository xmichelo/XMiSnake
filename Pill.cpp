/// \file
/// \date 2014-01-02
/// \author Xavier Michelon
///
/// \brief Implementation of pill class


#include "stdafx.h"
#include "Pill.h"
#include "Constants.h"


//**********************************************************************************************************************
/// \param[in] position The position of the pill
//**********************************************************************************************************************
Pill::Pill(QPoint const& position)
{
   this->setPosition(position);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
Pill::~Pill()
{

}




//**********************************************************************************************************************
/// \return the position of the pill
//**********************************************************************************************************************
QPoint Pill::getPosition() const
{
   return position_;
}


//**********************************************************************************************************************
/// \param[in] position The new position of the pill
//**********************************************************************************************************************
void Pill::setPosition(QPoint const& position)
{
   Q_ASSERT(position.x() >= 0);
   Q_ASSERT(position.x() < kBoardWidth);
   Q_ASSERT(position.y() >= 0);
   Q_ASSERT(position.y() < kBoardHeigth);
   position_ = position;
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void Pill::render()
{
   glColor3ub(kPillColor.red(), kPillColor.green(), kPillColor.blue());
   qint32 const xMin((position_.x() * kCellSize) + 10);
   qint32 const xMax(xMin + kCellSize - 20);
   qint32 const yMin((position_.y() * kCellSize) + 10);
   qint32 const yMax(yMin + kCellSize - 20);
   glBegin(GL_QUADS);
   glVertex2i(xMin, yMin);
   glVertex2i(xMax, yMin);
   glVertex2i(xMax, yMax);
   glVertex2i(xMin, yMax);
   glEnd();
}

