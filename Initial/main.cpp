#include <iostream>
#include "cellules.h"
#include "estimateurs.h"

using namespace std;

int prof_de_test = 14;
int main()
{
    InitRandom();
	//Initialisation sans bruit, voire constructeur pour enlever les bruits suivants.
    IntTree* root = new IntTree(0, 0, 1, 0,0) ;
	//Initialisation avec bruit.
    //IntTree* root = new IntTree(0,0,1,0,gaussienne(0,1)); //On initialise à age_new = 0, age_old = 0 et taux_croissance = 1 et generation = 0.
    construitArbre(root, 8);



    //cout << (*root).taux_croissance << endl;
    /*cout << (*root->getSon(0)).taux_croissance << endl;
    cout << (*root->getSon(1)).taux_croissance << endl;
    cout << (*root->getSon(0)->getSon(0)).taux_croissance << endl;
    cout << (*root->getSon(0)->getSon(1)).taux_croissance << endl;
    cout << (*root->getSon(1)->getSon(0)).taux_croissance << endl;
    cout << (*root->getSon(1)->getSon(1)).taux_croissance << endl;*/

    //double result = 0;
    //somme_taux_croissance_croise(root,1,1,result);
    //cout <<result << endl;


    //cout << "Estimateur de Alpha0 : " << estimateur_alpha_eps_r(root, 0, prof_de_test) << endl;
    //cout << "Estimateur de Alpha1 : " << estimateur_alpha_eps_r(root, 1, prof_de_test) << endl;
    //cout << "Estimateur de Beta0 : " << estimateur_beta_eps_r(root, 0, prof_de_test) << endl;
    //cout << "Estimateur de Beta1 : " << estimateur_beta_eps_r(root, 1, prof_de_test) << endl;
    openWindow(H,H);
    graphicDisplay(root,0,H/2);
    endGraphics();
	root->~IntTree();
    return 0;

}

