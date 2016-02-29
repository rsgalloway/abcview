#ifndef _AbcView_MainWindow_h_
#define _AbcView_MainWindow_h_

#include "GLWidget.h"
#include "GLState.h"
#include "All.h"

namespace AbcView {
namespace ABCVIEW_VERSION_NS {

class MainWindow : public QMainWindow
{
      Q_OBJECT
      
public:
    explicit MainWindow();
    void addScene( const std::string &fileName );
    AbcView::GLState* getState() { return &m_state; };

private:
    AbcView::GLState m_state;

signals:

private slots:
    void handleFileOpen();
    void handleFileQuit();
    void addObjectsWidget();
    void addViewerWidget();

};

} // End namespace ABCVIEW_VERSION_NS

using namespace ABCVIEW_VERSION_NS;

} // End namespace AbcView

#endif
