#ifndef DASHBOARDCIRCLE_H
#define DASHBOARDCIRCLE_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>

class DashBoardCircle: public QWidget
{
    Q_OBJECT
public:
    explicit DashBoardCircle(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *pe) Q_DECL_OVERRIDE;

public:
    void setCurrentValue(float value); // 新增方法设置当前刻度值

private:
    float currentValue = 0;
};

#endif // DASHBOARDCIRCLE_H
