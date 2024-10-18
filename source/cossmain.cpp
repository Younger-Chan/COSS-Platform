#include "cossmain.h"
#include "./ui_cossmain.h"

CossMain::CossMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CossMain)
{
    ui->setupUi(this);
}

CossMain::~CossMain()
{
    delete ui;
}
