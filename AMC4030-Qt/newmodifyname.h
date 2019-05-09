#ifndef NEWMODIFYNAME_H
#define NEWMODIFYNAME_H

#include <QDialog>

namespace Ui {
class newModifyName;
}

class newModifyName : public QDialog
{
    Q_OBJECT

public:
    explicit newModifyName(QWidget *parent = 0);
    ~newModifyName();
    QString New_FileName;
private:
    Ui::newModifyName *ui;

private slots:
    void changeEvent(QEvent *e);
    void on_pushButton_clicked();
};

#endif // NEWMODIFYNAME_H
