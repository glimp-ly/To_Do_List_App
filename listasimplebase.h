#ifndef LISTASIMPLEBASE_H
#define LISTASIMPLEBASE_H

template <typename T>
class Nodo {
private:
    Nodo * sgt;
    T * info;

public:
    Nodo() : sgt(NULL), info(nullptr) {}

    T * getInfo() { return info; }
    Nodo * getSgt(){ return sgt; }
    void setInfo (T * dato) { info = dato; }
    void setSgt(Nodo * n) { sgt = n; }
};

template <typename T>
class ListaSimple {
private:
    Nodo<T> * cab;
    int contador;

public:
    ListaSimple() : cab(nullptr), contador(0) {}
    ~ListaSimple() {
        while (cab != nullptr) {
            Nodo<T>* temp = cab;
            cab = cab->getSgt();
            delete temp;
        }
    }

    Nodo<T> * getCab() { return cab; }
    int getContador(){ return contador; }

    void insertarElemento(T * elemento){
        Nodo<T>* nuevoNodo = new Nodo<T>();
        nuevoNodo->setInfo(elemento);
        insertarNodo(nuevoNodo);
    }

    /*
    bool buscar(std::function<bool(T*, std::string)> condicion, std::string parametro) {
        if (cab == nullptr) {
            return false;
        }

        Nodo<T> *Q = cab;
        while (Q != nullptr) {
            if (condicion(Q->getInfo(), parametro)) {
                return true;
            }
            Q = Q->getSgt();
        }
        return false;
    }


    T* buscarRegistro(std::function<bool(T*, std::string, std::string)> condicion,
                      std::string a,
                      std::string b) {
        if (cab == nullptr) {
            return nullptr;
        }

        Nodo<T> *Q = cab;
        while (Q != nullptr) {
            if (condicion(Q->getInfo(), a, b)) {
                return Q->getInfo();
            }
            Q = Q->getSgt();
        }
        return NULL;
    }
    */

    bool eliminar(bool (*comparador)(T* elemento, void* param1, void* param2),
                  void* param1 = nullptr,
                  void* param2 = nullptr) {
        if (!cab) return false;

        Nodo<T> *actual = cab;
        Nodo<T> *anterior = nullptr;
        bool eliminado = false;

        while (actual) {
            if (comparador(actual->getInfo(), param1, param2)) {
                // Si es el primer nodo
                if (anterior == nullptr) {
                    cab = actual->getSgt();
                } else {
                    anterior->setSgt(actual->getSgt());
                }

                // Liberar memoria
                delete actual->getInfo();
                delete actual;

                contador--; // Decrementar contador
                eliminado = true;
                break;
            }

            anterior = actual;
            actual = actual->getSgt();
        }

        return eliminado;
    }

    template <typename A>
    bool buscar (A condicion);

private:
    void insertarNodo(Nodo<T> *info){
        if (cab == nullptr) {
            cab = info;
        } else {
            Nodo<T>* actual = cab;
            while (actual->getSgt() != nullptr) {
                actual = actual->getSgt();
            }
            actual->setSgt(info);
        }
        contador++;
    }


};

#endif // LISTASIMPLEBASE_H
