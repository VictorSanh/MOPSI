#include <iostream>
#include "cellules.h"
#include "estimateurs.h"

using namespace std;

int prof_de_test = 8;
int main()
{
    InitRandom();
	//Initialisation sans bruit, voire constructeur pour enlever les bruits suivants.
    IntTree* root = new IntTree(0, 0, 1, 0,0) ;
	//Initialisation avec bruit.
    //IntTree* root = new IntTree(0,0,1,0,gaussienne(0,1)); //On initialise à age_new = 0, age_old = 0 et taux_croissance = 1 et generation = 0.
    construitArbre(root, prof_de_test);

    stack <double> pile_taux;
    queue <IntTree*> file_arbres;
    file_arbres.push(root);
    liste_taux_simules(pile_taux,file_arbres);
    cout << pile_taux.top()<<endl;
    //afficher(pile_taux);



    //cout << "Estimateur de Alpha0 : " << estimateur_alpha_eps_r(root, 0, prof_de_test) << endl;
    //cout << "Estimateur de Alpha1 : " << estimateur_alpha_eps_r(root, 1, prof_de_test) << endl;
    //cout << "Estimateur de Beta0 : " << estimateur_beta_eps_r(root, 0, prof_de_test) << endl;
    //cout << "Estimateur de Beta1 : " << estimateur_beta_eps_r(root, 1, prof_de_test) << endl;
    //openWindow(H,H);
    //graphicDisplay(root,0,H/2,prof_de_test);
    //endGraphics();
	root->~IntTree();
    return 0;

}

