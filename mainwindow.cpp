#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Task.h"
#include "QMessageBox"
#include <sstream>
#include <fstream>
#include <stdlib.h>

const char lim = '_';
const std::string nombreArchivo = "../tareas.txt";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    listaTareas(new ListaSimple<Task>)
{
    ui->setupUi(this);
    recuperarDatos(listaTareas);
    checkboxes = this->findChildren<QCheckBox*>();
    actualizar(checkboxes);
    ui->cantTask->setText(QString::number(Task::getCant()));
    ocultarCheckbox(checkboxes, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    Dialog uiDialog(this);
    uiDialog.recibirLista(listaTareas);
    uiDialog.exec();
    actualizar(checkboxes);
}

void MainWindow::ocultarCheckbox(QList<QCheckBox *> checkboxes, int condi) {
    switch (condi) {
    case 1:
        for (QCheckBox* cb : checkboxes) {
            if(cb->text().isEmpty() && !(cb->isChecked()))
                cb->hide();
        }
        break;
    case 2:
        for (QCheckBox* cb : checkboxes) {
            cb->hide();
        }
    default:
        break;
    }
}

void MainWindow::actualizar(QList<QCheckBox*> checkboxes){
    if(!(listaTareas->getCab() == nullptr)){
        Nodo<Task> *aux = listaTareas->getCab();
        for (int i = 0; i <= Task::getCant() - 1; i++) {
            checkboxes[i]->setText(QString::fromStdString(aux->getInfo()->getTarea()));
            checkboxes[i]->show();
            aux = aux->getSgt();
        }
        ui->cantTask->setText(QString::number(Task::getCant()));
    }else{
        ui->cantTask->setText(QString::number(Task::getCant()));
        QMessageBox::information(this, "Sin Tareas Pendientes", "Por el momento usted no tiene tareas pendientes. Felicidades!");
    }
}

void MainWindow::recuperarDatos ( ListaSimple<Task> *lT ){
    std::string linea;
    std::string tarea, estado;
    bool esPendiente;
    std::ifstream archivo( nombreArchivo.c_str(), std::ios_base::in );
    while ( std::getline(archivo, linea)){
        std::stringstream entrada (linea);
        std::getline (entrada, tarea, lim);
        std::getline (entrada, estado, lim);

        /* Para convertir distintos tipos de datos a string
        pro->precioCompra = strtof(precioC.c_str(), NULL);
        pro->precioVenta = strtof(precioV.c_str(), NULL);
        pro->stock = atoi(stock.c_str());
        */

        if (estado == "1")
            esPendiente = true;
        else
            esPendiente = false;


        Task *task = new Task(tarea, esPendiente);
        lT->insertarElemento(task);
    }
    archivo.close();
}

void MainWindow::actuTask(QList<QCheckBox*> checkboxes){
    bool eliminado = false;
    for(QCheckBox *cb : checkboxes){
        if(!(cb->text().length() == 0)){
            if(cb->isChecked()){
                std::string tareaEli = cb->text().toStdString();
                eliminado = listaTareas->eliminar(comparar, &tareaEli);
                cb->setText("");
                cb->setChecked(false);
                Task::setCant(1);
            }
        }
    }
    if(eliminado){
        QMessageBox::information(this, "Tarea(s) Eliminada(s)", "La lista de tareas ha sido actualizada correctamente");
    }
    ocultarCheckbox(checkboxes, 2);
    actualizar(checkboxes);
}

void MainWindow::on_pushButton_clicked()
{
    actuTask(checkboxes);
}

void MainWindow::eliminarElementoTxt (bool esPendiente){

}
