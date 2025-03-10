#ifndef TASK_H
#define TASK_H

#include <iostream>

class Task
{

private:
    std::string tarea;
    static int cant;
    bool esPendiente;

public:

    Task(std::string tarea);

    void setTarea (std::string tarea){
        this->tarea = tarea;
    }

    void setPendiente(bool esPendiente){
        this->esPendiente = esPendiente;
    }

    static void setCant(int num){
        cant -= num;
    }

    std::string getTarea(){
        return tarea;
    }

    bool getEsPendiente(){
        return esPendiente;
    }

    static int getCant(){
        return cant;
    }
};

#endif // TASK_H
