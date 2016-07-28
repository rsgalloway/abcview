//-*****************************************************************************
//
// Copyright (c) 2009-2016,
//  Sony Pictures Imageworks, Inc. and
//  Industrial Light & Magic, a division of Lucasfilm Entertainment Company Ltd.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// *       Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// *       Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// *       Neither the name of Sony Pictures Imageworks, nor
// Industrial Light & Magic nor the names of their contributors may be used
// to endorse or promote products derived from this software without specific
// prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//-*****************************************************************************

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
