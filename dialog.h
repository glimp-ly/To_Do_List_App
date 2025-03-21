#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    std::string tarea;
    ~Dialog();

    bool contiene (std::string cadena, std::string subCadena);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:
    void acceptedWithData(std::string &tarea);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
