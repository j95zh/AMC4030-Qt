#ifndef NEWSAVEFILE_H
#define NEWSAVEFILE_H

#include <QDialog>

namespace Ui {
class newSaveFile;
}

class newSaveFile : public QDialog
{
    Q_OBJECT

public:
    explicit newSaveFile(QString name,QWidget *parent = 0);
    ~newSaveFile();

    QString File_Name;
    QString new_file_name;
    void set_file_name(QString name);
private slots:
    void on_pushButton_clicked();

    void changeEvent(QEvent *e);
    void on_Btn_ModifyName_clicked();

private:
    Ui::newSaveFile *ui;
};

#endif // NEWSAVEFILE_H
