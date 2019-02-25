#include <iostream>
#include <stdlib.h>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>

using namespace std;


vector<vector<int>> c;
vector<int> pere;
vector<int> d;

void lireFichier (string fileName){
	ifstream file;
	string currentLine;
	istringstream input;
	
	vector < int > values;
	int value;

	file.open(fileName);
	
	while (getline(file, currentLine)){
		input.str(currentLine);
		while(input >> value){
			values.push_back(value);
		}
		c.push_back(values);
		input.clear();
		values.erase(values.begin(), values.end());
	}
}

int min_element (vector <int> Cb){
	int minInd = 0;
	int min = INT_MAX;
	for (int i : Cb){
		if (d[i] > 0 && d[i] < min){
			minInd = i;
			min = d[i];
		}
	}
	return minInd;
}

void display_shortest_paths(vector <int> pere){
	
	for (int i = 0; i < pere.size(); i++){
		cout << pere[i] << " " ;
	}
	cout << endl;
}

void display_all (vector <int> Cb){
	cout << "###########################" << endl;
	cout << "Cb: " << endl;
	for (int i = 0; i < Cb.size(); i++){
		cout << Cb[i] << " ";
	}
	cout << endl << "Pere: " << endl;
	
	for (int i = 0; i < pere.size(); i++){
		cout << pere[i] << " ";
	}

	cout << endl << "D: " << endl;

	for (int i = 0; i < d.size(); i++){
		cout << d[i] << " ";
	}
	cout << endl;
}

void mooreDijsktra (int s = 0){
	vector <int> C(s);
	vector <int> Cb;
	// Initialisation des plus courts chemins (INT_MAX = infini)
	// Et initialisation des chemins
	for (int i = 0; i < c.size(); i++){
		if (i != s){
			Cb.push_back(i);
			d.push_back(INT_MAX);
		}else{
			d.push_back(0);
		}
		pere.push_back(0);
	}
	
	int j = s;
	cout << " 1 er affichage " << endl;
	display_all(Cb);
	cout << " -----------------------" << endl;
	for (int l = 0; l < c.size(); l++){
		for (int i : Cb){
			if (c[j][i] != 0){
				if (d[j] + c[j][i] < d[i]){
					d[i] = d[j] + c[j][i];
					pere[i] = j;
				}
			}
		}

		j = min_element(Cb);
		cout << "Min a dit: " << j << endl;
		for (int i = 0; i < Cb.size(); i++){
			if (Cb[i] == j){
				Cb.erase(Cb.begin() + i);
				break;
			}
		}
		display_all(Cb);
		C.push_back(j);
	}
}





//void display_shortest_paths(vector<int> pere)

int main(int argc, char const *argv[]){
	// Remplissage de la matrice des distances
	if (argc == 2){
		lireFichier (argv[1]);
	}else{
		cout << "Il faut donner un seul argument en entrée" << endl;
		return 0;
	}
	cout << c.size() << endl;
	//vector <int> Cb;
	//= {7,10,3,9};
	//vector <int> d; 
	//= {0,2,7,1,3,6,10,5,12,-1,14};
	//int res = min_element(d, Cb);
	//cout << res << endl;
	mooreDijsktra(); 
	return 0;
}
