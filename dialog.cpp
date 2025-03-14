#include "dialog.h"
#include "ui_dialog.h"
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <QMessageBox>

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
    try{
        if(ui->tareaIngreso->toPlainText().isEmpty() == false){
            tarea = ui->tareaIngreso->toPlainText().toStdString();
            if(contiene(tarea, "_")){
                throw std::runtime_error("El caracter '_' no es valido.");
            }
            Task *task = new Task(tarea);
            std::string tar = task->getTarea();
            if(listaTarea->existe(comparar, &tar)){
                delete task;
                throw std::runtime_error("Ya existe una tarea con esa descripcion.");
            }
            listaTarea->insertarElemento(task);
            guardarDatos(task);
        }
        else{
            close();
        }
    }catch(std::exception &e){
        QMessageBox::critical(this, "Caracter Invalido", e.what());
    }
}

void Dialog::on_buttonBox_rejected()
{
    close();
}

void Dialog::guardarDatos (Task *task){
    std::ofstream archivo;
    try{
        archivo.open( nombreArchivo.c_str(), std::ios_base::app | std::ios_base::out );
        if (!archivo.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo");
        }
        archivo << task->getTarea() << lim << task->getEsPendiente() << std::endl;
        archivo.close();

    }catch(const std::runtime_error& e){
        QMessageBox::critical(this, "Error", e.what());
    }
}

bool Dialog::contiene(std::string cadena, std::string subCadena) {
    return cadena.find(subCadena) != std::string::npos;
}

void Dialog::recibirLista(ListaSimple<Task> *listaTarea){
    this->listaTarea = listaTarea;
}
