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

    Task();

    Task(std::string tarea, bool esPendiente);

    void trim (std::string &s){
        s.erase(s.find_last_not_of(" \t\n\r") + 1);
    }

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
