//-*****************************************************************************
//
// Copyright (c) 2009-2013,
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

#include "ColorOverride.h"

namespace AbcOpenGL {
namespace ABCOPENGL_VERSION_NS {

//-*****************************************************************************

//! Virtual destructor
//! ...
ColorOverride::~ColorOverride() {
}

//! Add to map
//! ...
void ColorOverride::pushColorOverride( std::string const override_string, C3f const color_override ){
    m_color_overrides[override_string]=color_override;
};

//! Remove from map
//! ...
void ColorOverride::popColorOverride( std::string const override_string){
    m_color_overrides.erase(override_string);
}

//! Clear map
//! ...
void ColorOverride::clearColorOverride(){
    m_color_overrides.clear();
}

C3f ColorOverride::color_override( const std::string &comparison_string, const C3f &no_match_color ) const
{
    C3f result_color=no_match_color;
    std::map<std::string, C3f>::iterator it;
    it = m_color_overrides.find(comparison_string);
    if (it != m_color_overrides.end())
    {
         // We have a match therefore set a color
         result_color = it -> second;
    }    
    return result_color;
} 

std::map<std::string, C3f> ColorOverride::m_color_overrides;

} // End namespace ABCOPENGL_VERSION_NS
} // End namespace AbcOpenGL
