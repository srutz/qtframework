#ifndef ANIMATEDGRAPHICSITEM_H
#define ANIMATEDGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>

class AnimatedGraphicsItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    explicit AnimatedGraphicsItem(QObject *parent = nullptr);

    QGraphicsItem* item() const;
    void setItem(QGraphicsItem *item);

    QPointF pos() const;
    void setPos(QPointF &pos);


private:
    QGraphicsItem* m_item;
    QPointF m_pos;
};

#endif // ANIMATEDGRAPHICSITEM_H
