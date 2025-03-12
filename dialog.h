#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "listaSimpleBase.h"
#include "Task.h"

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

    void guardarDatos(Task *task);
    bool contiene (std::string cadena, std::string subCadena);
    void recibirLista(ListaSimple<Task> *listaTarea);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dialog *ui;
    ListaSimple<Task> *listaTarea;
};

#endif // DIALOG_H
