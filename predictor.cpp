#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "ngrams.h"
#include "locale.h"
#include <cmath>

#define UNICODE
#define DEBUG 1

using namespace std;

bool strequals(const char* s1, const char* s2) {
	if(strcmp(s1,s2) == 0)
		return true;
	return false;
}

bool load_ngram_count(const char* bigramfile, const char* trigramfile, Language* lang) {
	FILE* bigramfp, *trigramfp;
	char line[1000];
	int bigram_line = 0;
	int trigram_line = 0;
	char* token = NULL;

	//BIGRAMS
	bigramfp = fopen(bigramfile, "r");
	if(bigramfp == 0) {
		cerr << "Error opening file: " << bigramfile << endl;	
		return false;
	}

	while(fgets(line, 1000, bigramfp)) {
		token = strtok(line, "\t\n\r");

		if(token == NULL) {
			continue;
		}
		else {
			lang->bigrams.insert(pair<char*,int>(token, atoi(strtok(NULL, "\t\n\r"))));
		}
		bigram_line++;
	}
	lang->numbigrams = bigram_line;
	cout << "Loaded file: " << bigramfile << endl;
	fclose(bigramfp);

	token = NULL;

	//TRIGRAMS
	trigramfp = fopen(trigramfile, "r");
	if(trigramfp == 0) {
		cerr << "Error opening file: " << trigramfile << endl;	
		return false;
	}

	while(fgets(line, 1000, trigramfp)) {
		token = strtok(line, "\t\n\r");

		if(token == NULL) {
			continue;
		}
		else {
			lang->trigrams.insert(pair<char*,int>(token, atoi(strtok(NULL, "\t\n\r"))));
		}
		trigram_line++;
	}
	lang->numtrigrams = trigram_line;
	cout << "Loaded file: " << trigramfile << endl;
	fclose(trigramfp);
	return true;
}

void showtrigrams(const char* s) {
	int i = 0;
	char tri[3];	
	while(s[i+2] != '\0') {
		tri[0] = s[i];
		tri[1] = s[i+1];
		tri[2] = s[i+2];
		cout << tri[0] << tri[1] << tri[2] << endl;
		i++;
	}
}

float calculate_probability(Language *lang, const char* s) {
	int i = 0;
	string tri = "";
	string bi = "";
	float result = 0;
	while(s[i+2] != '\0') {
		tri += s[i];
		bi += s[i];
		tri += s[i+1];
		bi += s[i+1];
		tri += s[i+2];

		result += log(lang->trigrams[tri] / lang->bigrams[bi]);

		i++;
		bi = "";
		tri = "";	
	}

	return result;
}

int main(int argc, char** argv) {
	char *locale;
	locale = setlocale(LC_ALL, "");	

	Language langs[5];

	//load corpi
	load_ngram_count("pt/pt.bigrama", "pt/pt.trigrama", &langs[0]);
	cout << "Bigrams found: " << langs[0].numbigrams << endl;
	cout << "Trigrams found: " << langs[0].numtrigrams << endl;
	load_ngram_count("en/en.bigrama", "en/en.trigrama", &langs[1]);
	cout << "Bigrams found: " << langs[1].numbigrams << endl;
	cout << "Trigrams found: " << langs[1].numtrigrams << endl;
	load_ngram_count("de/de.bigrama", "de/de.trigrama", &langs[2]);
	cout << "Bigrams found: " << langs[2].numbigrams << endl;
	cout << "Trigrams found: " << langs[2].numtrigrams << endl;
	load_ngram_count("fr/fr.bigrama", "fr/fr.trigrama", &langs[3]);
	cout << "Bigrams found: " << langs[3].numbigrams << endl;
	cout << "Trigrams found: " << langs[3].numtrigrams << endl;
	load_ngram_count("it/it.bigrama", "it/it.trigrama", &langs[4]);
	cout << "Bigrams found: " << langs[4].numbigrams << endl;
	cout << "Trigrams found: " << langs[4].numtrigrams << endl;

	//ask for a sentence
	string sentence;
	cout << endl << "Write a sentence to predict the language: " << endl;
	getline(cin, sentence);
	sentence = "<<" + sentence + ">";	

	//calculate probabilities
	float pt = calculate_probability(&langs[0], sentence.c_str());
	float en = calculate_probability(&langs[1], sentence.c_str());
	float de = calculate_probability(&langs[2], sentence.c_str());
	float fr = calculate_probability(&langs[3], sentence.c_str());
	float it = calculate_probability(&langs[4], sentence.c_str());

	if(DEBUG) {		
		cout << "Probability (PT): " << pt << endl;	
		cout << "Probability (EN): " << en << endl;
		cout << "Probability (DE): " << de << endl;
		cout << "Probability (FR): " << fr << endl;
		cout << "Probability (IT): " << it << endl;
	}

	//output the prediction
	float prediction = max(pt,max(en,max(de,max(fr,it))));
	cout << "Prediction: "; 
	if(prediction == pt) {
		cout << "Portuguese" << endl;	
	}
	else if(prediction == en) {
		cout << "English" << endl;	
	}
	else if(prediction == de) {
		cout << "German" << endl;	
	}
	else if(prediction == fr) {
		cout << "French" << endl;	
	}
	else {
		cout << "Italian" << endl;	
	}

	return 0;
}
