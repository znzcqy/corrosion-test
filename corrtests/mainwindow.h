#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //void paintEvent(QPaintEvent *event);

private slots:

    void on_actZsw_triggered();

    void on_actOCP_triggered();

    void on_actScan_triggered();

    void on_pushButton_6_clicked();

    void on_actIniTest_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
