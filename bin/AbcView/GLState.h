#ifndef _AbcView_GLState_h_
#define _AbcView_GLState_h_

#include "All.h"

namespace AbcView {
namespace ABCVIEW_VERSION_NS {

class GLState : public QObject
{
      Q_OBJECT

public:
    explicit GLState();
    void addScene( const std::string &fileName );
    void addScene( const AbcOpenGL::SceneWrapper &scene );
    int size() { return m_scenes.size(); };
    std::vector<AbcOpenGL::SceneWrapper>* getScenes() { return &m_scenes; };
    void stepForward();

private:
    std::vector<AbcOpenGL::SceneWrapper> m_scenes;
    float m_fps;

signals:
    void sceneAdded(int index);
    void steppedForward();

public slots:

};

} // End namespace ABCVIEW_VERSION_NS

using namespace ABCVIEW_VERSION_NS;

} // End namespace AbcView

#endif
