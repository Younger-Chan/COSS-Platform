#include "thermometer.h"

Thermometer::Thermometer(QWidget *parent): QWidget(parent)
{

}

void Thermometer::setCurrentValue(float value)
{
    currentValue = value;
    update(); // 更新绘制
}

void Thermometer::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 定义绘制区域的中心和半径
    int side = qMin(width(), height());
    int padding = side * 0.4;  // 留出 40% 的边距
    int radius = (side - padding) / 2;

    // 定义圆心的位置，确保圆形位于widget的底部
    QPoint center(width() / 2, height() - radius - padding);  // 圆心位于widget的底部

    // 绘制圆形
    QRect ellipseRect(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius);
    QPen circlePen(Qt::NoPen);
    painter.setPen(circlePen);
    painter.setBrush(QColor(QStringLiteral("#a8e6cf")));  // 设置填充颜色
    painter.drawEllipse(ellipseRect);  // 绘制完整的圆形

    // 定义矩形的宽度和高度
    int rectWidth = radius;  // 矩形的宽度为圆形的半径
    int rectHeight = height();  // 矩形的高度可以根据需求调整
    int rectX = center.x() - rectWidth / 2;  // 矩形的中心与圆心对齐
    int rectY = center.y() - radius / 2;  // 矩形与圆形的顶部部分相交

    QRect rect(rectX, rectY - rectHeight, rectWidth, rectHeight);  // 矩形的区域

    // 绘制矩形
    QPen rectPen(Qt::NoPen);
    painter.setPen(rectPen);
    painter.setBrush(QColor(QStringLiteral("#a8e6cf")));
    painter.drawRect(rect);  // 绘制矩形

    // 定义刻度数量为11，以便包含矩形的顶部和底部
    int tickCount = 11;

    // 计算刻度之间的间距
    double tickSpacing = static_cast<double>(rectHeight) / (tickCount);

    // 从矩形的底部向上绘制刻度线
    for (int i = 0; i < tickCount; ++i)
    {
        int tickLength = 8;  // 每个刻度都为长刻度
        int y = ellipseRect.top() - i * tickSpacing * 0.9;  // 当前刻度的垂直位置，从矩形底部向上

        // 定义刻度的起点和终点
        QPoint startPoint(rect.left(), y);
        QPoint endPoint(rect.left() + tickLength, y);  // 在矩形内水平延伸

        // 绘制刻度
        QPen tickPen(Qt::black, 1);
        painter.setPen(tickPen);
        painter.drawLine(startPoint, endPoint);

        // 计算并绘制递增的刻度数
        int tickValue = i * (100 / (tickCount - 1));  // 将刻度从0递增到100
        painter.drawText(rect.left() - 20, y + 5, QString::number(tickValue));  // 在刻度线左侧绘制刻度数
    }
}
