#ifndef ERROR_H
#define ERROR_H

#include <Arduino.h>

#define INITIAL_SIZE 5
#define MAX_SIZE 40 // Définir selon la mémoire disponible et les besoins

/*---------------------------- Classe Error ----------------------------*/
struct ErrorInfo {
    String message;
    short importance;
};

class Error {
public:
    Error();
    ~Error();
    void ShowError();
    void AddError(String error, short importance);

private:
    ErrorInfo* errors;
    int count;       // Nombre d'erreurs actuellement stockées
    int capacity;    // Capacité actuelle du tableau

    void DoubleArray(); // Méthode pour augmenter la capacité du tableau
};

#endif // ERROR_H
