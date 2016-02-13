#include "cellules.h"
#include <iostream>
#include <sstream>
#include <cassert>
#include "Imagine\Common.h"

IntTree :: IntTree(int age_new0, int age_old0, double taux_croissance0, int generation0, double bruit0){
	age_new = age_new0 ;
	age_old = age_old0 ;
	double x = modelisation_mort_age(age_old);
	 if (x <= proba_mort){
		 alive = false;
	 }
	 else{
		 alive = true;
	 }
	 taux_croissance = taux_croissance0;
	 generation = generation0;
	 bruit = bruit0;
}

pair<int,int> IntTree :: getData(){
    return pair<int,int>(age_new,age_old);
}

IntTree :: ~IntTree(){
    for(int i=0;i<sons.size();i++)
         delete sons[i];
}

void IntTree :: setData(int age_new0,int age_old0){
      age_new = age_new0;
      age_old = age_old0;
}

bool IntTree::isAlive(){
	return alive;
}

int IntTree :: nbSons(){
    return sons.size();
}


IntTree* IntTree :: getSon(int pos){
    // on déclenche une exception si la position demandée
    //outrepasse la taille du vecteur
    if (pos >= sons.size())
        throw pos;
    return sons[pos];
}


 void IntTree :: setSon(int pos, IntTree* newSon){
 // on déclenche une exception si la position demandée
 //outrepasse la taille du vecteur
      if (pos >= sons.size())
          throw pos;
      sons[pos]=newSon;
}

 void IntTree :: addAsLastSon(IntTree* newSon){
      sons.push_back(newSon);
}

 void IntTree ::removeLastSon(){
    // on signale une erreur si le vecteur est vide

	if (sons.size()==0)
		throw "pas de fils à ce noeud" ;
    sons.pop_back();
 }

void IntTree :: display (){
//récursif donc parcours de l'arbre en profondeur

    cout << age_new<<age_old <<endl;

    if (nbSons()!=0){
        for (int i = 0; i<nbSons();i++)
            sons[i] -> display();

    }
}

void IntTree :: newDisplay(int ordre, string prefix , string indent){

   stringstream indent_number;
   for (int i = 0; i<ordre; i++){
       indent_number << indent;}
   cout << prefix << indent_number.str() << age_new<<age_old <<endl;

    if (nbSons()!=0){
        for (int i = 0; i<nbSons();i++)
            sons[i] -> newDisplay(ordre+1, prefix, indent);
    }

}

void  graphicDisplay(IntTree* tree, int generation, int position){

	if (generation == 8){
	}
	else{
		RGB<byte> color(0, 248 - 31 * (*tree).age_old, 248 - 31 * (*tree).age_old);
		fillCircle(position, espace*generation + 10, 10 * (*tree).taux_croissance, color);
		stringstream ss;
		ss << (*tree).age_new;
		ss << "  ";
		ss << (*tree).age_old;
		drawString(position, espace*generation + 25, ss.str(), BLACK, 7);
		drawLine(position, espace*generation + 10, position + H / pow(2, generation + 2), espace*(generation + 1), BLACK, 2);
		drawLine(position, espace*generation + 10, position - H / pow(2, generation + 2), espace*(generation + 1), BLACK, 2);
		if ((*tree).sons.size() != 0){
			graphicDisplay((*tree).sons[0], generation + 1, position - H / pow(2, generation + 2));
			if ((*tree).sons.size() > 1){
				graphicDisplay((*tree).sons[1], generation + 1, position + H / pow(2, generation + 2));
			}
		}
	}
}


void construitArbre(IntTree* tree, int generation){
   if(generation >=8){
       }
    else{
		if (tree->isAlive()){
			double bruit0 = gaussienne(0, 1);
			tree->addAsLastSon(new IntTree(0, (*tree).age_new + 1, alpha0*(*tree).taux_croissance + beta0+bruit0, (*tree).generation + 1,bruit0));
			construitArbre((*tree).sons[0], generation + 1);
			double bruit1 = gaussienne(0, 1);
			tree->addAsLastSon(new IntTree(0, (*tree).age_old + 1, alpha1*(*tree).taux_croissance + beta1+bruit1, (*tree).generation + 1,bruit1));
			construitArbre((*tree).sons[1], generation + 1);
		}
   }
}

//Fonction qui donne une certaine seuil qui sera comparé à proba_mort, pour simuler aléatoirement la mort des cellules
//en fonction de leur age.
//Modélisation qui est pour le moment linéaire, c'est donc à affiner.
double modelisation_mort_age(int age_old){
	double x = ((double)rand() / (RAND_MAX));
	//cout << x << endl;
	x += 0.001*age_old;
	//cout << x << endl;
	return x;
}

int cardinal(IntTree *tree, int generation){
	// retourner le cardinal de l'arbre jusqu'à la génération "generation"
	if ((*tree).generation > generation){ return 0; }
	else{
		int fils = tree->nbSons();
		int card = 0;
		for (int i = 0; i<fils; i++){
			card += cardinal((*tree).sons[i], generation);
		}
		return card;
	}
}


//Les estimateurs de alpha.
double somme_taux_croissance(IntTree* tree, int i, int r){
	double x = 0;
	if ((*tree).generation <= r){
		for (int k = 0; k < tree->nbSons(); k++){
			x += somme_taux_croissance((*tree).sons[k], i,r);
		}
	}
	return ((*tree).taux_croissance + x);
}
double somme_taux_croissance_next(IntTree* tree, int i, int r){
	double x = 0;
	if ((*tree).generation <= r){
		if (tree->nbSons()>0){
			x += somme_taux_croissance_next((*tree).sons[i], i,r);
		}
	}
	return ((*tree).taux_croissance + x);
}
double somme_taux_croissance_croise(IntTree* tree, int i, int r){
	double x = 0;
	if ((*tree).generation <= r){
		if (tree->nbSons() > 0){
			x += (*tree).taux_croissance*((*(*tree).sons[i]).taux_croissance);
		}
	}
	return  x;
}
double estimateur_alpha(IntTree* tree, int i){
	return 0;
}
