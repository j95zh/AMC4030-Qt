#include "newcombobox.h"

newcombobox::newcombobox(QWidget *parent):QComboBox(parent)
{

}

void newcombobox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked(true);
    }
    QComboBox::mousePressEvent(event);
}
