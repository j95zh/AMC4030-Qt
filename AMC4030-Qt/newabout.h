#ifndef NEWABOUT_H
#define NEWABOUT_H

#include "SystemParam.h"

#include <QDialog>

namespace Ui {
class newAbout;
}

class newAbout : public QDialog
{
    Q_OBJECT

public:
    explicit newAbout(QWidget *parent = 0);
    ~newAbout();

private slots:
    void on_Btn_Update_clicked();
    void RefreshProgram();
    void RefreshVersion();

    void on_Btn_AboutFuyu_clicked();
    void changeEvent(QEvent *e);
    void Combox_ListRefresh();

private:
    Ui::newAbout *ui;

    MACHINE_STATUS  tMachineStatus;
};

#endif // NEWABOUT_H
