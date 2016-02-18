#include "cellules.h"
#include "estimateurs.h"
#include <iostream>
#include <sstream>
#include <cassert>

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

int IntTree::getGeneration(){
	return generation;
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

//Construit un arbre qui aura pour profondeur "générationMax", la racine étant la génération 0.
void construitArbre(IntTree* tree, int generationMax){
   if((*tree).generation >=generationMax){
       }
    else{
		if (tree->isAlive()){
			double bruit0 = gaussienne(0, 1);
			tree->addAsLastSon(new IntTree(0, (*tree).age_new + 1, alpha0*(*tree).taux_croissance + beta0+bruit0, (*tree).generation + 1,bruit0));
			construitArbre((*tree).sons[0], generationMax);
			double bruit1 = gaussienne(0, 1);
			tree->addAsLastSon(new IntTree(0, (*tree).age_old + 1, alpha1*(*tree).taux_croissance + beta1+bruit1, (*tree).generation + 1,bruit1));
			construitArbre((*tree).sons[1], generationMax);
		}
   }
}

