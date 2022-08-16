#include "formscan.h"
#include "ui_formscan.h"
#include <QTextStream>
#include <QMessageBox>
#include <QValueAxis>
#include <QtMath>

void FormScan::iniData()
{
    QStringList headerlist;
    headerlist<<"电位(volts)"<<"电流密度(A/cm2)";
    theModel->setHorizontalHeaderLabels(headerlist);
}

void FormScan::readData()
{
    QStringList fileContent;
    QFile file("scan1.txt");
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

void FormScan::createChart()
{
    QChart *chart=new QChart();
    chart->setTitle("线性极化");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries *series0=new QLineSeries;


    series0->setName("80SS在某缓蚀剂中的线性极化曲线");
    series0->setColor(QColor(255,0,0));
    chart->addSeries(series0);

    QValueAxis *axisX=new QValueAxis;
    QValueAxis *axisY=new QValueAxis;

    // 设置X轴
    axisX->setRange(-5.5e-6,6.5e-6);
    axisX->setLabelFormat("%.5e");
    axisX->setTickCount(11);
    axisX->setMinorTickCount(5);
    axisX->setTitleText("i(A/cm2)");

    //设置Y轴
    axisY->setRange(-0.38,-0.35);
    axisY->setLabelFormat("%.6f");
    axisY->setTickCount(6);
    axisY->setMinorTickCount(5);
    axisY->setTitleText("E(Volts)");



    chart->setAxisX(axisX,series0);
    chart->setAxisY(axisY,series0);
}

void FormScan::prepareData()
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

void FormScan::readData2()
{
    QStringList fileContent;
    QFile file("tafel1.txt");
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

void FormScan::createChart2()
{
    QChart *chart=new QChart();
    chart->setTitle("Tafel极化");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries *series0=new QLineSeries;


    series0->setName("80SS在某缓蚀剂中的塔菲尔极化曲线");
    series0->setColor(QColor(255,0,0));
    chart->addSeries(series0);

    QValueAxis *axisX=new QValueAxis;
    QValueAxis *axisY=new QValueAxis;

    // 设置X轴
    axisX->setRange(-1.1e-4,1.2e-2);
    axisX->setLabelFormat("%.5e");
    axisX->setTickCount(11);
    axisX->setMinorTickCount(5);
    axisX->setTitleText("i(A/cm2)");

    //设置Y轴
    axisY->setRange(-0.65,-0.10);
    axisY->setLabelFormat("%.6f");
    axisY->setTickCount(6);
    axisY->setMinorTickCount(5);
    axisY->setTitleText("E(Volts)");



    chart->setAxisX(axisX,series0);
    chart->setAxisY(axisY,series0);
}

void FormScan::prepareData2()
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

void FormScan::createChartLog()//设置X轴为logi
{
    QChart *chart=new QChart();
    chart->setTitle("Tafel极化");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries *series0=new QLineSeries;


    series0->setName("80SS在某缓蚀剂中的塔菲尔极化曲线");
    series0->setColor(QColor(255,0,0));
    chart->addSeries(series0);

    QLogValueAxis *axisX=new QLogValueAxis;
    QValueAxis *axisY=new QValueAxis;

    // 设置X轴
    axisX->setRange(1e-9,0.1);
    axisX->setLabelFormat("%g");
    axisX->setBase(10);
    axisX->setMinorTickCount(-1);
    axisX->setTitleText("Logi(A/cm2)");

    //设置Y轴
    axisY->setRange(-0.65,-0.10);
    axisY->setLabelFormat("%.6f");
    axisY->setTickCount(6);
    axisY->setMinorTickCount(5);
    axisY->setTitleText("E(Volts)");



    chart->setAxisX(axisX,series0);
    chart->setAxisY(axisY,series0);
}

void FormScan::iniModelFromStringList(QStringList &fileContent)
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

FormScan::FormScan(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormScan)
{
    ui->setupUi(this);
    theModel=new QStandardItemModel(iniDataRowCount,fixedColumnCount,this);
    iniData();
    ui->tableView->setModel(theModel);
}

FormScan::~FormScan()
{
    delete ui;
}

void FormScan::on_btnOk_clicked()
{
    if(ui->lineEdit_2->text()=="2"&&ui->lineEdit_3->text()=="0.1"&&
            ui->lineEdit->text()=="-0.01"&&ui->lineEdit_5->text()=="0.01"&&
            ui->lineEdit_6->text()=="0.1"&&index1==0&&index2==0&&index3==0){
        QMessageBox::information(this,"提示","实验参数设置正确，正在进行测试，请耐心等待",
                                 QMessageBox::Ok,QMessageBox::NoButton);
        ui->actZoomIn->setEnabled(true);
        ui->actZoomOut->setEnabled(true);
        ui->actZoomReset->setEnabled(true);
        ui->actSaveData->setEnabled(true);
        ui->actDraw->setEnabled(true);
        readData();
        createChart();
        prepareData();
    }else if(ui->lineEdit_2->text()=="10"&&ui->lineEdit_3->text()=="1"&&
             ui->lineEdit->text()=="-0.25"&&ui->lineEdit_5->text()=="0.25"&&
             ui->lineEdit_6->text()=="1"&&index1==0&&index2==0&&index3==0){
        QMessageBox::information(this,"提示","实验参数设置正确，正在进行测试，请耐心等待",
                                 QMessageBox::Ok,QMessageBox::NoButton);
        ui->actZoomIn->setEnabled(true);
        ui->actZoomOut->setEnabled(true);
        ui->actZoomReset->setEnabled(true);
        ui->actSaveData->setEnabled(true);
        ui->actDraw->setEnabled(true);
        theModel->clear();
        readData2();
        createChart2();
        prepareData2();
    }
    else{
        QMessageBox::warning(this,"提示","实验参数设置错误，请重新设置");
    }
}

void FormScan::on_actZoomIn_triggered()
{
    ui->chartView->chart()->zoom(1.2);
}

void FormScan::on_actZoomOut_triggered()
{
    ui->chartView->chart()->zoom(0.8);
}

void FormScan::on_actZoomReset_triggered()
{
    ui->chartView->chart()->zoomReset();
}

void FormScan::on_comboBox_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    index1=ui->comboBox->currentIndex();
}

void FormScan::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    index2=ui->comboBox_3->currentIndex();
}

void FormScan::on_comboBox_4_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    index3=ui->comboBox_4->currentIndex();
}

void FormScan::on_btnIniData_clicked()
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

void FormScan::on_comboBox_5_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    index4=ui->comboBox_5->currentIndex();
}

void FormScan::on_actDraw_triggered()
{
    if(index4==1){
        createChartLog();
        QLineSeries *series0=(QLineSeries *)ui->chartView->chart()->series().at(0);
        series0->clear();
        //添加数据
        float x,y;
        for(int i=1;i<readDataRowCount;i++)
        {
            x=(theModel->item(i,1)->text()).toFloat();
            x=qFabs(x);
            y=(theModel->item(i,0)->text()).toFloat();
            series0->append(x,y);
        }
    }
}

void FormScan::on_actSaveData_triggered()
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
