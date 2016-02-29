#include "GLWidget.h"

namespace AbcView {
namespace ABCVIEW_VERSION_NS {

void set_diffuse_light()
{
    GLfloat ambient[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat diffuse[] = {0.5, 1.0, 1.0, 1.0};
    GLfloat position[] = {90.0, 90.0, 150.0, 0.0};

    GLfloat front_mat_shininess[] = {60.0};
    GLfloat front_mat_specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat front_mat_diffuse[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat back_mat_shininess[] = {60.0};
    GLfloat back_mat_specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat back_mat_diffuse[] = {0.0, 0.0, 0.0, 1.0};

    GLfloat lmodel_ambient[] = {0.0, 0.0, 0.0, 1.0};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
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
    glClearColor(0.16, 0.17, 0.18, 0.0);
    set_diffuse_light();

    // camera orbit defaults
    m_last_p3d = Imath::V3d(1.0, 0.0, 0.0);
    m_last_pok = false;
    m_rotating = false;
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawBuffer(GL_BACK);
    glLoadIdentity();
    m_camera.apply();

    for (int i=0; i<m_state->getScenes()->size(); i++)
    {
        (*m_state->getScenes())[i].draw();
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

    if (key == Qt::Key_Right) {
        stepForward();
    } else if (key == Qt::Key_F) {
        frame();
    }
        
    m_camera.apply();
    updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_last_p2d = Imath::V2d(event->pos().x(), event->pos().y());
    std::pair<bool, Imath::V3d> map;
    map = mapToSphere(m_last_p2d);
    m_last_pok = map.first;
    m_last_p3d = map.second;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
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
        || (event->buttons() == Qt::RightButton & event->modifiers() == Qt::AltModifier) ) {
        m_camera.dolly(Imath::V2d(dx, dy));
    } else if ( (event->buttons() & Qt::MidButton
        || (event->buttons() == Qt::LeftButton & event->modifiers() == Qt::ShiftModifier)) ) {
        m_camera.track(Imath::V2d(dx, dy));
    } else if ( event->buttons() & Qt::LeftButton ) {
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
