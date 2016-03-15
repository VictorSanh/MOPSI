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
<<<<<<< HEAD
void liste_taux_simules(stack <double>& pile, queue <IntTree*> file);
=======
void liste_taux_simules(stack <double> pile, queue <IntTree*> file);
>>>>>>> a4a1c029f88b497aa3c01b1c4ae7e28d4ea9c525
double gaussienne(double mu,double sigma); //Génération d'une gaussienne de paramètres mu et sigma
void verifie_gaussienne(); //Fonction de vérification d'une gaussienne
void afficher(const stack<double>& pile);
