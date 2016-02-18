#pragma once

#include <cmath>
#include <cassert>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
#include <math.h>

void InitRandom();
double Random(double a, double b);
double gaussienne(double mu,double sigma); //Génération d'une gaussienne de paramètres mu et sigma
void verifie_gaussienne(); //Fonction de vérification d'une gaussienne
