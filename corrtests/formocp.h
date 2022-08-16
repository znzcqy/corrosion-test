#ifndef FORMOCP_H
#define FORMOCP_H

#include <QMainWindow>
#include <QLineSeries>
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE
#include <QStandardItemModel>
#define fixedColumnCount 2
#define iniDataRowCount 10

namespace Ui {
class FormOcp;
}

class FormOcp : public QMainWindow
{
    Q_OBJECT
private:
    QStandardItemModel *theModel;
    void iniData();
    void readData();
    void createChart();
    void prepareData();
    void iniModelFromStringList(QStringList& fileContent);
    int readDataRowCount;
    int index=0;
public:
    explicit FormOcp(QWidget *parent = 0);
    ~FormOcp();

private slots:
    void on_btnOk_clicked();

    void on_btnIniData_clicked();

    void on_actZoomIn_triggered();

    void on_actZoomOut_triggered();

    void on_actZoomReset_triggered();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_actSaveData_triggered();

private:
    Ui::FormOcp *ui;
};

#endif // FORMOCP_H
