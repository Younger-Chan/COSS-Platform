#ifndef BUTTONBAR_H
#define BUTTONBAR_H

#include <QWidget>
#include <QSvgRenderer>
#include <QPainter>

namespace Ui {
class ButtonBar;
}

class ButtonBar : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonBar(QWidget *parent = nullptr);
    ~ButtonBar();

signals:
    void stackedIndex(int);

private:
    Ui::ButtonBar *ui;

private:
    void initGui();
    QIcon loadSvgIcon(const QString &filePath, const QSize &size);
    void updateButtonIcons(bool isPerfSelected);

private slots:
    void slot_pb_perf();
    void slot_pb_info();
};

#endif // BUTTONBAR_H
