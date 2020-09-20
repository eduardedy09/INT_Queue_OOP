#include <iostream>

using namespace std;

class Nod {
    Nod *next;
public:
    Nod() {
        info = 0;
        next = NULL;
    }

    Nod(char inf) : info(inf), next(NULL) {};

    ~Nod() {

    };
    char info; // Am pus membru public din cauza functiei de supraincarcare a operatorului de afisare.
    friend class coada; // Pentru a putea folosi membrul privat next in metodele cerute.
};


class coada {
    Nod *first;
    Nod *last;
public:
    coada() : first(NULL), last(NULL) {};
    /// Copy constructor
    coada(const coada &aux) {
        first = aux.first;
        last = aux.last;
    }
    int isempty() {
        if (first == NULL) return 1;  // 1 daca stiva este goala.
        return 0;
    }

    // Functia Push pune un element in coada prin spate.
    void push(char x) {
        if (isempty() == 1) {
            first = new Nod;
            first->info = x;
            first->next = last;
        } else if (last == NULL) {
            last = new Nod;
            last->info = x;
            last->next = NULL;
            first->next = last;
        } else {
            Nod *t = new Nod; // Pentru noul element adaugat in coada.
            t->info = x;
            t->next = NULL;
            last->next = t;
            last = t;
        }
    }

    // Functia pop sterge primul element din coada
    void pop() {
        if (isempty() == 1) return;
        if (first == last) { //1 singur element
            delete (first);
            first = NULL;
            last = NULL;
        } else {
            Nod *t = first;
            first = first->next;
            delete t;
        }
    }

    //Supraincarcare operatorului[] necesar la functionarea demoului
    char operator[](int i)
    {
        Nod *da=first;
        for(int aux=0;aux<=i;aux++)
            da = da->next;
        return da->next->info;
    }

    // Supraincarcarea operatorului =
    coada &operator=(const coada &c1) {
        Nod *aux = c1.first; // Aux reprezinta un pointer la inceputul cozii folosit pentru a parcurge coada.
        while (aux != NULL) {
            push(aux->info);
            aux = aux->next;
        }
    }

    // Supraincarcarea operatorului +
    coada operator+(const coada &c2) {
        coada c3; // C3 reprezinta coada returnata in urma concatenarii celor 2 cozi.
        Nod *aux;
        aux = first;
        while (aux != NULL) {
            c3.push(aux->info);
            aux = aux->next;
        }
        aux = c2.first;
        while (aux != NULL) {
            c3.push(aux->info);
            aux = aux->next;
        }
        return c3;
    }

    // Supraincarcarea operatorului -
    coada operator-(const coada &c2) {
        coada c3;
        Nod *aux1 = this->first;
        Nod *aux2 = c2.first;
        while (aux1 != NULL && aux2 != NULL) {
            if (aux1->info > aux2->info)
                c3.push(aux1->info);
            else c3.push(aux2->info);
            aux1 = aux1->next;
            aux2 = aux2->next;
        }
        return c3;
    }

    ~coada() {
        while (isempty() != 1)
            pop();
    }

    friend class Nod;

    friend ostream &operator<<(ostream &out, coada &z);

    friend istream &operator>>(istream &in, coada &z);
};

class Coada_sir {
    coada *vector;
    int nr_elem;
public:
    Coada_sir(int nr) : nr_elem(nr) {
        vector = new coada[nr];
    };
    Coada_sir( Coada_sir &aux) {
        nr_elem = aux.nr_elem;
        vector = aux.vector;
    }

    void citire() {
        for (int iterator = 0; iterator < nr_elem; iterator++) {
            int nr;
            cout << "numarul de elemente pt coada " << iterator + 1 << " :";
            cin >> nr;
            while (nr) {
                char caracter;
                cin >> caracter;
                vector[iterator].push(caracter);
                nr--;
            }
        }
    }

    void afisare() {
        for (int iterator = 0; iterator < nr_elem; iterator++) {
            cout << "coada " << iterator + 1 << " : ";
            cout << vector[iterator];
            cout << endl;
        }

    }
    //am folosit un getter pentru a putea lua un element din vector dupa iterator
    coada get(int iterator) {
        return vector[iterator];
    }

    ~Coada_sir() {
        delete[]vector;
    }

};

// Supraincarcarea operatorului <<
ostream &operator<<(ostream &out, coada &z) {
    while (z.isempty() != 1) {
        out << z.first->info << " ";
        z.pop();
    }
}

// Supraincarcarea operatorului >>
istream &operator>>(istream &in, coada &z) {
    char aux;
    in >> aux;
    z.push(aux);
}

int main() {

    Coada_sir queue(3);
    queue.citire();
    coada c, d, e;
    c = queue.get(1);
    d = queue.get(2);
    e = c + d;
    cout << e;
    cout << endl;
    e = c - d;
    cout << endl;
    cout << e;
    cout << endl;
    cout << c;
    cout << endl;
    cout << d;


}
