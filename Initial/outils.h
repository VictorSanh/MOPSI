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
double gaussienne(double mu,double sigma); //G�n�ration d'une gaussienne de param�tres mu et sigma
void verifie_gaussienne(); //Fonction de v�rification d'une gaussienne
