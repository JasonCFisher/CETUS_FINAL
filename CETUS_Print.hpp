#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <term.h>
#include <fstream>

using std::string;
using std::cout;
using std::endl;
using std::ifstream;

#ifndef CETUS_PRINT_HPP
#define CETUS_PRINT_HPP

#define LINESIZE 109

const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
const std::string reset("\033[0m");


void printLogo(){

//source - https://www.uow.edu.au/~lukes/TEXTBOOK/notes-cpp/io/readtextfile.html

	cout << green;
	ifstream inFile;
	inFile.unsetf(std::ios_base::skipws);
	inFile.open("./cetus.txt");

	char temp;

	while(inFile >> temp){

		cout << temp;

	}
	cout << endl;
	cout << reset;
}

void ClearScreen(){

	//This is the least complex way to clear the screen and remain system agnostic

	for(int i = 0; i < 75; i++){

		cout << endl;

	}

}

void cetusPrint(string* inText, int color){
	
	switch(color){

		case 0:
			cout << red;
			break;

		case 1:

			cout << green;
			break;

		case 2:

			cout << yellow;
			break;

		case 3:

			cout << cyan;
			break;

		case 4:

			cout << magenta;
			break;

		default:

			break;

	}

	int count = 0;

	for (size_t i = 0; i < inText->length(); i++){

		if(count < LINESIZE){


			cout << inText->at(i);
			count++;
			if(inText->at(i) == '\n'){
	
				count = 0;

			}

		}

		else{

            if(inText->at(i) != ' ' && inText->at(i) != '\n'){
				
				cout << inText->at(i);
               	count++;
				
            }
			else{
				cout << inText->at(i);
				cout << endl;
				count = 0;
            }           
		}
	
	}
	cout << endl << reset;
	
	return;

}

#endif

