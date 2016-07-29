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

#include "ObjectTreeWidget.h"

namespace AbcView {
namespace ABCVIEW_VERSION_NS {

struct MatchPathSeparator
{
    bool operator()( char ch ) const
    {
        return ch == '/';
    }
};

std::string basename( std::string const& pathname )
{
    return std::string( 
        std::find_if( pathname.rbegin(), pathname.rend(),
                      MatchPathSeparator() ).base(),
        pathname.end() );
}

OutlinerTreeWidget::OutlinerTreeWidget(QWidget *parent)
{
    setIconSize(QSize(20, 20));
    setAllColumnsShowFocus(true);
    setAnimated(false);
    setAutoScroll(false);
    setUniformRowHeights(true);
    setSelectionMode(ExtendedSelection);
    setDragDropMode(NoDragDrop);
    setFocusPolicy(Qt::NoFocus);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setHeaderHidden(true);

    connect(this, SIGNAL(itemExpanded(QTreeWidgetItem*)), this,
            SLOT(handleItemExpanded(QTreeWidgetItem*)));
    connect(this, SIGNAL(itemSelectionChanged()), this,
            SLOT(handleItemSelection()));
}

void OutlinerTreeWidget::setState( AbcView::GLState* state )
{
    m_state = state;

    for (int i=0; i<m_state->size(); i++)
    {
        sceneAdded(i);
    }

    connect(m_state, SIGNAL(sceneAdded(int)), this, SLOT(sceneAdded(int)));
}

Alembic::AbcGeom::IObject OutlinerTreeWidget::getIObject( QTreeWidgetItem *item )
{
    if ( SceneTreeWidgetItem* scene = dynamic_cast<SceneTreeWidgetItem*>(item) )
    {
        return scene->getScene()->getTop();
    }
    else if (ObjectTreeWidgetItem* obj = dynamic_cast<ObjectTreeWidgetItem*>(item))
    {
        return obj->getIObject();
    }
}

void OutlinerTreeWidget::sceneAdded( int index )
{
    SceneTreeWidgetItem *item = new SceneTreeWidgetItem(this);
    item->setScene( &(*m_state->getScenes())[index] );
    addTopLevelItem( item );
}

void OutlinerTreeWidget::handleItemExpanded(QTreeWidgetItem *item)
{
    SceneTreeWidgetItem* scene = dynamic_cast<SceneTreeWidgetItem*>(item);
    if ( scene && !scene->visited() )
    {
        Alembic::AbcGeom::IObject top = scene->getScene()->getTop();
        for (int i=0; i<top.getNumChildren(); i++)
        {
            ObjectTreeWidgetItem *child = new ObjectTreeWidgetItem(scene);
            child->setIObject( top.getChild(i) );
            child->setScene( scene->getScene() );
            scene->addChild( child );
        }
        scene->setVisited();
    }
    else if (ObjectTreeWidgetItem* obj = dynamic_cast<ObjectTreeWidgetItem*>(item))
    {
        if (!obj->visited())
        {
            Alembic::AbcGeom::IObject iobject = obj->getIObject();
            for (int i=0; i<iobject.getNumChildren(); i++)
            {
                ObjectTreeWidgetItem *child = new ObjectTreeWidgetItem(obj);
                child->setIObject( iobject.getChild(i) );
                child->setScene( obj->getScene() );
                obj->addChild( child );
            }
            obj->setVisited();
        }
    }
}

void OutlinerTreeWidget::handleItemSelected(QTreeWidgetItem *item)
{
    Alembic::AbcGeom::IObject iobject = getIObject(item);
}

void OutlinerTreeWidget::handleItemSelection()
{
    QList<QTreeWidgetItem *> selected = selectedItems();
    m_state->clearSelection();

    foreach(QTreeWidgetItem *item, selected)
    {
       Alembic::AbcGeom::IObject iobject = getIObject(item);
       if (ObjectTreeWidgetItem* obj = dynamic_cast<ObjectTreeWidgetItem*>(item))
       {
           obj->getScene()->addOverrideColorString(
              iobject.getFullName(), Imath::C3f(0.5f, 0.1f, 0.0f));
       }
    }

    m_state->update();
}

SceneTreeWidgetItem::SceneTreeWidgetItem(QWidget *parent)
{
    m_visited = false;
}

void SceneTreeWidgetItem::setScene( AbcOpenGL::SceneWrapper* scene )
{
    m_scene = scene;
    std::string name = m_scene->getArchive().getName();
    setText(0, basename( name ).c_str());
    setChildIndicatorPolicy( QTreeWidgetItem::ShowIndicator );
}

ObjectTreeWidgetItem::ObjectTreeWidgetItem(QTreeWidgetItem *parent)
{
    m_visited = false;
}

void ObjectTreeWidgetItem::setIObject( Alembic::Abc::IObject iobject )
{
    m_iobject = iobject;
    setText(0, iobject.getName().c_str());

    if ( iobject.getNumChildren() )
        setChildIndicatorPolicy( QTreeWidgetItem::ShowIndicator );
}

void ObjectTreeWidgetItem::setScene( AbcOpenGL::SceneWrapper* scene )
{
    m_scene = scene;
}

PropertyTreeWidget::PropertyTreeWidget(QWidget *parent)
{
    setIconSize(QSize(20, 20));
    setAllColumnsShowFocus(true);
    setAnimated(false);
    setAutoScroll(false);
    setUniformRowHeights(true);
    setSelectionMode(ExtendedSelection);
    setDragDropMode(NoDragDrop);
    setFocusPolicy(Qt::NoFocus);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setHeaderHidden(true);
}

void PropertyTreeWidget::setState( AbcView::GLState* state )
{
    m_state = state;
}


} // End namespace ABCVIEW_VERSION_NS
} // End namespace AbcView
