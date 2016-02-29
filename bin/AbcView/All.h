
#ifndef _AbcView_All_h_
#define _AbcView_All_h_

#define ABCVIEW_VERSION_NS v1

#include <iostream>
#include <algorithm>
#include <math.h>

#include <ImathMath.h>
#include <ImathVec.h>
#include <ImathMatrix.h>
#include <ImathBox.h>
#include <ImathQuat.h>
#include <ImathColor.h>
#include <ImathFun.h>
#include <ImathBoxAlgo.h>

#ifdef PLATFORM_DARWIN

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#else
// http://stackoverflow.com/questions/8580675/error-gl-h-included-before-glew-h
#include <GL/glew.h>

#endif // ifdef PLATFORM_DARWIN

#include <QtCore/QtCore>
#include <QtGui/QAction>
#include <QtGui/QAbstractItemView>
#include <QtGui/QDockWidget>
#include <QtGui/QFileDialog>
#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QMainWindow>
#include <QtGui/QStyleFactory>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QTreeWidgetItem>
#include <QtGui/QWidget>
#include <QIODevice>
#include <QFile>
#include <QResizeEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFormat>
#include <AbcOpenGL/GLCamera.h>
#include <AbcOpenGL/SceneWrapper.h>

#endif
