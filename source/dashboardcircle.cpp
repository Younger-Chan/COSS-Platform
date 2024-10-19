#include "dashboardcircle.h"

DashBoardCircle::DashBoardCircle(QWidget *parent): QWidget(parent)
{

}

void DashBoardCircle::setCurrentValue(float value)
{
    currentValue = value;
    update(); // 更新绘制
}

void DashBoardCircle::paintEvent(QPaintEvent *pe)
{
    // 创建 QPainter 对象
    QPainter painter(this);

    // 设置抗锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 定义圆心和半径
    // QPoint center(width() / 2, height() / 2);
    // int outerRadius = 100;  // 外圆半径
    // int innerRadius = 80;   // 内圆半径

    // 计算当前控件的最小边
    int side = qMin(width(), height());
    // 动态调整外圆和内圆的半径
    int padding = side * 0.05;  // 留出 5% 边距
    int outerRadius = (side - padding) / 2;  // 动态外圆半径
    int innerRadius = outerRadius * 0.8;     // 内圆半径占外圆的 80%
    QPoint center(width() / 2, height() / 2);
    // int outerRadius = side / 2 - 20;  // 留出20像素边距
    // int innerRadius = outerRadius - 20;
    // QPoint center(width() / 2, height() / 2);

    QPen whitePen(Qt::transparent, 1);   // 白色边界线
    QBrush whiteBrush(Qt::white);
    painter.setPen(whitePen);
    painter.setBrush(QColor(QStringLiteral("#e8f1f5")));  // 透明填充
    painter.drawEllipse(center, outerRadius, outerRadius);

    // 绘制扇形
    QRectF arcRect(center.x() - outerRadius, center.y() - outerRadius, 2 * outerRadius, 2 * outerRadius);
    int startAngle = 210 * 16;  // 扇形起始角度
    int spanAngle = 120 * 16;   // 扇形角度

    // 设置扇形的白色填充和边界
    painter.setPen(whitePen);
    painter.setBrush(whiteBrush);
    painter.drawPie(arcRect, startAngle, spanAngle);

    // 计算当前值的占比
    float ratio = currentValue / 100.0f; // 当前值占比
    int filledAngle = static_cast<int>(ratio * 240); // 填充的角度（从210°到390°的总角度为240°）

    // 绘制已填充的部分，从210°开始顺时针填充到390°
    // 创建剪切路径，用于显示填充部分
    QPainterPath path;
    path.addEllipse(arcRect); // 添加完整的椭圆
    // painter.setClipPath(path); // 设置剪切区域

    // 绘制已填充的部分
    painter.setBrush(QColor(QStringLiteral("#62d2a2"))); // 绿色表示当前值的区域
    painter.drawPie(arcRect, startAngle, -filledAngle * 16); // 从210°开始顺时针填充

    // 绘制内圆（填充为白色）
    painter.setPen(whitePen);
    painter.setBrush(whiteBrush);  // 白色填充
    painter.drawEllipse(center, innerRadius, innerRadius);

    // 绘制刻度
    int tickLength = 10;    // 刻度线长度

    // 扇形起始角度和跨度（从 210 度到 330 度，总计 120 度）
    double start = 150.0;   // 刻度起始角度
    double end = 390.0;     // 刻度结束角度
    int numTicks = 11;      // 刻度数量，包括0到100的10个刻度

    // 计算每个刻度之间的角度间隔
    double angleStep = (end - start) / (numTicks - 1);  // 刻度间隔

    // 绘制刻度线
    QPen tickPen(Qt::black, 1);  // 刻度线的画笔
    painter.setPen(tickPen);
    painter.setBrush(Qt::NoBrush);

    for(int i = 0; i < numTicks; ++i)
    {
        // 从0到10绘制刻度
        double angle = start + i * angleStep;  // 计算刻度的角度
        double radian = angle * M_PI / 180.0;

        // 刻度线的起点和终点
        QPointF innerPoint(center.x() + innerRadius * cos(radian), center.y() + innerRadius * sin(radian));
        QPointF outerPoint(center.x() + (innerRadius - tickLength) * cos(radian), center.y() + (innerRadius - tickLength) * sin(radian));

        // 绘制刻度线
        painter.drawLine(innerPoint, outerPoint);

        // 在每个刻度旁边绘制数字
        QString label = QString::number(i * 10); // 刻度值为 0, 10, 20, ..., 100
        // 计算标签位置，向内偏移一定的距离
        QPointF labelPoint(center.x() + (innerRadius + tickLength) * cos(radian) - 8, // 向内偏移10   - tickLength - 15
                           center.y() + (innerRadius + tickLength) * sin(radian) + 3); // 确保与刻度线相对位置合理
        painter.drawText(labelPoint, label);

        // 在十位数刻度之间添加个位数刻度
        if(i < numTicks - 1)
        {
            for(int j = 1; j < 10; ++j)
            { // 每个十位数之间的个位数
                double subAngle = angle + (angleStep / 10) * j;  // 计算个位数刻度的角度
                double subRadian = subAngle * M_PI / 180.0;

                // 刻度线的起点和终点
                QPointF subInnerPoint(center.x() + innerRadius * cos(subRadian), center.y() + innerRadius * sin(subRadian));
                QPointF subOuterPoint(center.x() + (innerRadius - (tickLength / 2)) * cos(subRadian), center.y() + (innerRadius - (tickLength / 2)) * sin(subRadian));

                // 绘制个位数刻度线
                painter.drawLine(subInnerPoint, subOuterPoint);
            }
        }
    }

    // 绘制指针

    // 绘制圆心的小圆作为指针的起点
    int circleRadius = 5;  // 小圆的半径
    painter.setBrush(QColor(QStringLiteral("#f57170")));  // 设置小圆为黑色
    painter.setPen(Qt::NoPen);    // 边框为无
    painter.drawEllipse(center, circleRadius, circleRadius);  // 以圆心为中心绘制小圆

    // 指针的长度
    int pointerLength = innerRadius - 20;  // 可以根据需要调整长度
    int pointerWidth = 10;                 // 指针的宽度

    // 计算指针的角度（当前值对应的刻度）
    double pointerAngle = start + ratio * (end - start);  // 根据当前值的比例计算指针的角度
    double radian = pointerAngle * M_PI / 180.0;          // 转换为弧度

    // 指针的四个顶点，形成菱形
    QPointF topPoint(center.x() + pointerLength * cos(radian), center.y() + pointerLength * sin(radian));
    QPointF bottomPoint(center.x() - 5 * cos(radian), center.y() - 5 * sin(radian));
    QPointF leftPoint(center.x() + pointerWidth / 2 * sin(radian), center.y() - pointerWidth / 2 * cos(radian));
    QPointF rightPoint(center.x() - pointerWidth / 2 * sin(radian), center.y() + pointerWidth / 2 * cos(radian));

    // 创建 QPainterPath 绘制菱形
    QPainterPath pointerPath;
    pointerPath.moveTo(topPoint);
    pointerPath.lineTo(leftPoint);
    pointerPath.lineTo(bottomPoint);
    pointerPath.lineTo(rightPoint);
    pointerPath.closeSubpath();

    // 设置指针的颜色为红色
    painter.setBrush(QColor(QStringLiteral("#f57170")));
    painter.setPen(Qt::NoPen);

    // 绘制菱形指针
    painter.drawPath(pointerPath);

    // 在扇形区域中间添加当前值
    painter.setPen(Qt::black); // 设置文本颜色为黑色
    painter.setFont(QFont("Arial", 28, QFont::Bold)); // 设置字体和大小
    QString currentValueText = QString::number(currentValue); // 将当前值转换为字符串

    // 计算文本的边界矩形
    QFontMetrics metrics(painter.font());
    QRect textRect = metrics.boundingRect(currentValueText);
    int textWidth = textRect.width();
    int textHeight = textRect.height();

    int offsetY = 60; // 向上偏移，确保文本在扇形内显示
    painter.drawText(center.x() - textWidth / 2, center.y() + textHeight / 4 + offsetY, currentValueText);

    QPropertyAnimation *animation = new QPropertyAnimation(this, "currentValue");
    animation->setDuration(500);  // 设置动画持续时间
    animation->setStartValue(0);  // 设置起始值
    animation->setEndValue(currentValue);    // 设置结束值
    animation->start();

}
