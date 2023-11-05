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

double AnimatedGraphicsItem::scale() const
{
    return m_scale;
}

void AnimatedGraphicsItem::setScale(double scale)
{
    this->m_scale = scale;
    if (m_item) {
        m_item->setScale(scale);
    }
}

double AnimatedGraphicsItem::rotation() const
{
    return m_rotation;
}

void AnimatedGraphicsItem::setRotation(double rotation)
{
    this->m_rotation = rotation;
    if (m_item) {
        m_item->setTransformOriginPoint(m_item->boundingRect().center());
        m_item->setRotation(rotation);
    }
}
