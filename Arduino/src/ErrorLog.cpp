#include "ErrorLog.h"

/*---------------------------- Classe Error ----------------------------*/
Error::Error() : count(0), capacity(INITIAL_SIZE) {
    errors = new ErrorInfo[capacity];
}

Error::~Error() {
    delete[] errors;
}

void Error::AddError(String error, short importance) {
    if (count >= capacity) {
        DoubleArray();
    }
    if (count < capacity) { // Vérifiez après avoir tenté d'augmenter la taille
        errors[count++] = {error, importance};
    }
}

void Error::ShowError() {
    for (int i = 0; i < count; i++) {
        Serial.print("Error: ");
        Serial.print(errors[i].message);
        Serial.print(" | Importance: ");
        Serial.println(errors[i].importance);
    }
}

void Error::DoubleArray() {
    if (capacity >= MAX_SIZE) return; // Ne pas dépasser la taille maximale

    int newCapacity = capacity * 2;
    if (newCapacity > MAX_SIZE) {
        newCapacity = MAX_SIZE;
    }

    ErrorInfo* newArray = new ErrorInfo[newCapacity];
    for (int i = 0; i < count; i++) {
        newArray[i] = errors[i];
    }

    delete[] errors;
    errors = newArray;
    capacity = newCapacity;
}
