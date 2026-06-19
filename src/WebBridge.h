#pragma once
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QProcess>
#include <QCoreApplication>

class WebBridge : public QObject
{
    Q_OBJECT
public:
    explicit WebBridge(QObject *parent = nullptr) : QObject(parent) {}

    void sendToFrontend(int comm, const QJsonValue &data)
    {
        QJsonObject response;
        response["comm"] = comm;
        response["data"] = data;

        emit sendMessage(response);
    }

public slots:
    void postMessage(const QJsonObject &packet)
    {
        if (!packet.contains("comm") || !packet.contains("data"))
        {
            qWarning() << "收到非法 JSON 协议格式！";
            return;
        }
        int comm = packet["comm"].toInt();
        QJsonValue data = packet["data"];
        dispatchMessage(comm, data);
    }

signals:
    void sendMessage(const QJsonObject &packet);

private:
    void dispatchMessage(int comm, const QJsonValue &data)
    {
        switch (comm)
        {
        case 0:
            handleSearch(data.toString());
            break;
        case 1:
            handleLike(data.toInt());
            break;
        default:
            qWarning() << "未知的命令号:" << comm;
            break;
        }
    }

    void handleSearch(const QString &keyword)
    {
        qDebug() << "C++ 处理搜索业务，关键词:" << keyword;

        QString macosDir = QCoreApplication::applicationDirPath();
        QString program = macosDir + QStringLiteral("/../Helpers/crawler");
        QString workingDir = macosDir + QStringLiteral("/../Resources/crawler_tool");

        QStringList arguments;
        arguments << keyword;

        QProcess *process = new QProcess(this);
        process->setWorkingDirectory(workingDir);

        connect(process, &QProcess::finished, this,
                [this, process, keyword](int exitCode, QProcess::ExitStatus exitStatus)
                {
                    if (exitStatus == QProcess::NormalExit && exitCode == 0)
                    {
                        // 读取爬虫程序通过 std::cout 吐出来的全部 JSON 文本
                        QByteArray output = process->readAllStandardOutput();

                        // 将文本转换解析为 Qt 的 QJsonDocument
                        QJsonParseError parseError;

                        qDebug() << output;
                        QJsonDocument doc = QJsonDocument::fromJson(output, &parseError);

                        if (parseError.error == QJsonParseError::NoError)
                        {
                            qDebug() << "爬虫执行成功，成功拿到网络数据！";
                            // 完美把爬虫得到的动态对象/数组，通过 100 号指令推送给 React 前端
                            sendToFrontend(100, doc.object());
                        }
                        else
                        {
                            qWarning() << "爬虫返回的数据不是合法的 JSON 格式:" << parseError.errorString();
                            sendToFrontend(500, QStringLiteral("爬虫数据解析失败"));
                        }
                    }
                    else
                    {
                        qWarning() << "爬虫进程异常退出，错误码:" << exitCode;
                        sendToFrontend(500, QStringLiteral("爬虫程序执行崩溃"));
                    }

                    // 安全释放进程资源
                    process->deleteLater();
                });

        // 异步启动爬虫程序
        process->start(program, arguments);
    }

    void
    handleLike(int count)
    {
        qDebug() << "C++ 处理点赞业务，当前狂赞次数:" << count;
    }
};