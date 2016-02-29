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

signals:

public slots:

};

} // End namespace ABCVIEW_VERSION_NS

using namespace ABCVIEW_VERSION_NS;

} // End namespace AbcView

#endif
