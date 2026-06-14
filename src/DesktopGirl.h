#pragma once
#include <QWidget>

class DesktopGirl : public QWidget
{
    Q_OBJECT
public:
    explicit DesktopGirl(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPoint dragPos;
};