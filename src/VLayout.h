#pragma once
#include <QVBoxLayout>

class VLayout : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit VLayout(QWidget* parent = nullptr);
};