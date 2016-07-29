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

#include "GLWidget.h"

namespace AbcView {
namespace ABCVIEW_VERSION_NS {

void set_diffuse_light()
{
    GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat diffuse[] = {0.9, 0.9, 0.9, 1.0};
    GLfloat position[] = {90.0, 90.0, 150.0, 0.0};

    GLfloat front_mat_shininess[] = {10.0};
    GLfloat front_mat_specular[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat front_mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat back_mat_shininess[] = {10.0};
    GLfloat back_mat_specular[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat back_mat_diffuse[] = {0.5, 0.5, 0.5, 1.0};

    GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    //glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

    glMaterialfv(GL_FRONT, GL_SHININESS, front_mat_shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, front_mat_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_mat_diffuse);
    glMaterialfv(GL_BACK, GL_SHININESS, back_mat_shininess);
    glMaterialfv(GL_BACK, GL_SPECULAR, back_mat_specular);
    glMaterialfv(GL_BACK, GL_DIFFUSE, back_mat_diffuse);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void draw_grid()
{
    glDisable(GL_LIGHTING);
    glColor3f(0.5, 0.5, 0.5);

    for (int x=-10; x<11; x++)
    {
        if (x == 0)
            continue;
        glBegin(GL_LINES);
        glVertex3f(x, 0, -10);
        glVertex3f(x, 0, 10);
        glVertex3f(-10, 0, x);
        glVertex3f(10, 0, x);
        glEnd();  
    }

    glBegin(GL_LINES);
    glVertex3f(0, 0, -10);
    glVertex3f(0, 0, 10);
    glVertex3f(-10, 0, 0);
    glVertex3f(10, 0, 0);
    glEnd();
}

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    QGLFormat format;
    format.setDirectRendering(true);
    format.setSampleBuffers(true);
    setAutoBufferSwap(true);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

    // default values
    m_fps = 24.0;
    m_camera.setFovy(45.0);
    m_camera.setClippingPlanes(0.1, 100000);
    m_camera.setCenterOfInterest(0.1);
}

void GLWidget::setState( AbcView::GLState* state )
{
    m_state = state;
    connect(m_state, SIGNAL(sceneAdded(int)), this, SLOT(updateGL()));
    connect(m_state, SIGNAL(steppedForward()), this, SLOT(updateGL()));
    connect(m_state, SIGNAL(redraw()), this, SLOT(updateGL()));
}

void GLWidget::frame()
{
    if ( m_state->getScenes()->size() > 0 )
    {
        m_camera.frame((*m_state->getScenes())[0].bounds());
    }
}

void GLWidget::initializeGL()
{
    QGLWidget::makeCurrent();
    glPointSize(1.0);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.26, 0.27, 0.28, 0.0);
    set_diffuse_light();

    // camera orbit defaults
    m_last_p3d = Imath::V3d(1.0, 0.0, 0.0);
    m_last_pok = false;
    m_rotating = false;

    // drawing settings
    m_draw_grid = false;
    m_draw_mode = GL_FILL;
    m_visible_only = true;
    m_bounds_only = false;
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawBuffer(GL_BACK);
    glLoadIdentity();
    m_camera.apply();

    if (m_draw_mode == 0)
        return;

    if (m_draw_grid)
    {
        draw_grid();
    }

    glPolygonMode(GL_FRONT_AND_BACK, m_draw_mode);

    for (int i=0; i<m_state->getScenes()->size(); i++)
    {
        (*m_state->getScenes())[i].draw(m_visible_only, m_bounds_only);
    }
}

void GLWidget::stepForward()
{
    m_state->stepForward();
}

void GLWidget::resizeEvent(QResizeEvent *event)
{
    float width = event->size().width();
    float height = event->size().height();
    resizeGL(width, height);
}

void GLWidget::resizeGL(float width, float height)
{
    m_camera.setSize(width, height);
    QGLWidget::resizeGL(width, height);
}

std::pair<bool, Imath::V3d> GLWidget::mapToSphere(Imath::V2d p2d)
{
    Imath::V3d p3d(0.0, 0.0, 0.0);

    if ( ((p2d.x >= 0) & (p2d.x <= width()) &
         (p2d.y >= 0) & (p2d.y <= height())) ) {
        float x = (p2d.x - 0.5 * width())  / width();
        float y = (0.5 * height() - p2d.y) / height();
        p3d[0] = x;
        p3d[1] = y;
        float z2 = (2.0 * 0.5 * 0.5 - x * x - y * y);
        p3d[2] = sqrt(std::max(z2, (float)0));
        Imath::V3d n = p3d.normalize();
        p3d = p3d / n;
        return std::make_pair(true, p3d);
    }
    else {
        return std::make_pair(false, p3d);
    }
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    Qt::KeyboardModifiers mod = event->modifiers();

    if (key == Qt::Key_Right)
    {
        stepForward();
    }
    else if (key == Qt::Key_F)
    {
        frame();
    }
    else if (key == Qt::Key_0)
    {
        m_draw_mode = 0;
    }
    else if (key == Qt::Key_1)
    {
        m_bounds_only = false;
        m_draw_mode = GL_FILL;
    }
    else if (key == Qt::Key_2)
    {
        m_bounds_only = false;
        m_draw_mode = GL_LINE;
    }
    else if (key == Qt::Key_3)
    {
        m_bounds_only = false;
        m_draw_mode = GL_POINT;
    }
    else if (key == Qt::Key_4)
    {
        m_bounds_only = true;
    }
        
    m_camera.apply();
    updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if ( event->modifiers() == Qt::AltModifier )
    {
        m_last_p2d = Imath::V2d(event->pos().x(), event->pos().y());
        std::pair<bool, Imath::V3d> map;
        map = mapToSphere(m_last_p2d);
        m_last_pok = map.first;
        m_last_p3d = map.second;
    }
    else
    {
        int x = event->pos().x();
        int y = event->pos().y();
        std::string hit = m_state->selection(x, y, m_camera);
        m_state->update();
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ( event->modifiers() != Qt::AltModifier )
        return;

    Imath::V2d newPoint2D(event->pos().x(), event->pos().y());
    
    if ( ((newPoint2D.x < 0) || (newPoint2D.x > width()) ||
       (newPoint2D.y < 0) || (newPoint2D.y > height())) ) {
        event->ignore();
    }

    float value_y = 0;

    std::pair<bool, Imath::V3d> map;
    map = mapToSphere(m_last_p2d);
    bool newPoint_hitSphere = map.first;
    Imath::V3d newPoint3D = map.second;

    float dx = newPoint2D.x - m_last_p2d.x;
    float dy = newPoint2D.y - m_last_p2d.y;
    float w = width();
    float h = height();
    makeCurrent();

    if ( (event->buttons() == Qt::LeftButton & event->modifiers() == Qt::ControlModifier)
        || (event->buttons() == Qt::RightButton & event->modifiers() == Qt::AltModifier) )
    {
        m_camera.dolly(Imath::V2d(dx, dy));
    }
    else if ( (event->buttons() & Qt::MidButton
        || (event->buttons() == Qt::LeftButton & event->modifiers() == Qt::ShiftModifier)) )
    {
        m_camera.track(Imath::V2d(dx, dy));
    }
    else if ( event->buttons() & Qt::LeftButton )
    {
        m_rotating = true;
        m_camera.rotate(Imath::V2d(dx, dy));
    }

    m_last_p2d = newPoint2D;
    m_last_p3d = newPoint3D;
    m_last_pok = newPoint_hitSphere;
    
    m_camera.apply();
    updateGL();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    Imath::V2d point(event->delta() / 2.0, 0.0);
    m_camera.dolly(point, 1.0);
    event->accept();
    m_camera.apply();
    updateGL();
}

} // End namespace ABCVIEW_VERSION_NS
} // End namespace AbcView
