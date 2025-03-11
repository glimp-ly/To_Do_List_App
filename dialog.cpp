#include "dialog.h"
#include "ui_dialog.h"
#include <sstream>
#include <fstream>
#include <stdlib.h>

const char lim = '_';
const std::string nombreArchivo = "../tareas.txt";

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
        guardarDatos(task);
    }
    else{
        close();
    }
}

void Dialog::on_buttonBox_rejected()
{
    close();
}

void Dialog::guardarDatos (Task *task){
    std::ofstream archivo;
    archivo.open( nombreArchivo.c_str(), std::ios_base::app | std::ios_base::out );

    if (!archivo.is_open()) {
        qDebug() << "Error: No se pudo abrir el archivo" << nombreArchivo.c_str();
        return;
    }

    archivo << task->getTarea() << lim << task->getEsPendiente() << std::endl;
    archivo.close();
}

void Dialog::recibirLista(ListaSimple<Task> *listaTarea){
    this->listaTarea = listaTarea;
}
