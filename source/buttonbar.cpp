#include "buttonbar.h"
#include "ui_buttonbar.h"

ButtonBar::ButtonBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ButtonBar)
{
    ui->setupUi(this);
    initGui();
    connect(ui->pb_perf, &QPushButton::clicked, this, &ButtonBar::slot_pb_perf);
    connect(ui->pb_info, &QPushButton::clicked, this, &ButtonBar::slot_pb_info);
}

ButtonBar::~ButtonBar()
{
    delete ui;
}

void ButtonBar::initGui()
{
    // QIcon perfSvgIcon = loadSvgIcon(":/svg/svg/dashboard_origin.svg", QSize(50, 50));
    QIcon infoSvgIcon = loadSvgIcon(":/svg/svg/certificates_origin.svg", QSize(50, 50));
    QIcon perfSelectedSvgIcon = loadSvgIcon(":/svg/svg/dashboard_selected.svg", QSize(50, 50));
    // QIcon infoSelectedSvgIcon = loadSvgIcon(":/svg/svg/certificates_selected.svg", QSize(50, 50));
    ui->pb_perf->setIcon(perfSelectedSvgIcon);
    ui->pb_info->setIcon(infoSvgIcon);
    emit stackedIndex(0);
}

QIcon ButtonBar::loadSvgIcon(const QString &filePath, const QSize &size)
{
    QSvgRenderer svgRenderer(filePath);
    QPixmap pixmap(size);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    svgRenderer.render(&painter);
    return QIcon(pixmap);
}

void ButtonBar::updateButtonIcons(bool isPerfSelected)
{
    QIcon perfIcon = loadSvgIcon(":/svg/svg/dashboard_origin.svg", QSize(50, 50));
    QIcon infoIcon = loadSvgIcon(":/svg/svg/certificates_origin.svg", QSize(50, 50));
    QIcon perfSelectedIcon = loadSvgIcon(":/svg/svg/dashboard_selected.svg", QSize(50, 50));
    QIcon infoSelectedIcon = loadSvgIcon(":/svg/svg/certificates_selected.svg", QSize(50, 50));

    if (isPerfSelected)
    {
        ui->pb_perf->setIcon(perfSelectedIcon);
        ui->pb_info->setIcon(infoIcon);
        emit stackedIndex(0);
    }
    else
    {
        ui->pb_perf->setIcon(perfIcon);
        ui->pb_info->setIcon(infoSelectedIcon);
        emit stackedIndex(1);
    }
}

void ButtonBar::slot_pb_perf()
{
    updateButtonIcons(true);
}

void ButtonBar::slot_pb_info()
{
    updateButtonIcons(false);
}
