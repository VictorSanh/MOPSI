#include <iostream>
#include "cellules.h"

using namespace std;

int main()
{
	InitRandom();
    IntTree* root = new IntTree(0,0,1,0,gaussienne(0,1)); //On initialise à age_new = 0, age_old = 0 et taux_croissance = 1 et generation = 0.
	cout << somme_taux_croissance(root, 0,10) << endl;
 

    openWindow(H,H);
    construitArbre(root,0);
    //root->newDisplay(0,"*");
    graphicDisplay(root,0,H/2);

    endGraphics();
    return 0;

}

