#include <iostream>
#include "cellules.h"

using namespace std;

int main()
{
	InitRandom();
    IntTree* root = new IntTree(0,0,1,0,gaussienne(0,1)); //On initialise à age_new = 0, age_old = 0 et taux_croissance = 1 et generation = 0.
 

    openWindow(H,H);
    construitArbre(root,2);
    //root->newDisplay(0,"*");
    graphicDisplay(root,0,H/2);

    endGraphics();
	cout << (*root).taux_croissance << endl;
	cout << (*root->getSon(0)).taux_croissance << endl;
	cout << (*root->getSon(1)).taux_croissance << endl;
	double result = 0;
	somme_taux_croissance_next(root, 0, 0, result);
	cout <<cardinal(root,2) << endl;

    return 0;

}

