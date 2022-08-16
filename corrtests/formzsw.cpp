#include "formzsw.h"
#include "ui_formzsw.h"
#include <QTextStream>
#include <QMessageBox>
#include <QValueAxis>
#include <QtMath>

void FormZsw::iniData()
{
    QStringList headerlist;
    headerlist<<"Z'(Ohm.cm^2)"<<"Z''(Ohm.cm^2)";
    theModel->setHorizontalHeaderLabels(headerlist);
}

void FormZsw::readData()
{
    QStringList fileContent;
    QFile file("zsw1.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream stream(&file);
        ui->plainTextEdit->clear();
        while (!stream.atEnd()) {
            QString str=stream.readLine();
            ui->plainTextEdit->appendPlainText(str);
            fileContent.append(str);
        }
        file.close();
        iniModelFromStringList(fileContent);
    }
}

void FormZsw::createChart()
{
    QChart *chart=new QChart();
    chart->setTitle("交流阻抗");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries *series0=new QLineSeries;


    series0->setName("80SS在某缓蚀剂中的阻抗谱图");
    series0->setColor(QColor(255,0,0));
    chart->addSeries(series0);

    QValueAxis *axisX=new QValueAxis;
    QValueAxis *axisY=new QValueAxis;

    // 设置X轴
    axisX->setRange(0,2000);
    axisX->setLabelFormat("%g");
    axisX->setTickCount(11);
    axisX->setMinorTickCount(5);
    axisX->setTitleText("Z'(Ohm.cm^2)");

    //设置Y轴
    axisY->setRange(0,700);
    axisY->setLabelFormat("%g");
    axisY->setTickCount(8);
    axisY->setMinorTickCount(5);
    axisY->setTitleText("Z''(Ohm.cm^2)");



    chart->setAxisX(axisX,series0);
    chart->setAxisY(axisY,series0);
}

void FormZsw::prepareData()
{
    QLineSeries *series0=(QLineSeries *)ui->chartView->chart()->series().at(0);
    series0->clear();
    //添加数据
    float x,y;
    for(int i=1;i<readDataRowCount;i++)
    {
        x=(theModel->item(i,0)->text()).toFloat();
        y=(theModel->item(i,1)->text()).toFloat();
        y=qFabs(y);
        series0->append(x,y);
    }
}

void FormZsw::iniModelFromStringList(QStringList &fileContent)
{
    theModel->setRowCount(fileContent.count()-1);
    readDataRowCount=fileContent.count()-1;
    QString header=fileContent.at(0);
    QStringList headerlist=header.split(QRegExp("\\s+"),QString::SkipEmptyParts);
    theModel->setHorizontalHeaderLabels(headerlist);

    int j;
    QStandardItem *item;
    for(int i=1;i<fileContent.count();i++){
        QString lineText=fileContent.at(i);
        QStringList tmpList=lineText.split(QRegExp("\\s+"),QString::SkipEmptyParts);
        for(j=0;j<fixedColumnCount;j++){
            item=new QStandardItem(tmpList.at(j));
            theModel->setItem(i-1,j,item);
        }
    }
}

FormZsw::FormZsw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormZsw)
{
    ui->setupUi(this);
    theModel=new QStandardItemModel(iniDataRowCount,fixedColumnCount,this);
    iniData();
    ui->tableView->setModel(theModel);
}

FormZsw::~FormZsw()
{
    delete ui;
}

void FormZsw::on_btnOk_clicked()
{
    if(ui->lineEdit->text()=="100000"&&ui->lineEdit_2->text()=="10"&&
            ui->lineEdit_3->text()=="0.01"&&ui->lineEdit_4->text()=="10"&&
            ui->lineEdit_5->text()=="0"&&index==0&&ui->radioButton_2->isChecked()){
        QMessageBox::information(this,"提示","实验参数设置正确，正在进行测试，请耐心等待",
                                         QMessageBox::Ok,QMessageBox::NoButton);
        ui->actZoomIn->setEnabled(true);
        ui->actZoomOut->setEnabled(true);
        ui->actZoomReset->setEnabled(true);
        ui->actSaveData->setEnabled(true);
        readData();
        createChart();
        prepareData();
    }else{
        QMessageBox::warning(this,"提示","实验参数设置错误，请重新设置");
    }
}

void FormZsw::on_btnIniData_clicked()
{
    ui->plainTextEdit->clear();
    theModel->clear();
    theModel=new QStandardItemModel(iniDataRowCount,fixedColumnCount,this);
    iniData();
    ui->tableView->setModel(theModel);

    QChart *chart=new QChart();
    ui->chartView->setChart(chart);
    QLineSeries *series0=new QLineSeries;
    chart->addSeries(series0);
    QValueAxis *axisX=new QValueAxis;
    QValueAxis *axisY=new QValueAxis;
    chart->setAxisX(axisX,series0);
    chart->setAxisY(axisY,series0);
}

void FormZsw::on_comboBox_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    index=ui->comboBox->currentIndex();
}

void FormZsw::on_actSaveData_triggered()
{
    QString curPath=QCoreApplication::applicationDirPath();
    QString dlgTitle="保存数据文件";
    QString filter="文本文件(*.txt);;所有文件(*.*)";
    QString aFileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);
    if (aFileName.isEmpty()) return;
    QFile file(aFileName);
    if (file.open(QIODevice::WriteOnly|QIODevice::Text)){
        QString str=ui->plainTextEdit->toPlainText();
        QByteArray strBytes=str.toUtf8();

        file.write(strBytes,strBytes.length());
        file.close();
    }
}
