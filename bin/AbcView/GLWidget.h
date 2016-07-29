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

#ifndef _AbcView_GLWidget_h_
#define _AbcView_GLWidget_h_

#include "All.h"
#include "GLState.h"

namespace AbcView {
namespace ABCVIEW_VERSION_NS {

class GLWidget : public QGLWidget
{

public:
    explicit GLWidget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void resizeEvent( QResizeEvent *event );
    void resizeGL( float width, float height );
    void wheelEvent( QWheelEvent *event );
    void keyPressEvent( QKeyEvent *event );
    void mousePressEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );
    std::pair<bool, Imath::V3d> mapToSphere( Imath::V2d point );
    void setState( AbcView::GLState* state );
    void stepForward();
    void frame();

private:
    AbcView::GLState* m_state;
    AbcOpenGL::GLCamera m_camera;
    float m_fps;
    Imath::V2d m_last_p2d;
    Imath::V3d m_last_p3d;
    float m_radius;
    bool m_last_pok;
    bool m_rotating;
    bool m_draw_grid;
    int m_draw_mode;
    bool m_visible_only;
    bool m_bounds_only;

signals:

public slots:

};

} // End namespace ABCVIEW_VERSION_NS

using namespace ABCVIEW_VERSION_NS;

} // End namespace AbcView

#endif
