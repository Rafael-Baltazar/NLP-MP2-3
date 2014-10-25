// #---------------------------------#
// #             Grupo 3             #
// #    Marcos Germano,  nº 69721    #
// #    Rafael Baltazar, nº 70116    #
// #---------------------------------#

#include <map>

using namespace std;

class Language {
public:
	map<string,float> bigrams;
	int numbigrams;
	map<string,float> trigrams;
	int numtrigrams;
};
