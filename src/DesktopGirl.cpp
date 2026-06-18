#include "DesktopGirl.h"
#include "VLayout.h"
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

    new VLayout(this);
};

void DesktopGirl::mousePressEvent(QMouseEvent *event)
{
    dragPos = event->globalPosition().toPoint() - frameGeometry().topLeft();
}

void DesktopGirl::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPosition().toPoint() - dragPos);
}