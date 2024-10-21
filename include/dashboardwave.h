#ifndef DASHBOARDWAVE_H
#define DASHBOARDWAVE_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>

class DashBoardWave: public QWidget
{
    Q_OBJECT
public:
    // DashBoardWave();
    explicit DashBoardWave(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *pe) Q_DECL_OVERRIDE;

public:
    void setCurrentValue(float value); // 新增方法设置当前刻度值

private:
    float currentValue = 0;
};

#endif // DASHBOARDWAVE_H
