#include <QApplication>
#include "DesktopGirl.h"

int main(int argc, char** argv){
    QApplication app(argc,argv);
    
    DesktopGirl girl;
    girl.show();
    
    return app.exec();
}
