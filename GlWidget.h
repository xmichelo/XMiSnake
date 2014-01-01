/// \file
/// \date 2014-01-01
/// \author Xavier Michelon
///
/// \brief Declaration of custom OpenGL widget class


#ifndef XMI__SNAKE__GL__WIDGET__H
#define XMI__SNAKE__GL__WIDGET__H


//**********************************************************************************************************************
/// \brief Custom OpenGL Widget class
//**********************************************************************************************************************
class GlWidget: public QGLWidget
{
public: // member functions
   GlWidget(QWidget* parent = nullptr); ///< Default constructor
   ~GlWidget(); ///< Destructor

private: // member functions
   GlWidget(GlWidget const&); ///< Disabled copy-constructor
   GlWidget& operator=(GlWidget const&); ///< Disabled assignment operator
   void initializeGL(); ///< Initialize the OpenGL system
   void paintGL();  ///< OpenGL redraw callback
   void resizeGL(int width, int height); /// OpenGL resize callback
};


#endif // #ifndef XMI__SNAKE__GL__WIDGET__H