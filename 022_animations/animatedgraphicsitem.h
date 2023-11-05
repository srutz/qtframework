#ifndef ANIMATEDGRAPHICSITEM_H
#define ANIMATEDGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>

class AnimatedGraphicsItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(double scale READ scale WRITE setScale)
    Q_PROPERTY(double rotation READ rotation WRITE setRotation)
public:
    explicit AnimatedGraphicsItem(QObject *parent = nullptr);

    QGraphicsItem* item() const;
    void setItem(QGraphicsItem *item);

    QPointF pos() const;
    void setPos(QPointF &pos);

    double scale() const;
    void setScale(double);

    double rotation() const;
    void setRotation(double);

private:
    QGraphicsItem* m_item;
    QPointF m_pos;
    double m_scale;
    double m_rotation;
};

#endif // ANIMATEDGRAPHICSITEM_H
