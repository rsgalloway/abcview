#include "MainWindow.h"
#include "GLState.h"
#include "ObjectTreeWidget.h"
#include "GLWidget.h"
#include "style.h"

namespace AbcView {
namespace ABCVIEW_VERSION_NS {

MainWindow::MainWindow()
     : QMainWindow()
{
	setWindowState(Qt::WindowActive);
	setWindowFlags(Qt::Window);
	setWindowTitle("AbcView");
    setMinimumSize(200, 200);

    //setStyle(QStyleFactory::create("cleanlooks"));
    setStyleSheet(QString(STYLE));

	QAction *fileOpenAction = new QAction("&Open", this);
	QAction *fileQuitAction = new QAction("&Quit", this);
	QAction *widgetsObjectsAction = new QAction("&Outliner", this);
	QAction *widgetsViewerAction = new QAction("&Viewer", this);

    QMenu *file = menuBar()->addMenu("&File");
    QMenu *widgets = menuBar()->addMenu("&Widgets");
    
    file->addAction(fileOpenAction);
    file->addAction(fileQuitAction);
    widgets->addAction(widgetsObjectsAction);
    widgets->addAction(widgetsViewerAction);
    
    connect(fileOpenAction, SIGNAL(triggered()), this, SLOT(handleFileOpen()));
    connect(fileQuitAction, SIGNAL(triggered()), this, SLOT(handleFileQuit()));
    connect(widgetsObjectsAction, SIGNAL(triggered()), this, SLOT(addObjectsWidget()));
    connect(widgetsViewerAction, SIGNAL(triggered()), this, SLOT(addViewerWidget()));
}

void MainWindow::handleFileOpen()
{
    QString filepath = QFileDialog::getOpenFileName(this, "Open File", 
                ".", ("Alembic Files (*.abc)"));
    if (!filepath.isEmpty())
    {
        m_state.addScene(filepath.toUtf8().constData());
    }
}

void MainWindow::handleFileQuit()
{
	close();
}

void MainWindow::addObjectsWidget() 
{
	QDockWidget *dock = new QDockWidget("Outliner", this);
	OutlinerTreeWidget *objectTree = new OutlinerTreeWidget(dock);
	dock->setWidget(objectTree);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
    objectTree->setState(getState());
}

void MainWindow::addViewerWidget() 
{
	QDockWidget *dock = new QDockWidget("Viewer", this);
	GLWidget *viewer = new GLWidget(dock);
	dock->setWidget(viewer);
	addDockWidget(Qt::RightDockWidgetArea, dock);
    viewer->setState(getState());
    viewer->frame();
}

void MainWindow::addScene( const std::string &fileName )
{
	m_state.addScene(fileName);
}

} // End namespace ABCVIEW_VERSION_NS
} // End namespace AbcView
