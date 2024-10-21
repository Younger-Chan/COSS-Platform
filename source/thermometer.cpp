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
    int padding = side * 0.1;  // 留出 10% 的边距
    int radius = (side - padding) / 2;

    // 定义圆心的位置，确保圆形位于widget的底部
    QPoint center(width() / 2, height() - radius - padding);  // 圆心位于widget的底部

    // 绘制矩形，矩形的中心与圆心在同一垂直线上，宽度为圆形的半径
    int rectWidth = radius;  // 矩形的宽度为圆形的半径
    int rectHeight = height() * 1.1;  // 矩形的高度可以根据需求调整
    int rectX = center.x() - rectWidth / 2;  // 矩形的中心与圆心对齐
    int rectY = center.y() - radius / 2;  // 矩形与圆形的顶部部分相交

    QRect rect(rectX, rectY - rectHeight, rectWidth, rectHeight);  // 矩形的区域

    // 绘制矩形
    QPen rectPen(Qt::NoPen);  // 矩形边框为白色
    painter.setPen(rectPen);
    painter.setBrush(QColor(QStringLiteral("#a8e6cf")));
    painter.drawRect(rect);  // 绘制矩形

    // 使用 QRect 创建圆形区域
    QRect ellipseRect(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius);
    QRegion ellipseRegion(ellipseRect, QRegion::Ellipse);

    // 使用 QRect 创建矩形区域
    QRegion rectRegion(rect);

    // 使用相交区域，确保圆形下半部分遮住矩形
    QRegion combinedRegion = rectRegion.subtracted(ellipseRegion);
    painter.setClipRegion(combinedRegion);  // 将矩形区域与圆形相交部分裁剪掉

    // 绘制圆形，圆形会覆盖矩形的下半部分
    painter.setClipping(false);  // 确保剪切区域不影响圆形绘制
    QPen circlePen(Qt::NoPen);  // 圆形边框为白色
    painter.setPen(circlePen);
    painter.setBrush(Qt::transparent);
    painter.drawEllipse(ellipseRect);  // 绘制完整的圆形

    // Optional: 填充颜色（可选）
    QBrush fillBrush(QColor(QStringLiteral("#a8e6cf")));  // 设置填充颜色
    painter.setBrush(fillBrush);
    painter.drawEllipse(ellipseRect);  // 填充圆形
}
