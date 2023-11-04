#include "animatedgraphicsitem.h"

AnimatedGraphicsItem::AnimatedGraphicsItem(QObject *parent)
    : QObject{parent}, m_item(nullptr)
{

}


QGraphicsItem* AnimatedGraphicsItem::item() const
{
    return m_item;
}

void AnimatedGraphicsItem::setItem(QGraphicsItem *item)
{
    m_item = item;
}

QPointF AnimatedGraphicsItem::pos() const
{
    return m_pos;
}

void AnimatedGraphicsItem::setPos(QPointF &pos)
{
    m_pos = pos;
    if (m_item) {
        m_item->setPos(pos);
    }
}


