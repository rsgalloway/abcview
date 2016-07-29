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
	QAction *widgetsObjectsAction = new QAction("&Objects", this);
    QAction *widgetsPropertiesAction = new QAction("&Properties", this);
	QAction *widgetsViewerAction = new QAction("&Viewer", this);

    QMenu *file = menuBar()->addMenu("&File");
    QMenu *widgets = menuBar()->addMenu("&Widgets");
    
    file->addAction(fileOpenAction);
    file->addAction(fileQuitAction);
    widgets->addAction(widgetsObjectsAction);
    widgets->addAction(widgetsPropertiesAction);
    widgets->addAction(widgetsViewerAction);
    
    connect(fileOpenAction, SIGNAL(triggered()), this, SLOT(handleFileOpen()));
    connect(fileQuitAction, SIGNAL(triggered()), this, SLOT(handleFileQuit()));
    connect(widgetsObjectsAction, SIGNAL(triggered()), this, SLOT(addObjectsWidget()));
    connect(widgetsPropertiesAction, SIGNAL(triggered()), this, SLOT(addPropertiesWidget()));
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
	QDockWidget *dock = new QDockWidget("Objects", this);
	OutlinerTreeWidget *objectTree = new OutlinerTreeWidget(dock);
	dock->setWidget(objectTree);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
    objectTree->setState(getState());
}

void MainWindow::addPropertiesWidget() 
{
    QDockWidget *dock = new QDockWidget("Properties", this);
    PropertyTreeWidget *propertyTree = new PropertyTreeWidget(dock);
    dock->setWidget(propertyTree);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    propertyTree->setState(getState());
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
