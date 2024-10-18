#include "cossmain.h"
#include "./ui_cossmain.h"

CossMain::CossMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CossMain)
{
    ui->setupUi(this);
    bb = findChild<ButtonBar*>("widget");
    connect(bb, &ButtonBar::stackedIndex, this, &CossMain::slot_stacked_index);
    initGui();
}

CossMain::~CossMain()
{
    delete ui;
}

void CossMain::initGui()
{
    dbPaint = new DashBoardCircle(ui->w_wave);
    dbPaint->setCurrentValue(66);
    ui->stackedWidget->setCurrentIndex(0);

    // 创建QMovie对象，加载GIF文件
    QMovie *movie = new QMovie(":/gif/gif/yh1.gif");  // 替换为GIF文件的路径

    QSize labelSize = ui->label->size();
    // 设置 GIF 的缩放大小与 QLabel 一致
    movie->setScaledSize(labelSize);

    ui->label->setMovie(movie);  // 将QMovie对象设置到QLabel上

    // 启动播放GIF动画
    movie->start();
}

void CossMain::slot_stacked_index(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}
