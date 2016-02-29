#include "GLState.h"

namespace AbcView {
namespace ABCVIEW_VERSION_NS {

GLState::GLState()
{
    m_fps = 24.0;
}

void GLState::addScene( const std::string &fileName )
{
    addScene( AbcOpenGL::SceneWrapper( fileName ) );
}

void GLState::addScene( const AbcOpenGL::SceneWrapper &scene )
{
    m_scenes.push_back( scene );
    emit sceneAdded(m_scenes.size() - 1);
}

void GLState::stepForward()
{
    for (int i=0; i<m_scenes.size(); i++)
    {
        m_scenes[i].playForward(m_fps);
    }
    emit steppedForward();
}

} // End namespace ABCVIEW_VERSION_NS
} // End namespace AbcView
