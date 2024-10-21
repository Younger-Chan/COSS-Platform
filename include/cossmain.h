#ifndef COSSMAIN_H
#define COSSMAIN_H

#include <QMainWindow>
#include <QSvgRenderer>
#include <QMovie>
#include "dashboardcircle.h"
#include "buttonbar.h"
#include "thermometer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CossMain;
}
QT_END_NAMESPACE

class CossMain : public QMainWindow
{
    Q_OBJECT

public:
    CossMain(QWidget *parent = nullptr);
    ~CossMain();

private:
    Ui::CossMain *ui;
    DashBoardCircle *dbPaint;
    // DashBoardWave *dbwPaint;
    ButtonBar *bb;

private:
    void initGui();
    // QIcon loadSvgIcon(const QString &filePath, const QSize &size);

private slots:
    void slot_stacked_index(int);
};
#endif // COSSMAIN_H
