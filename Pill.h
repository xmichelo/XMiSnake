/// \file
/// \date 2014-01-02
/// \author Xavier Michelon
///
/// \brief Declaration of pill class


#ifndef XMI__SNAKE__PILL__H
#define XMI__SNAKE__PILL__H


//**********************************************************************************************************************
/// \brief Class representing a pill
//**********************************************************************************************************************
class Pill
{
public: // member functions
   Pill(QPoint const& position = QPoint(0,0)); ///< Default constructor
   ~Pill(); ///< Destructor
   QPoint getPosition() const; ///< Return the position of the pill
   void setPosition(QPoint const& position); ///< Set the position of the pill
   void render(); ///< Return the pill

private: // member functions
   Pill(Pill const&); ///< Disabled copy-constructor
   Pill& operator=(Pill const&); ///< Disabled assignment operator

public:
   QPoint position_; ///< The position of the pill
};


#endif // #ifndef XMI__SNAKE__PILL__H
