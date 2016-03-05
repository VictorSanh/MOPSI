#include "outils.h"

using namespace std;
using namespace Imagine;

void InitRandom(){
	srand((unsigned int)time(0));
}
double Random(double a, double b){
	double x = double(rand()) / RAND_MAX;
	return a + (b - a)*x;
}

double gaussienne(double mu, double sigma){
	//g�n�ration de gaussienne selon la m�thode de Box Muller
	double y, z;
	double x1, x2;
	x1 = Random(0, 1);
	x2 = Random(0, 1);
	y = sqrt(-2 * log(x1))*cos(2 * 3.1415*x2);
	z = mu + sigma*y;
	return z;
}

void verifie_gaussienne(){
	//� mettre dans le main pour v�rifier
	double tab[100];
	for (int i = 0; i < 100; i++){
		tab[i] = gaussienne(0, 1);
	}

	int histogramme[4];
	for (int i = 0; i<100; i++){
		if (tab[i] <= -2)
			histogramme[0] += 1;
		else if (tab[i] > -2 && tab[i] <= 0)
			histogramme[1] += 1;
		else if (tab[i]>0 && tab[i] <= 2)
			histogramme[2] += 1;
		else if (tab[i] > 2){
			histogramme[3] += 1;
		}
	}
	for (int i = 0; i < 4; i++){
		drawLine(20 * i, 512, 20 * i, 512 - histogramme[i], BLUE, 10);
	}
}
