// Global.h
#ifndef GLOBAL_H
#define GLOBAL_H

#include "ErrorLog.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

extern Error errorLogger; // Déclaration de l'objet global
extern LiquidCrystal_I2C lcd;

enum com {
    FILAIRE,
    BLUETOOTH
  };


#endif