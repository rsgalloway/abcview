#ifndef _AbcView_ObjectTreeWidget_h_
#define _AbcView_ObjectTreeWidget_h_

#include "All.h"
#include "GLState.h"

namespace AbcView {
namespace ABCVIEW_VERSION_NS {

class SceneTreeWidgetItem : public QWidget, public QTreeWidgetItem
{

public:
    explicit SceneTreeWidgetItem(QWidget *parent = 0);
    AbcOpenGL::SceneWrapper* getScene() { return m_scene; };
    void setScene( AbcOpenGL::SceneWrapper* scene );
    bool visited () { return m_visited; };
    void setVisited () { m_visited = true; };
    int numChildren() { return getScene()->getTop().getNumChildren(); };

private:
	AbcOpenGL::SceneWrapper* m_scene;
    bool m_visited;

};

class ObjectTreeWidgetItem : public QTreeWidgetItem
{

public:
    explicit ObjectTreeWidgetItem(QTreeWidgetItem *parent = 0);
    Alembic::Abc::IObject getIObject() { return m_iobject; };
    void setIObject( Alembic::Abc::IObject iobject );
    bool visited () { return m_visited; };
    void setVisited () { m_visited = true; };
    int numChildren() { return getIObject().getNumChildren(); };

private:
    Alembic::Abc::IObject m_iobject;
    bool m_visited;

};

class PropertyTreeWidgetItem : public QTreeWidgetItem
{

public:
    explicit PropertyTreeWidgetItem(QWidget *parent = 0);

private:

};

class OutlinerTreeWidget : public QTreeWidget
{
      Q_OBJECT

public:
    explicit OutlinerTreeWidget(QWidget *parent = 0);
    void setState( AbcView::GLState* state );

private:
    AbcView::GLState* m_state;

signals:

public slots:
    void sceneAdded(int index);
    void handleItemExpanded(QTreeWidgetItem *item);

};

} // End namespace ABCVIEW_VERSION_NS

using namespace ABCVIEW_VERSION_NS;

} // End namespace AbcView

#endif
