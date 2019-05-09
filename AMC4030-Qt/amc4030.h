#ifndef AMC4030_H
#define AMC4030_H

#include <QMainWindow>

#include <QTimer>
#include <QMutex>
#include <QString>
#include <QMessageBox>
#include <QLibrary>
#include <QDebug>
#include <iostream>
#include <QTextStream>
#include <QDialog>
#include <QComboBox>
#include <QTableWidgetItem>
#include <QEvent>
#include <QTranslator>

#include "Commdefine.h"
#include "newmanualoperation.h"

namespace Ui {
class AMC4030;
}

class AMC4030 : public QMainWindow
{
    Q_OBJECT
public:
    explicit AMC4030(QWidget *parent = 0);
    ~AMC4030();

    static Communication* pComTimerWork;
    static QThread* pComThread;
    static QString currentFilename;

private:
    Ui::AMC4030 *ui;

    int CUR_LANG;

    MACHINE_STATUS  tMachineStatus;
    QTimer *Timer;

    static int CurrentPage;

private slots:
    void on_Btn_ConnectController_clicked();

    void ParameterSet();
    void ManualOperate();
    void ProgramEdite();

    void ChooseChineseLanguage();
    void ChooseEnglishLanguage();

    void WriteUserSettingsCfgFile();
    void ReadUserSettingsCfgFile();
    void on_Btn_About_clicked();

    void ReadMachineStatus();
    void get(const QString&);//接收到手动界面发出的seek(const QString&)信号函数，所需要的反应函数

};

#endif // AMC4030_H
