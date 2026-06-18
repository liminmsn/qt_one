#include "VLayout.h"
#include <QVBoxLayout>

VLayout::VLayout(QWidget *parent)
    : QVBoxLayout(parent)
{
    setAlignment(Qt::AlignTop);
    
}
