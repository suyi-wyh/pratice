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

private slots:
    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_clicked(bool checked);

    void on_color_clicked();

    void setline2color();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
