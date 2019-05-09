#ifndef NEWPARAMETERSETTING_H
#define NEWPARAMETERSETTING_H

#include <QDialog>

#include "Commdefine.h"
#include "SystemParam.h"

#include <QTimer>
#include <QMutex>
#include <QString>
#include <QMessageBox>
#include <QLibrary>
#include <QDebug>
#include <iostream>
#include <QTextStream>
#include <QUrl>
#include <QDesktopServices> ///用于访问桌面服务的类
#include <QDialog>
#include <QComboBox>
#include <QTableWidgetItem>
#include <QEvent>

namespace Ui {
class newParameterSetting;
}

class newParameterSetting : public QDialog
{
    Q_OBJECT

public:
    explicit newParameterSetting(QWidget *parent = 0);
    ~newParameterSetting();

private:
    Ui::newParameterSetting *ui;

    double m_dbPulseFactor[3];
    double m_dbPulseFactorDown[3];
    double m_dbPulseFactorUp[3];
    float m_fMaxPos[3];
    double m_dbHomeSpeed[3];
    double m_dbHomeOffset[3];
    double m_dbBackLashLen[3];

    double m_dbSysAccSpeed;

    AXIS_PARAM  m_tAxisParam[3];

    SYS_PARAM		g_tSysParam;

    MACHINE_STATUS  tMachineStatus;

    QString CurDir;
private slots:
    void on_Btn_ParameterLoade_clicked();
    void on_Btn_ParameterSave_clicked();
    void on_Btn_RestoreFactorySettings_clicked();

    void PulseFactor_SetText();

    void DisplayContentsAccordingFile();
    void ReadSysCfgFile();
    void LoadDefaultSysCfgFile();
    void OnSetActive();
    void WriteSysCfgFile();

    void changeEvent(QEvent *e);
};

#endif // NEWPARAMETERSETTING_H
