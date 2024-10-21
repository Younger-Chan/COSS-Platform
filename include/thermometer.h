#ifndef THERMOMETER_H
#define THERMOMETER_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>

class Thermometer: public QWidget
{
    Q_OBJECT
public:
    // DashBoardWave();
    explicit Thermometer(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *pe) Q_DECL_OVERRIDE;

public:
    void setCurrentValue(float value); // 新增方法设置当前刻度值

private:
    float currentValue = 0;
    // int waveOffset, waveAmplitude, waveLength;
};

#endif // THERMOMETER_H
