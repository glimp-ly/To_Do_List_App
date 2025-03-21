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
            if(contiene(tarea, "_") || contiene(tarea, "\n")){
                if(contiene(tarea, "_")){ throw std::runtime_error("El caracter '_' no es valido."); }
                if(contiene(tarea, "\n")){ throw std::runtime_error("El 'Enter' no es valido, puede usar el punto('.') en su lugar."); }
            }
            emit acceptedWithData(tarea);
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

bool Dialog::contiene(std::string cadena, std::string subCadena) {
    return cadena.find(subCadena) != std::string::npos;
}

