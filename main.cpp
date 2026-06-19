#include <QApplication>
#include "DesktopGirl.h"

int main(int argc, char** argv){
    QApplication app(argc,argv);
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "9999");

    DesktopGirl girl;
    girl.show();
    
    return app.exec();
}
