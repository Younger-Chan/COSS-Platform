#include "dashboardwave.h"

DashBoardWave::DashBoardWave(QWidget *parent): QWidget(parent)
{
    waveAmplitude = 7; // 波浪的振幅
    waveLength = 100;   // 波浪的波长
    // 初始化定时器，确保只启动一次
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        waveOffset += 5;
        if(waveOffset > waveLength)
        {
            waveOffset = 0;
        }
        update();  // 触发重绘
    });
    timer->start(100);  // 波浪移动的时间间隔
}

void DashBoardWave::setCurrentValue(float value)
{
    currentValue = value;
    update(); // 更新绘制
}

void DashBoardWave::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 定义圆心和半径
    // 计算当前控件的最小边
    int side = qMin(width(), height());
    // 动态调整外圆和内圆的半径
    int padding = side * 0.05;  // 留出 5% 边距
    int outerRadius = (side - padding) / 2;  // 动态外圆半径
    int innerRadius = outerRadius * 0.95;     // 内圆半径占外圆的 80%
    QPoint center(width() / 2, height() / 2);

    // 绘制外圆（边界为绿色，填充为透明）
    QPen greenPen(Qt::green, 2);
    painter.setPen(greenPen);
    painter.setBrush(Qt::transparent);
    painter.drawEllipse(center, outerRadius, outerRadius);

    // 绘制内圆（边界为白色，填充为透明）
    QPen whitePen(Qt::white, 2);
    painter.setPen(whitePen);
    painter.setBrush(Qt::transparent);
    painter.drawEllipse(center, innerRadius, innerRadius);

    // 限制 currentValue 在 0 到 100 之间，防止超过 100%
    float clampedValue = qBound(0.0f, currentValue, 100.0f);

    // 根据百分比计算波浪线的基线位置
    int fillHeight = innerRadius * (1.0 - clampedValue / 50.0);
    // int fillHeight = innerRadius - (innerRadius * (clampedValue / 50.0));  // 计算基线高度

    // 创建波浪线路径
    QPainterPath wavePath;
    wavePath.moveTo(center.x() - innerRadius, center.y() + fillHeight);  // 从左侧内圆边开始，并按填充比例下移基线

    // waveAmplitude = 7; // 波浪的振幅
    // waveLength = 100;   // 波浪的波长

    // 生成波浪线形状
    for(int x = -innerRadius; x <= innerRadius; x += 5)
    {
        int y = waveAmplitude * sin((x + innerRadius + waveOffset) * 2 * M_PI / waveLength);
        // 调整波浪线位置，使其始终处于内圆范围内
        wavePath.lineTo(center.x() + x, center.y() + fillHeight + y);
    }

    // 创建封闭路径，返回到波浪线起点并封闭下方区域
    wavePath.lineTo(center.x() + innerRadius, center.y() + innerRadius);  // 右侧到底部
    wavePath.arcTo(center.x() - innerRadius, center.y() - innerRadius, 2 * innerRadius, 2 * innerRadius, 0, -180); // 内圆下半部分的弧线
    wavePath.closeSubpath();  // 完成封闭路径

    // 创建用于裁剪的内圆区域
    QRegion innerCircle(QRect(center.x() - innerRadius, center.y() - innerRadius, 2 * innerRadius, 2 * innerRadius), QRegion::Ellipse);
    // 将波浪线与内圆区域相交，限制绘制范围
    QRegion waveRegion = QRegion(wavePath.toFillPolygon().toPolygon()) & innerCircle;

    // 设置绿色填充
    painter.setClipRegion(waveRegion);  // 限制绘制区域
    // 设置填充颜色
    QBrush waveBrush;
    if(clampedValue > 90)
    {
        waveBrush = QBrush(QColor(QStringLiteral("#ffaaa5"))); // 大于90%时显示为红色
    }
    else if(clampedValue > 70)
    {
        waveBrush = QBrush(QColor(QStringLiteral("#ffd3b6"))); // 大于70%时显示为橙色
    }
    else
    {
        waveBrush = QBrush(QColor(QStringLiteral("#a8e6cf"))); // 其余情况下显示为绿色
    }
    painter.setBrush(waveBrush);

    // 绘制波浪线及其下方的填充区域
    painter.drawPath(wavePath);

    // 确保在绘制数值时没有启用剪切
    painter.setClipping(false);

    // 绘制当前数值
    painter.setPen(Qt::black);  // 设置文本颜色为黑色
    QFont font = painter.font();
    font.setPointSize(16);  // 设置字体大小
    painter.setFont(font);

    // 将数值转换为字符串并绘制在圆心
    QString valueText = QString::number(currentValue, 'f', 0) + "%";
    QRect textRect(center.x() - 50, center.y() - 20, 100, 40);  // 定义文本区域，水平垂直居中
    painter.drawText(textRect, Qt::AlignCenter, valueText);
}
