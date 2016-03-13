#pragma once

#include <cmath>
#include <cassert>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
#include <math.h>
#include <queue>
#include <stack>
#include "cellules.h"
using namespace std;

void InitRandom();
double Random(double a, double b);
void liste_taux_simules(stack <double>& pile, queue <IntTree*> file);
double gaussienne(double mu,double sigma); //G�n�ration d'une gaussienne de param�tres mu et sigma
void verifie_gaussienne(); //Fonction de v�rification d'une gaussienne
void afficher(const stack<double>& pile);
