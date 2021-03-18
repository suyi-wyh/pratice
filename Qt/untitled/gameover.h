#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QMainWindow>
#include<gamemainwindow.h>
#include <dialog.h>
namespace Ui {
class gameover;
}

class gameover : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameover(QWidget *parent = 0);
    ~gameover();

private slots:
    void on_chosse_clicked();

    void on_again_clicked();

private:
    Ui::gameover *ui;
};

#endif // GAMEOVER_H
