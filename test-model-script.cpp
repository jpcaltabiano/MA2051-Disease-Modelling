/*
 * Joseph Caltabiano Nov 2018
 *
 * Note - would probably be eaiser in matlab
 *
 *********************
 ******* Model *******
 *********************
 * Create a population of indivduals and model the spread of disease throughout them
 * Individuals could have certain charcateristics, such as 
 * 	- Suceptible, recovered, and infected
 * 	- Age
 * The model would have certain paramters such as 
 *	- the contact rate of individuals
 * 	- death rate of individuals
 *  - birth rate of new individuals
 *
 *
 *
 *********************
 ***** Purpsose ******
 *********************
 * This script would model an implementation of the SIR model for the spread of
 * infetcious diseases. User can change input to change different variables in the model
 * which would reflect in the output. Output would be a list of statisttics about the 
 * events that occured during the model and final population statistics
 *
 *
 *
 *
 *********************
 ***** Variables *****
 *********************
 * t = time
 * N = num of indivs in total population
 *
 * S(t) = num of susceptible indivs
 * I(t) = num of infected 	 indivs
 * R(t) = num of recovered   indivs
 *
 * s(t) = S(t)/N = fraction susceptible
 * i(t) = I(t)/N = fraction infected
 * r(t) = R(t)/N = fraction recovered
 *
 * b = num of contacts per day of infected indiv
 * k = fraction of infected that will recover during any given day
 *		ex. if duration of infection is 3 days, then on average 1/3 of currently
 *		infected population will recover each day
 *
 * Hence - num susceptible = -b *s(t) * I(t)
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace::std;

class Indiv {
public:
	/* 
	 1 - susceptible
	 2 - infected
	 3 - recovered
	 */
	int type;
	int days; //numbar of days infected

	Indiv(int type) : type(type), days(0) {}
};

int main(int argc, char **argv) {

	FILE *fp = fopen("output.csv", "a");

	int S, R;

	/*int n = atoi(argv[1]); 		//population
	int I = atoi(argv[2]);		//starting num infected
	int numDays = atoi(argv[3]);		//time in days
	int b = atoi(argv[4]); 		//num of contacts per day
	int recovery = atoi(argv[5]); //num days that disease lasts
	*/
	int n = 300; 		//population
	int I = 5;		//starting num infected
	int numDays = 100;		//time in days
	int b = 4; 		//num of contacts per day
	int recovery = 4; //num days that disease lasts

	//initial values at t = 0
	S = n - I;
	R = 0;


	Indiv *pop = (Indiv *)malloc(n * sizeof(Indiv));
	for (int i = 0; i < n; i++) {
		if (i < I) {
			Indiv a(2);
			pop[i] = a;
		}
		else {
			Indiv a(1);
			pop[i] = a;
		}	
	}

	srand(time(NULL));	
	for (int t = 1; t <= numDays; t++) {
		//each day, infecteds make b contacts meaning they contact
		//b random people every day. could be s i or r people

		//each day, some fraction of the population recovers

		//num new contacts per day = b * I
		//if susceptible, become infected, else no change

		//access b*I random indicies and change types

		for (int i = 0; i < n; i++) {

			//Indiv a = pop[i];
			if (pop[i].type == 2) {
				//printf("%i, ", a.days);
				if (pop[i].days < recovery) {
					pop[i].days++;
					//printf("%i, ", pop[i].days);
				}
				else if (pop[i].days == recovery) {
					pop[i].days = 0;
					pop[i].type = 3;
					//printf("recovered");
				}
			}
		}

		for (int i = 0; i < b * I; i++) {
			//Indiv a = pop[rand() % n];
			if (pop[rand() % n].type == 1) {
				pop[rand() % n].type = 2;
			}
		}

		int s = 0, i = 0, r = 0;
		for (int x = 0; x < n; x++) {
			switch (pop[x].type) {
				case 1: s++; break;
				case 2: i++; break;
				case 3: r++; break;
			}
		}

		printf("S: %i, R: %i, I: %i", s, i, r);
		printf("\n\n");

		fprintf(fp, "%i,%i,%i\n", s, i, r);

	}

}