#include <map>

using namespace std;

class Language {
public:
	map<string,float> bigrams;
	int numbigrams;
	map<string,float> trigrams;
	int numtrigrams;
};
