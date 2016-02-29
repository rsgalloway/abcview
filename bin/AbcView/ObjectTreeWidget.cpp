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
    setSelectionMode(SingleSelection);
    setDragDropMode(NoDragDrop);
    setFocusPolicy(Qt::NoFocus);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setHeaderHidden(true);

    connect(this, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, 
            SLOT(handleItemExpanded(QTreeWidgetItem*)));
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
                obj->addChild( child );
            }
            obj->setVisited();
        }
    }
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

} // End namespace ABCVIEW_VERSION_NS
} // End namespace AbcView
