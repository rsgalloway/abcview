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
    std::string selection( int x, int y, AbcOpenGL::GLCamera &camera );
    void clearSelection();
    void stepForward();
    void update();

private:
    std::vector<AbcOpenGL::SceneWrapper> m_scenes;
    float m_fps;

signals:
    void sceneAdded(int index);
    void steppedForward();
    void redraw();

public slots:

};

} // End namespace ABCVIEW_VERSION_NS

using namespace ABCVIEW_VERSION_NS;

} // End namespace AbcView

#endif
