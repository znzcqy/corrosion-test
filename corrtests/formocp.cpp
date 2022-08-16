#include "formocp.h"
#include "ui_formocp.h"
#include <QTextStream>
#include <QMessageBox>
#include <QValueAxis>

void FormOcp::iniData()
{
    QStringList headerlist;
    headerlist<<"电位(volts)"<<"时间(sec)";
    theModel->setHorizontalHeaderLabels(headerlist);
}

void FormOcp::readData()
{
    QStringList fileContent;
    QFile file("ocp1.txt");
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

void FormOcp::createChart()
{
    QChart *chart=new QChart();
    chart->setTitle("开路电位");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries *series0=new QLineSeries;


    series0->setName("80SS在某缓蚀剂中的开路电位");
    series0->setColor(QColor(255,0,0));
    chart->addSeries(series0);

    QValueAxis *axisX=new QValueAxis;
    QValueAxis *axisY=new QValueAxis;

    // 设置X轴
    axisX->setRange(0,1200);
    axisX->setLabelFormat("%.1f");
    axisX->setTickCount(11);
    axisX->setMinorTickCount(5);
    axisX->setTitleText("T(secs)");

    //设置Y轴
    axisY->setRange(-0.34,-0.29);
    axisY->setLabelFormat("%.6f");
    axisY->setTickCount(6);
    axisY->setMinorTickCount(5);
    axisY->setTitleText("E(Volts)");



    chart->setAxisX(axisX,series0);
    chart->setAxisY(axisY,series0);

}

void FormOcp::prepareData()
{
    QLineSeries *series0=(QLineSeries *)ui->chartView->chart()->series().at(0);
    series0->clear();
    //添加数据
    float x,y;
    for(int i=1;i<readDataRowCount;i++)
    {
        x=(theModel->item(i,1)->text()).toFloat();
        y=(theModel->item(i,0)->text()).toFloat();
        series0->append(x,y);
    }

}

void FormOcp::iniModelFromStringList(QStringList &fileContent)
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

FormOcp::FormOcp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormOcp)
{
    ui->setupUi(this);
    theModel=new QStandardItemModel(iniDataRowCount,fixedColumnCount,this);
    iniData();
    ui->tableView->setModel(theModel);
}

FormOcp::~FormOcp()
{
    delete ui;
}

void FormOcp::on_btnOk_clicked()
{
    if(ui->lineEdit_2->text()=="1"&&ui->lineEdit_3->text()=='5'&&index==0){
        QMessageBox::information(this,"提示","实验参数设置正确，正在进行测试，请耐心等待",
                                 QMessageBox::Ok,QMessageBox::NoButton);
        readData();
        createChart();
        prepareData();
        ui->actZoomIn->setEnabled(true);
        ui->actZoomOut->setEnabled(true);
        ui->actZoomReset->setEnabled(true);
        ui->actSaveData->setEnabled(true);
    }else{
        QMessageBox::warning(this,"提示","实验参数设置错误，请重新设置");
    }
}

void FormOcp::on_btnIniData_clicked()
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

void FormOcp::on_actZoomIn_triggered()
{
    ui->chartView->chart()->zoom(1.2);
}

void FormOcp::on_actZoomOut_triggered()
{
    ui->chartView->chart()->zoom(0.8);
}

void FormOcp::on_actZoomReset_triggered()
{
    ui->chartView->chart()->zoomReset();
}

void FormOcp::on_comboBox_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    index=ui->comboBox->currentIndex();
}

void FormOcp::on_actSaveData_triggered()
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
