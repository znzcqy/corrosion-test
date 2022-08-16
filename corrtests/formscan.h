#ifndef FORMSCAN_H
#define FORMSCAN_H

#include <QMainWindow>
#include <QLineSeries>
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE
#include <QStandardItemModel>
#define fixedColumnCount 2
#define iniDataRowCount 10

namespace Ui {
class FormScan;
}

class FormScan : public QMainWindow
{
    Q_OBJECT
private:
    QStandardItemModel *theModel;
    void iniData();
    void readData();
    void createChart();
    void prepareData();
    void readData2();
    void createChart2();
    void prepareData2();
    void createChartLog();
    void iniModelFromStringList(QStringList& fileContent);
    int readDataRowCount;
    int index1=0;
    int index2=0;
    int index3=0;
    int index4=0;
public:
    explicit FormScan(QWidget *parent = 0);
    ~FormScan();

private slots:


    void on_btnOk_clicked();

    void on_actZoomIn_triggered();

    void on_actZoomOut_triggered();

    void on_actZoomReset_triggered();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_3_currentIndexChanged(const QString &arg1);

    void on_comboBox_4_currentIndexChanged(const QString &arg1);

    void on_btnIniData_clicked();

    void on_comboBox_5_currentIndexChanged(const QString &arg1);

    void on_actDraw_triggered();

    void on_actSaveData_triggered();

private:
    Ui::FormScan *ui;
};

#endif // FORMSCAN_H
