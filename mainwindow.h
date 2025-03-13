#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dialog.h>
#include "listaSimpleBase.h"
#include "Task.h"
#include "ui_mainwindow.h"
#include "QCheckBox"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ocultarCheckbox(QList<QCheckBox*> checkboxes, int condi);
    void actualizar();
    void actuTask(QList<QCheckBox*> checkboxes);
    void recuperarDatos (ListaSimple<Task> *lT);
    void eliminarElementoTxt (const std::string tareaElim);

    static bool comparar(Task* tarea, void* nombre, void*) {
        return tarea->getTarea() == *(std::string*)nombre;
    }

    bool band = true;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    ListaSimple<Task> *listaTareas;
    QList<QCheckBox*> checkboxes;
};
#endif // MAINWINDOW_H
