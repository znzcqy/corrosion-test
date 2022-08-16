#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QChart>
#include <QMessageBox>
#include "formocp.h"
#include "formscan.h"
#include "formzsw.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->widget);

    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        ui->tabWidget->setCurrentIndex(0);
    });
    connect(ui->pushButton_2,&QPushButton::clicked,this,[=](){
        ui->tabWidget->setCurrentIndex(1);
    });
    connect(ui->pushButton_3,&QPushButton::clicked,this,[=](){
        ui->tabWidget->setCurrentIndex(2);
    });
    connect(ui->pushButton_4,&QPushButton::clicked,this,[=](){
        ui->tabWidget->setCurrentIndex(3);
    });
    connect(ui->pushButton_5,&QPushButton::clicked,this,[=](){
        ui->tabWidget->setCurrentIndex(4);
    });
    ui->label->setPixmap(QPixmap(":/images/images/1.png"));
    ui->label->setScaledContents(true);
    ui->label->setAlignment(Qt::AlignCenter);

    ui->label_2->setPixmap(QPixmap(":/images/images/2.png"));
    ui->label_2->setScaledContents(true);
    ui->label_2->setAlignment(Qt::AlignCenter);

    ui->label_3->setPixmap(QPixmap(":/images/images/3.png"));
    ui->label_3->setScaledContents(true);
    ui->label_3->setAlignment(Qt::AlignCenter);

    ui->label_4->setPixmap(QPixmap(":/images/images/4.png"));
    ui->label_4->setScaledContents(true);
    ui->label_4->setAlignment(Qt::AlignCenter);

    ui->label_5->setPixmap(QPixmap(":/images/images/5.png"));
    ui->label_5->setScaledContents(true);
    ui->label_5->setAlignment(Qt::AlignCenter);

    ui->label_6->setPixmap(QPixmap(":/images/images/6.png"));
    ui->label_6->setScaledContents(true);
    ui->label_6->setAlignment(Qt::AlignCenter);

    ui->label_7->setPixmap(QPixmap(":/images/images/7.png"));
    ui->label_7->setScaledContents(true);
    ui->label_7->setAlignment(Qt::AlignCenter);

    ui->label_8->setPixmap(QPixmap(":/images/images/8.png"));
    ui->label_8->setScaledContents(true);
    ui->label_8->setAlignment(Qt::AlignCenter);

    ui->label_9->setPixmap(QPixmap(":/images/images/9.png"));
    ui->label_9->setScaledContents(true);
    ui->label_9->setAlignment(Qt::AlignCenter);

    ui->label_10->setPixmap(QPixmap(":/images/images/10.png"));
    ui->label_10->setScaledContents(true);
    ui->label_10->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
void MainWindow::paintEvent(QPaintEvent *event)
{
    setWindowTitle("腐蚀电化学测试系统");
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0,ui->mainToolBar->height()+ui->menuBar->height(),this->width(),
                       this->height()-ui->mainToolBar->height()-ui->menuBar->height(),
                       QPixmap(":/images/images/back2.jpg"));
}
*/
void MainWindow::on_actZsw_triggered()
{
    FormZsw *formZsw=new FormZsw(this);
    formZsw->setAttribute(Qt::WA_DeleteOnClose);
    formZsw->setWindowTitle("阻抗-频率扫描");
    formZsw->show();
}

void MainWindow::on_actOCP_triggered()
{
    FormOcp *formOcp=new FormOcp(this);
    formOcp->setAttribute(Qt::WA_DeleteOnClose);
    formOcp->setWindowTitle("开路电位");
    // formOcp->setWindowOpacity(0.8);
    formOcp->show();
}

void MainWindow::on_actScan_triggered()
{
    FormScan *formScan=new FormScan(this);
    formScan->setAttribute(Qt::WA_DeleteOnClose);
    formScan->setWindowTitle("动电位扫描");
    // formScan->setWindowOpacity(0.8);
    formScan->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->widget->setVisible(false);
    QMessageBox::information(this,"提示","实验前准备已完成，可以进行电化学测试",
                             QMessageBox::Ok,QMessageBox::NoButton);
}

void MainWindow::on_actIniTest_triggered()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->widget->setVisible(true);
    QMessageBox::information(this,"提示","请进行实验前准备",
                             QMessageBox::Ok,QMessageBox::NoButton);
}
