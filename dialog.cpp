#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    if(ui->tareaIngreso->toPlainText().isEmpty() == false){
        tarea = ui->tareaIngreso->toPlainText().toStdString();
        Task *task = new Task(tarea);
        listaTarea->insertarElemento(task);
    }
    else{
        close();
    }
}

void Dialog::on_buttonBox_rejected()
{
    close();
}

void Dialog::recibirLista(ListaSimple<Task> *listaTarea){
    this->listaTarea = listaTarea;
}
