#ifndef NEWBUILDFILE_H
#define NEWBUILDFILE_H

#include <QDialog>

namespace Ui {
class newBuildFile;
}

class newBuildFile : public QDialog
{
    Q_OBJECT

public:
    explicit newBuildFile(QWidget *parent = 0);
    ~newBuildFile();

    QString File_Name;
private:
    Ui::newBuildFile *ui;

private slots:
    void changeEvent(QEvent *e);
    void on_pushButton_clicked();
};

#endif // NEWBUILDFILE_H
