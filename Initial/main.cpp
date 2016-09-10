#include <iostream>
#include "cellules.h"
#include "estimateurs.h"
#include "outils.h"

using namespace std;

int prof_de_test = 8;
int main()
{
	//InitRandom();
	//Initialisation sans bruit, voire constructeur pour enlever les bruits suivants.
	//IntTree* root = new IntTree(0, 0, 1, 0,0) ;
	//Initialisation avec bruit.
	//IntTree* root = new IntTree(0, 0, 1, 0, gaussienne(0, 1)); //On initialise à age_new = 0, age_old = 0 et taux_croissance = 1 et generation = 0.
	//construitArbre(root, 10);
	//double tab2[512];
	//load_tab(root, tab2);

	//Partie sur l'arbre expérimental : on applique nos estimateurs et les statistiques de tests !

	//On génère l'arbre expérimental
	//511=pow(2,9)-1 donc l'arbre expérimental est de profondeur 8, où la racine est à 0.
	//IntTree* arbre_exp = load_experimental();
	/*for (int k = 2; k < 8; k++){
		long double alpha0exp = estim_alpha_eps_r(arbre_exp, 0, k);
		long double alpha1exp = estim_alpha_eps_r(arbre_exp, 1, k);
		long double beta0exp = estim_beta_eps_r(arbre_exp, 0, k);
		long double beta1exp = estim_beta_eps_r(arbre_exp, 1, k);
		cout << "experience " << k << endl << "   " << alpha0exp << " " << alpha1exp << " " << beta0exp << " " << beta1exp << endl;
		//cout << "fixe " <<alpha0 << " " << alpha1 << " " << beta0 << " " << beta1 << endl;
		estim_bruit(arbre_exp, k, alpha0exp, beta0exp, alpha1exp, beta1exp);
		cout << "   Statistique de test 35 : " << stat35(arbre_exp, k) << endl;
		cout << "   Statistique de test 36 : " << stat36(arbre_exp, k) << endl;
	}*/

	//cout << comparaison_erreur(tab2) << endl;

	
	
	/*stack <double> pile_taux;
    queue <IntTree*> file_arbres;
    file_arbres.push(root);
    liste_taux_simules(pile_taux, file_arbres);
    cout << pile_taux.top() <<endl;  
    afficher(pile_taux);*/

	//openWindow(1200, 650);
	//histo35(10);
	//graphicDisplay(arbre_exp, 0, 600, 9);
	//graphicDisplay(root, 0, H / 2, 6);
	//click();
	//endGraphics();

	//arbre_exp->~IntTree();
	double data[100];
	data[99] = 5.4;
	ecrire("test.txt", data);
	return 0;

}

