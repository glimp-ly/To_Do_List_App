#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Task.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    listaTareas(new ListaSimple<Task>)
{
    ui->setupUi(this);
    checkboxes = this->findChildren<QCheckBox*>();
    ui->cantTask->setText(QString::number(Task::getCant()));
    ocultarCheckbox(checkboxes, 2);
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
    }else{
        QMessageBox::information(this, "Sin Tareas Pendientes", "Por el momento usted no tiene tareas pendientes. Felicidades!");
    }
    ui->cantTask->setText(QString::number(Task::getCant()));
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

