#ifndef COSSMAIN_H
#define COSSMAIN_H

#include <QMainWindow>

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
};
#endif // COSSMAIN_H
