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

#ifndef _AbcOpenGL_ColorOverride_h_
#define _AbcOpenGL_ColorOverride_h_

#include "Export.h"
#include "Foundation.h"

namespace AbcOpenGL {
namespace ABCOPENGL_VERSION_NS {

//-*****************************************************************************
//! Set an override colour for a particular path within an alembic
class ABC_OPENGL_EXPORT ColorOverride
{
public:
    ColorOverride() {}

    //! Virtual destructor for abstract base class
    //! ...
    virtual ~ColorOverride();
    virtual void pushColorOverride( std::string const override_string, C3f const color_override );
    virtual void popColorOverride( std::string const override_string);
    virtual void clearColorOverride();
    const std::map<std::string, C3f> &overrides() const{ return m_color_overrides ;}
    C3f color_override ( const std::string &comparison_string, const C3f &no_match_color ) const;    

protected:
    static std::map<std::string, C3f> m_color_overrides;

};

} // End namespace ABCOPENGL_VERSION_NS

using namespace ABCOPENGL_VERSION_NS;

} // End namespace AbcOpenGL

#endif
