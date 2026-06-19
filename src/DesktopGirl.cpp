#include "DesktopGirl.h"
#include "WebBridge.h"
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebChannel>
#include <QUrl>

void DesktopGirl::mousePressEvent(QMouseEvent *event)
{
    dragPos = event->globalPosition().toPoint() - frameGeometry().topLeft();
}

void DesktopGirl::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPosition().toPoint() - dragPos);
}
DesktopGirl::DesktopGirl(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::Window |
                   Qt::WindowTitleHint |
                   Qt::WindowMinimizeButtonHint |
                   Qt::WindowCloseButtonHint);

    setFixedSize(800, 600); 
    setWindowTitle("网络图片查找");


    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);

    // 1. 初始化主网页
    webView = new QWebEngineView(this);
    vbox->addWidget(webView);

    // 2. 创建并注册 WebChannel【必须在 load 之前，且必须 setWebChannel】
    QWebChannel *channel = new QWebChannel(this);
    WebBridge *bridge = new WebBridge(this);
    
    // 注册桥梁对象
    channel->registerObject(QStringLiteral("backend"), bridge);
    // ⭐【关键绑定】：必须把 channel 塞给 webView 的 page！
    webView->page()->setWebChannel(channel);

    // 3. 绑定完成后，再执行加载
    webView->load(QUrl("http://localhost:5173"));

    // // 4. 弹出 DevTools 窗口
    // QWebEngineView *devView = new QWebEngineView();
    // devView->setWindowTitle("Developer Tools");
    // devView->resize(800, 600);
    // devView->setAttribute(Qt::WA_DeleteOnClose);
    // devView->load(QUrl("http://localhost:9999"));
    // devView->show();
}