#include "DesktopGirl.h"
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QUrl>

DesktopGirl::DesktopGirl(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::Window |
                   Qt::WindowTitleHint |
                   Qt::WindowMinimizeButtonHint |
                   Qt::WindowCloseButtonHint);

    setFixedSize(800, 600);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);

    webView = new QWebEngineView(this);
    vbox->addWidget(webView);
    webView->load(QUrl("http://localhost:5173/"));
    // webView->load(QUrl("qrc:/assets/web/index.html"));
};

void DesktopGirl::mousePressEvent(QMouseEvent *event)
{
    dragPos = event->globalPosition().toPoint() - frameGeometry().topLeft();
}

void DesktopGirl::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPosition().toPoint() - dragPos);
}