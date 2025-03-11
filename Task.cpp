#include "Task.h"

int Task::cant = 0; // Definición de la variable estática

Task::Task (std::string tarea){
    this->tarea = tarea;
    esPendiente = true;
    cant++;
}

Task::Task (std::string tarea, bool esPendiente){
    this->tarea = tarea;
    this->esPendiente = esPendiente;
    cant++;
}
