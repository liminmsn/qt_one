#include "DesktopGirl.h"
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>

DesktopGirl::DesktopGirl(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::Window |
                   Qt::WindowTitleHint |
                   Qt::WindowMinimizeButtonHint |
                   Qt::WindowCloseButtonHint);

    // setAttribute(Qt::WA_TranslucentBackground);
    
    setFixedSize(300, 500);

    // QLabel *image = new QLabel(this);
    // image->setPixmap(
    //     QPixmap(":/assets/girl.jpg")
    //         .scaled(300, 500,
    //                 Qt::KeepAspectRatio,
    //                 Qt::SmoothTransformation));
    // QVBoxLayout *layout = new QVBoxLayout(this);
    // layout->addWidget(image);
    // setLayout(layout);
};

void DesktopGirl::mousePressEvent(QMouseEvent *event)
{
    dragPos = event->globalPosition().toPoint() - frameGeometry().topLeft();
}

void DesktopGirl::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPosition().toPoint() - dragPos);
}