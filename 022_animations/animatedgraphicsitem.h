#ifndef ANIMATEDGRAPHICSITEM_H
#define ANIMATEDGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>

class AnimatedGraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    explicit AnimatedGraphicsItem(QObject *parent = nullptr);
};

#endif // ANIMATEDGRAPHICSITEM_H
