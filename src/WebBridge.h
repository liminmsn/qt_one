#pragma once
#include <QObject>
#include <QDebug>

class WebBridge : public QObject
{
    Q_OBJECT
public:
    explicit WebBridge(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    // 供 JS 调用的 C++ 函数
    void callFromJs(const QString &message) {
        qDebug() << "收到来自前端的消息:" << message;
    }

signals:
    // C++ 发送给前端的信号
    void sendToJs(const QString &message);
};