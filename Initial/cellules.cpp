#include "cellules.h"

#include <iostream>
#include <sstream>
#include <cassert>

IntTree::IntTree(int age_new0, int age_old0, double taux_croissance0, int generation0, double bruit0){
	age_new = age_new0;
	age_old = age_old0;
	double x = Random(0, 1);
	/*if (x<=proba_deces){
		alive = false;
		new_son_will_live = false;
		old_son_will_live = false;
		}
		if (x>proba_deces && x<= proba_deces + p10){
		alive = true;
		new_son_will_live = true;
		old_son_will_live = true;
		}
		if(x>proba_deces + p10 && x <= proba_deces +p10+p1){
		alive = true;
		new_son_will_live = false;
		old_son_will_live = true;
		}
		if(x> proba_deces+p10+p1){
		alive = true;
		new_son_will_live = true;
		old_son_will_live = false;
		}*/
	alive = true;
	taux_croissance = taux_croissance0;
	generation = generation0;
	bruit = bruit0;
}

pair<int, int> IntTree::getData(){
	return pair<int, int>(age_new, age_old);
}

IntTree :: ~IntTree(){
	for (int i = 0; i < sons.size(); i++)
		delete sons[i];
}

void IntTree::setData(int age_new0, int age_old0){
	age_new = age_new0;
	age_old = age_old0;
}

bool IntTree::isAlive(){
	return alive;
}
void IntTree::setAlive(bool deadoralive){
	alive = deadoralive;
}
bool IntTree::new_son_alive(){
	return new_son_will_live;
}

bool IntTree::old_son_alive(){
	return old_son_will_live;
}

int IntTree::getGeneration(){
	return generation;
}

double IntTree::getTauxCroissance() {
	return taux_croissance;
}

int IntTree::nbSons(){
	return sons.size();
}


IntTree* IntTree::getSon(int pos){
	// on déclenche une exception si la position demandée
	//outrepasse la taille du vecteur
	if (pos >= sons.size())
		throw pos;
	return sons[pos];
}


void IntTree::setSon(int pos, IntTree* newSon){
	// on déclenche une exception si la position demandée
	//outrepasse la taille du vecteur
	if (pos >= sons.size())
		throw pos;
	sons[pos] = newSon;
}

void IntTree::addAsLastSon(IntTree* newSon){
	sons.push_back(newSon);
}

void IntTree::removeLastSon(){
	// on signale une erreur si le vecteur est vide

	if (sons.size() == 0)
		throw "pas de fils à ce noeud";
	sons.pop_back();
}

void IntTree::display(){
	//récursif donc parcours de l'arbre en profondeur

	cout << age_new << age_old << endl;

	if (nbSons() != 0){
		for (int i = 0; i < nbSons(); i++)
			sons[i]->display();

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

void  graphicDisplay(IntTree* tree, int generation, int position, int profondeur) {

	if (generation == profondeur) {
	}
	else {
		RGB<byte> color(0, 248 - 31 * (*tree).age_old, 248 - 31 * (*tree).age_old);
		fillCircle(position, espace*generation + 10, 10 * (*tree).taux_croissance, color);
		stringstream ss;
		ss << (*tree).age_new;
		ss << "  ";
		ss << (*tree).age_old;
		drawString(position, espace*generation + 25, ss.str(), BLACK, 7);
		if (generation <profondeur - 1) {
			drawLine(position, espace*generation + 10, position + H / pow(2, generation + 2), espace*(generation + 1), BLACK, 2);
			drawLine(position, espace*generation + 10, position - H / pow(2, generation + 2), espace*(generation + 1), BLACK, 2);
		}
		if ((*tree).sons.size() != 0) {
			graphicDisplay((*tree).sons[0], generation + 1, position - H / pow(2, generation + 2), profondeur);
			if ((*tree).sons.size() > 1) {
				graphicDisplay((*tree).sons[1], generation + 1, position + H / pow(2, generation + 2), profondeur
					);
			}
		}
	}
}

//Construit un arbre qui aura pour profondeur "générationMax", la racine étant la génération 0.
void construitArbre(IntTree* tree, int generationMax){
	if ((*tree).generation >= generationMax){
	}
	else{
		if (tree->isAlive()){
			//double bruit0 = 0;
			double bruit0 = gaussienne(0, 1);
			double new_taux_croissance = alpha0*(*tree).taux_croissance + beta0 + bruit0;
			IntTree* new_son = new IntTree(0, (*tree).age_new + 1, new_taux_croissance, (*tree).generation + 1, bruit0);
			if (tree->new_son_alive())
				new_son->setAlive(true);
			else
				new_son->setAlive(false);
			tree->addAsLastSon(new_son);
			construitArbre((*tree).sons[0], generationMax);

			//double bruit1 = 0;
			double bruit1 = gaussienne(0, 1);
			double old_taux_croissance = alpha1*(*tree).taux_croissance + beta1 + bruit1;
			IntTree* old_son = new IntTree(0, (*tree).age_old + 1, old_taux_croissance, (*tree).generation + 1, bruit1);
			if (tree->old_son_alive())
				old_son->setAlive(true);
			else
				old_son->setAlive(false);
			tree->addAsLastSon(old_son);
			construitArbre((*tree).sons[1], generationMax);
		}
	}
}

//Fonction qui remplit les estimateurs de bruit
void estim_bruit(IntTree* tree, int r, long double alpha0, long double beta0, long double alpha1, long double beta1){
	if (tree->getGeneration() == 0){ 
		(*tree).estim_bruit = (*tree).bruit; 
		(*tree->getSon(0)).estim_bruit = -alpha0*(*tree).taux_croissance - beta0 + (*tree->getSon(0)).taux_croissance;
		estim_bruit(tree->getSon(0), r, alpha0, beta0, alpha1, beta1);
		(*tree->getSon(1)).estim_bruit = -alpha1*(*tree).taux_croissance - beta1 + (*tree->getSon(1)).taux_croissance;
		estim_bruit(tree->getSon(1), r, alpha0, beta0, alpha1, beta1);
	}
	else if (tree->getGeneration() <= r){
		(*tree->getSon(0)).estim_bruit = -alpha0*(*tree).taux_croissance - beta0 + (*tree->getSon(0)).taux_croissance;
		estim_bruit(tree->getSon(0), r, alpha0, beta0, alpha1, beta1);
		(*tree->getSon(1)).estim_bruit = -alpha1*(*tree).taux_croissance - beta1 + (*tree->getSon(1)).taux_croissance;
		estim_bruit(tree->getSon(1), r, alpha0, beta0, alpha1, beta1);
	}
	else{ (*tree).estim_bruit = (*tree).bruit; }
}

void liste_taux_simules(stack <double>& pile_taux, queue <IntTree*> file_arbres) {
	if (file_arbres.empty()) {
		cout << "c'est fini !" << endl;
	}
	else {
		int size = file_arbres.size();
		//en parcourant chaque élément de la file :
		for (int i = 0; i< size; i++) {
			IntTree* current_tree = file_arbres.front();
			//on ajoute le taux de l'arbre courant à la pile
			double newTaux = current_tree->getTauxCroissance();
			pile_taux.push(newTaux);
			cout << pile_taux.top() << endl;
			//on ajoute les fils de l'arbre courant
			for (int j = 0; j<(*current_tree).sons.size(); j++) {
				file_arbres.push((*current_tree).sons[j]);
			}
			//on enlève l'arbre courant de la file
			file_arbres.pop();
			i++;
		}
		liste_taux_simules(pile_taux, file_arbres);
	}

}

IntTree* load_experimental(){
	IntTree* arbre_exp = new IntTree(0, 0, 1, 0, 0);
	construitArbre(arbre_exp, 8);
	std::queue<IntTree*> fifo;
	int i = 0;
	fifo.push(arbre_exp);
	while (fifo.empty() == false && i<512){
		IntTree* node = fifo.front();
		(*node).taux_croissance = tab[i];
		fifo.pop();
		i++;
		if (node->getGeneration() < 8){
			fifo.push(node->getSon(0));
			fifo.push(node->getSon(1));
		}
	}
	cout << "Arbre experimental charge ! Have fun now !" << endl;
	return arbre_exp;
}

void load_tab(IntTree* arbre, double tab1[512]){
	std::queue<IntTree*> fifo;
	int i = 0;
	fifo.push(arbre);
	while (fifo.empty() == false && i<512){
		IntTree* node = fifo.front();
		tab1[i] = (*node).taux_croissance;
		fifo.pop();
		i++;
		if (node->getGeneration() < 8){
			fifo.push(node->getSon(0));
			fifo.push(node->getSon(1));
		}
	}
}