#ifndef FORMZSW_H
#define FORMZSW_H

#include <QMainWindow>
#include <QLineSeries>
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE
#include <QStandardItemModel>
#define fixedColumnCount 2
#define iniDataRowCount 10

namespace Ui {
class FormZsw;
}

class FormZsw : public QMainWindow
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
    explicit FormZsw(QWidget *parent = 0);
    ~FormZsw();

private slots:
    void on_btnOk_clicked();

    void on_btnIniData_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_actSaveData_triggered();

private:
    Ui::FormZsw *ui;
};

#endif // FORMZSW_H
