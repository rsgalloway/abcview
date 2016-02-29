#include "MainWindow.h"
#include "MainWindow.moc"
#include "GLState.moc"
#include "ObjectTreeWidget.moc"
#include <QtGui/QApplication>

//-*****************************************************************************
int main( int argc, char *argv[] )
{
    QApplication *app = new QApplication(argc, argv);

    // create the viewer widget
    AbcView::MainWindow *win = new AbcView::MainWindow();

    // parse args
    std::vector<std::string> arguments(argv, argv + argc);
    std::vector<std::string> options;
    std::vector<std::string> files;

    // separate file args from option args
    for (std::size_t i = 1; i < arguments.size(); i++) {
        if (arguments[i].substr(0, 1) == "-")
            options.push_back(arguments[i]);
        else
            files.push_back(arguments[i]);
    }

    for (std::size_t i = 0; i < files.size(); i++) {
        win->addScene(files[i]);
    }

    // set default size
    //viewer_group.setMinimumSize(QtCore.QSize(100, 100))
    win->resize(500, 500);
    win->show();

    int ret = app->exec();
 
    delete win;
    delete app;
    return ret;
}
