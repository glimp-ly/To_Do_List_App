#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Task.h"
#include "QMessageBox"
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <QFile>

const char lim = '_';
const std::string nombreArchivo = "../tareas.txt";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    listaTareas(new ListaSimple<Task>)
{
    ui->setupUi(this);
    recuperarDatos(listaTareas);
    actualizar();
    ui->cantTask->setText(QString::number(Task::getCant()));
    ocultarCheckbox(checkboxes, 1);
    ui->pushButton_2->setShortcut(QKeySequence("Ctrl+A"));
    ui->pushButton->setShortcut(QKeySequence("Ctrl+U"));
    ui->pushButton_2->setStyleSheet(
        "QPushButton:hover{"
        "   background-color: green;"
        "}"
        );
    ui->pushButton->setStyleSheet(
        "QPushButton:hover{"
        "   background-color: red;"
        "}"
        );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    Dialog *uiDialog = new Dialog(this);
    connect(uiDialog, &Dialog::acceptedWithData, this, &MainWindow::agregarTarea);
    connect(uiDialog, &Dialog::finished, uiDialog, &QObject::deleteLater);
    uiDialog->exec();
    if(!Task::getCant() == 0){
        actualizar();
    }
}

void MainWindow::ocultarCheckbox(QList<CheckBoxPerso *> checkboxes, int condi) {
    switch (condi) {
    case 1:
        for (CheckBoxPerso* cb : checkboxes) {
            if(cb->checkBox->text().isEmpty() && !(cb->checkBox->isChecked()))
                cb->hide();
        }
        break;
    case 2:
        for (CheckBoxPerso* cb : checkboxes) {
            cb->hide();
        }
    default:
        break;
    }
}

void MainWindow::actualizar(){

    for (CheckBoxPerso* cb : checkboxes) {
        ui->verticalLayout_2->removeWidget(cb);
        disconnect(cb, &CheckBoxPerso::editWithData, this, &MainWindow::editarTarea);
        delete cb;
    }
    checkboxes.clear();

    if(!(listaTareas->getCab() == nullptr)){
        Nodo<Task> *aux = listaTareas->getCab();        

        for (int i = 0; i <= Task::getCant() - 1; i++) {
            CheckBoxPerso *checkbox = new CheckBoxPerso;
            checkbox->setStyleSheet(
                "QCheckBox {"
                "   font-size: 20px;"
                "   color: #fff;"
                "   font-family: Arial;"
                "}"
                "QPushButtom {"
                "   font-size: 20px;"
                "   color: #fff;"
                "   font-family: Arial;"
                "}"
                );
            ui->verticalLayout_2->insertWidget(0, checkbox);
            checkbox->checkBox->setText(QString::fromStdString(aux->getInfo()->getTarea()));
            checkbox->button->setText("Editar");
            checkbox->show();
            connect(checkbox, &CheckBoxPerso::editWithData, this, &MainWindow::editarTarea);
            checkboxes.append(checkbox);
            aux = aux->getSgt();
        }
        ui->cantTask->setText(QString::number(Task::getCant()));
    }else{
        if(band){
            band = false;
            return;
        }
        QMessageBox::information(this, "Sin Tareas Pendientes", "Por el momento usted no tiene tareas pendientes. Felicidades!");
    }
    band = false;
}

void MainWindow::recuperarDatos ( ListaSimple<Task> *lT ){
    std::string linea;
    std::string tarea, estado;
    bool esPendiente;

    try{
        std::ifstream archivo(nombreArchivo.c_str(), std::ios_base::in);
        if (!archivo.is_open()) {
            throw std::runtime_error("El archivo para recuperar datos no se puede abrir.");
        }

        while ( std::getline(archivo, linea)){
            if(!(linea == "")){
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
        }
        archivo.close();
    }catch(std::runtime_error &e){
        QMessageBox::critical(this,"Error al abrir el archivo", e.what());
    }
}

void MainWindow::actuTask(QList<CheckBoxPerso*> checkboxes){
    bool eliminado = false;
    for(CheckBoxPerso *cb : checkboxes){
        if(!(cb->checkBox->text().length() == 0)){
            if(cb->checkBox->isChecked()){
                std::string tareaEli = cb->checkBox->text().toStdString();
                eliminado = listaTareas->eliminar(comparar, &tareaEli);
                eliminarElementoTxt(tareaEli);
                cb->checkBox->setText("");
                cb->checkBox->setChecked(false);
                cb->hide();
                Task::setCant(1);
            }
        }
    }
    if(eliminado){
        ui->cantTask->setText(QString::number(Task::getCant()));
        QMessageBox::information(this, "Tarea(s) Eliminada(s)", "La lista de tareas ha sido actualizada correctamente");
    }
    ocultarCheckbox(checkboxes, 2);
    actualizar();
}

void MainWindow::on_pushButton_clicked()
{
    actuTask(checkboxes);
}

void MainWindow::eliminarElementoTxt (const std::string tareaElim){
    std::string linea, tareaEn;
    std::ifstream archivo( nombreArchivo.c_str(), std::ios_base::in );
    std::ofstream archivoTemp;
    archivoTemp.open("temp.txt", std::ios_base::out | std::ios_base::trunc);

    try{
        if(!archivo.is_open() || !archivoTemp.is_open()){
            throw std::runtime_error("Los Archivos no se pudieron abrir");
        }

        while(std::getline(archivo, linea)){
            if(!(linea == "")){
                std::stringstream buf(linea);
                std::getline(buf, tareaEn, lim);

                if(!(tareaEn == tareaElim)){
                    archivoTemp << linea << std::endl;
                }
            }
        }
        archivo.close();
        archivoTemp.close();

        if (remove(nombreArchivo.c_str())) {
            throw std::runtime_error("Error al eliminar el archivo original");
        }
        if (rename("temp.txt", nombreArchivo.c_str())) {
            remove("temp.txt");
            throw std::runtime_error("Error al renombrar el archivo temporal");
        }
    }catch(std::runtime_error &e){
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::agregarTarea(std::string &tarea){
    try{
        Task *task = new Task(tarea);
        if(listaTareas->existe(comparar, &tarea)){
            delete task;
            throw std::runtime_error("Ya existe una tarea con esa descripcion.");
        }
        listaTareas->insertarElemento(task);
        guardarDatos(task);
    }
    catch(const std::runtime_error &e){
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::guardarDatos (Task *task){
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

void MainWindow::editarTarea(std::string &tareaAntigua, std::string &tareaActual){
    try{
        Nodo<Task> *nodoTask = listaTareas->nodoBuscado(comparar, &tareaAntigua);
        if (!nodoTask) {
            QMessageBox::critical(this, "Error", "Tarea no encontrada.");
            return;
        }
        if(listaTareas->existe(comparar, &tareaActual)){
            throw std::runtime_error("Ya existe una tarea con esa descripcion.");
        }
        nodoTask->getInfo()->setTarea(tareaActual);
        //guardarCambiosEnArchivo(tareaAntigua, tareaActual);  Actualizar archivo
        actualizar();
    }
    catch(const std::runtime_error &e){
        QMessageBox::critical(this, "Error", e.what());
    }
}
