#include <iostream>
#include <stdlib.h>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int n = 0;

void affiche (vector <int> ch, vector<vector<int>> f, int min){
	cout << "***** Ch : ******" << endl;
	for (int i = 0; i < n; i++){
		cout << ch[i] << " ";
	}
	cout << endl;
	cout << "******* Flots ******" << endl;
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; j++){
			cout << f[i][j] << " ";
		}
		cout << endl;
	}
	cout << "********* Min *********" << endl;
	cout << min << endl;
	cout << "########################################" << endl;
}

void afficheMatrix (vector<vector<int>> Mat){
	for (int i = 0; i < Mat.size(); i++){
		for (int j = 0; j < Mat.size(); j++){
			cout << Mat[i][j] << " ";
		}
		cout << endl;
	}
}

void chaineaugmentante(vector<int> & ch, vector<vector<int>> c, vector<vector<int>> f, int s, int t, vector<vector<int>> b){
	stack <int> P;
	bool visite[n];
	bool stop = false;

	
	// On initialise ch à false
	for (int i = 0; i < n; i++){
	 	visite[i] = false;
	 	ch.push_back(-1);
	}

	// On commence par le point de départ
	P.push(s);
	int cur;



	// Tant que la pile n'est pas vide ou qu'on est pas au dernier noeud
	while(!P.empty() && stop == false){
		cur = P.top();
		P.pop();

		//Si on est au dernier noeud on met stop a true pour s'arreter
		if (cur == t){
			stop = true;
		}

		//Si on a pas visité le noeud
		else if (visite[cur] == false){
			visite[cur] = true;

			//Pour chaque noeud dans le graphe
			for (int j = 0; j < n; j++){
				//Qui n'a pas été visité
				if (visite[j] == false){
					//On regarde si on peut y aller
					//Si la capacité de cur à j supérieure à 0 et capacité de cur à j supérieure ou égale au flot
					// ou
					// capacité de j à cur supérieure à 0 et flot de cur à j supérieur à 0
					//if (((c[cur][j] > 0) && (c[cur][j] > f[cur][j])) || ((c[j][cur] > 0) && (f[cur][j] > 0))) {
					if (((c[cur][j] > 0) && (c[cur][j] > f[cur][j])) || ((c[j][cur] > 0) && (f[j][cur] >= b[j][cur]))) {
						P.push(j);
						ch[j] = cur;
					}
				}
			}
		}
	}
}


int increment(vector <int> ch, vector<vector<int>> c, vector<vector<int>> & f, int s, int t, vector<vector<int>> b){
	// On initialise le minimum au delta du premier chemin
	int min = c[ch[t]][t] - f[ch[t]][t];
	int delta = -1;
	int i = t;
	int precedent;

	while(i != s){

		precedent = ch[i];

		// cas ou on prend l'arc à l'envers
		if (c[precedent][i] == 0 && f[i][precedent] > b[i][precedent]){
			delta = f[i][precedent] - b[i][precedent];
		}
		else{
			delta = c[precedent][i] - f[precedent][i];
		}

		if (delta < min){
			min = delta;
		}
		
		i = precedent;
	}

	i = t;
	while(i != s){

		precedent = ch[i];

		// cas ou on prend l'arc à l'envers
		if (c[precedent][i] == 0){
			f[i][precedent] -= min;
		}
		else{
			f[precedent][i] += min;
		}
		i = precedent;
	}
	return min;
}


void FlotMax(vector<int> ch, vector<vector<int>> c, vector<vector<int>> & f, int s, int t, vector<vector<int>> b){
	bool stop = false;
	int min;
	while (!stop){
		ch.erase(ch.begin(), ch.end());
		chaineaugmentante(ch, c, f, s, t,b);
		if(ch[t] == -1){
			stop = true;
		}
		else{
			min = increment(ch, c, f, s, t, b);
		}
		affiche(ch, f, min);
	}
	int flotMaximum=0;
	for (int i = 0; i < n; i++){
		flotMaximum += f[0][i];
	}
	cout << "Le flot maximum est: " << flotMaximum << endl;
}

void lireFichier (string fileName, vector<vector<int>> & c, vector<vector<int>> & f){
	ifstream file;
	string currentLine;
	istringstream input;
	
	vector < int > values;
	int value;
	n=0;

	file.open(fileName);
	
	while (getline(file, currentLine)){
		input.clear();
		input.str(currentLine);
		while(input >> value){
			values.push_back(value);
		}
		c.push_back(values);
		values.erase(values.begin(), values.end());
	}
	for (int i = 0; i < c.size(); i ++){
		values.push_back(0);
	}

	if (f.size() == 0){
		for (int j = 0; j < c.size(); j++){
			f.push_back(values);
		}
	}
	n = c.size();
	file.close();
//	afficheMatrix(f);
}

int main(int argc, char const *argv[])
{


	vector <vector <int>> c;
	vector <vector <int>> f;
	vector <vector <int>> b;
	lireFichier(argv[1], c, f);
	lireFichier(argv[2], b, f);

	
	//Matrice des capacité
//	int c[n][n] = {	{0,6,6,0,0,0},
//			{0,0,0,5,0,0},
//			{0,0,0,4,3,0},
//			{0,0,0,0,0,7},
//			{0,0,0,0,0,4},
//			{0,0,0,0,0,0}};


	// Tableau d'une chaine augmantante
	vector < int > ch;

	//Début du graphe
	int s = 0;

	//Fin du graphe
	int t = 5;


	FlotMax(ch, c, f, s, t, b);

	afficheMatrix(f);

	// for (int i = 0; i < ; ++i)
	// {
	// 	/* code */
	// }
	// cout << endl;

	// cout << endl;
	// for (int i = 0; i < n; ++i)
	// {
	// 	cout << ch[i] << " ";
	// }
	// cout << endl;

	return 0;
}
