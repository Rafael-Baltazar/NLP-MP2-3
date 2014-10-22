#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "ngrams.h"
#include <cmath>

using namespace std;

// Quality of life function
// No need to use strcmp(x,y) == 0 this way
bool strequals(const char* s1, const char* s2) {
	if(strcmp(s1,s2) == 0)
		return true;
	return false;
}

bool load_ngram_count(const char* bigramfile, const char* trigramfile, Language* lang) {
	FILE* bigramfp, *trigramfp;
	char line[100];
	int bigram_line = 0;
	int trigram_line = 0;
	char* token = NULL;

	// BIGRAMS
	bigramfp = fopen(bigramfile, "r");
	if(bigramfp == 0) {
		cerr << "Error opening file: " << bigramfile << endl;	
		return false;
	}

	// Read a line from the file
	while(fgets(line, 100, bigramfp)) {
		// Get the bigram sequence
		token = strtok(line, "\t\n\r");

		if(token == NULL) {
			continue;
		}
		else {
			// Get the number of occurrences and add the bigram to the language
			lang->bigrams.insert(pair<char*,int>(token, atoi(strtok(NULL, "\t\n\r"))));
		}
		bigram_line++;
	}
	lang->numbigrams = bigram_line;
	cout << "Loaded file: " << bigramfile << endl;
	fclose(bigramfp);

	token = NULL;

	// TRIGRAMS
	trigramfp = fopen(trigramfile, "r");
	if(trigramfp == 0) {
		cerr << "Error opening file: " << trigramfile << endl;	
		return false;
	}

	// Read a line from the file
	while(fgets(line, 100, trigramfp)) {
		// Get the trigram sequence
		token = strtok(line, "\t\n\r");

		if(token == NULL) {
			continue;
		}
		else {
			// Get the number of occurrences and add the trigram to the language
			lang->trigrams.insert(pair<char*,int>(token, atoi(strtok(NULL, "\t\n\r"))));
		}
		trigram_line++;
	}
	lang->numtrigrams = trigram_line;
	cout << "Loaded file: " << trigramfile << endl;
	fclose(trigramfp);
	
	return true;
}

float calculate_probability(Language *lang, const char* s) {
	int i = 0;
	string trigram = "";
	string bigram = "";
	float result = 0;

	// Cycle for getting each bigram and trigram of the given sentence
	while(s[i+2] != '\0') {
		trigram += s[i];
		trigram += s[i+1];		
		trigram += s[i+2];
		bigram += s[i];
		bigram += s[i+1];
		
		// Search for the trigram and bigram in the language given
		// and get the number of times it occurred to compute the probability
		result += log(lang->trigrams[trigram] / lang->bigrams[bigram]);

		i++;
		bigram = "";
		trigram = "";	
	}

	return result;
}

int main(int argc, char** argv) {
	char *locale;
	locale = setlocale(LC_ALL, "");	

	Language langs[5];

	// Load all the corpora into the program
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

	// Ask for a sentence
	string sentence;
	cout << endl << "Write a sentence to predict the language: " << endl;
	getline(cin, sentence);
	// Normalize the sentence (we expect punctuation to be correctly separated already)
	sentence = "<<" + sentence + ">";	

	// Calculate the probability for each language
	float pt = calculate_probability(&langs[0], sentence.c_str());
	float en = calculate_probability(&langs[1], sentence.c_str());
	float de = calculate_probability(&langs[2], sentence.c_str());
	float fr = calculate_probability(&langs[3], sentence.c_str());
	float it = calculate_probability(&langs[4], sentence.c_str());
		
	// Show the calculated value for each probability	
	cout << endl << "Log-Probability for sentence: " << endl;
	cout << sentence << endl;
	cout << "(PT): " << pt << endl;	
	cout << "(EN): " << en << endl;
	cout << "(DE): " << de << endl;
	cout << "(FR): " << fr << endl;
	cout << "(IT): " << it << endl;

	// Output the prediction
	float prediction = max(pt,max(en,max(de,max(fr,it))));
	cout << "Prediction: "; 
	if(prediction == pt) {
		cout << "Portuguese (PT)" << endl;	
	}
	else if(prediction == en) {
		cout << "English (EN)" << endl;	
	}
	else if(prediction == de) {
		cout << "German (DE)" << endl;	
	}
	else if(prediction == fr) {
		cout << "French (FR)" << endl;	
	}
	else if(prediction == it) {
		cout << "Italian (IT)" << endl;	
	}
	else {
		cout << "Could not predict language: log(0) = -inf" << endl;
	}
	cout << endl;

	return 0;
}
