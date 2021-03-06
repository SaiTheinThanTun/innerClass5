/*
 * Observer.cpp
 *
 *  Created on: Jan 9, 2562 BE
 *      Author: Sai
 */

#include "Observer.h"
#include "Human.h"
#include "Infection.h"
#include "discpp.h"

namespace io {

void Observer::CountingStates(){
	//count the states in a given human array
	//set respective numbers to statesSummary object
	int S_=0,I_=0,R_=0; //new declaration for this function only!!!
	for(int i=0; i<humanMax;i++){
		switch(humanArray[i].infection->GetState()){

		case S: S_++; break;
		case I: I_++; break;
		case R: R_++; break;
		}
	}
	statesSummary.SetS(S_);
	statesSummary.SetI(I_);
	statesSummary.SetR(R_);

}

void Observer::PushOut(){
	//push the values to statesSummaryAll array to be stored for all iterations
	//iterations variable was intended for this but simple array could not be initialized with user input value.
	statesSummaryAll.push_back(statesSummary);
}

void Observer::PatchPlot(States State, int row, int col){
	//current states available: S,I,R
	/*Precondition: Observer object must have statesSummaryAllPatchesAllTime
	Parameters: States, iterations, row, col
	Output: series of plot
	Agnostic of the states*/

	double statesData3D[iterations][row][col];
	std::string title1; // sections of the title
	//double StatesData2D0[row][col];


	//1. Check the State input
	//2. Turn 2D StatesSummary to 3D array of single state info
	if(State == S){
		title1 = "No. of Susceptible at Time ";
		for(int i=0; i< iterations; i++){
			for(int j=0; j<row; j++){
				for(int k=0;k<col; k++){
					statesData3D[i][j][k] = GetSxy(i,((j*row)+k)) ;
				}

			}
		}
	} else if(State == I){
		title1 = "No. of Infected at Time ";
		for(int i=0; i< iterations; i++){
			for(int j=0; j<row; j++){
				for(int k=0;k<col; k++){
					statesData3D[i][j][k] = GetIxy(i,((j*row)+k)) ;
				}

			}
		}
	} else if(State == R){
		title1 = "No. of Recovered at Time ";
		for(int i=0; i< iterations; i++){
			for(int j=0; j<row; j++){
				for(int k=0;k<col; k++){
					statesData3D[i][j][k] = GetRxy(i,((j*row)+k)) ;
				}

			}
		}
	} else std::cout << "Invalid State" << std::endl;

	//3. Loop through until end of iterations, each time producing a plot*/
	for(int i=0; i< iterations; i++){
		std::string title2 = title1+std::to_string(i);
		const char* title = title2.c_str(); //change normal string to c string

		Dislin g;

		g.scrmod ("revers");
		g.setfil ("plot.png");
		g.metafl ("png");
		g.disini ();
		g.pagera ();
		g.hwfont ();

		g.titlin ("3-D Colour Plot of Patches", 2);
		g.titlin (title, 4);

		g.name   ("X-axis", "x");
		g.name   ("Y-axis", "y");
		g.name   ("Z-axis", "z");

		g.intax  ();
		g.autres (col, row);
		g.axspos (300, 1850);
		g.ax3len (2200, 1400, 1400);

		g.graf3  (0.0, col, 0.0, 1.0, 0.0, row, 0.0, 1.0,
				0.0, 8.0, 0.0, 1.0);
		g.crvmat ((double *) statesData3D[i], col, row, 1, 1);

		//g.height (50);
		g.title  ();
		g.disfin ();
	}
}

void Observer::OverallPlot(int stateS, int stateI, int stateR){
	//current states available: S,I,R
	/*OverallPlot(statesSummaryAllPatchesAllTime, State, iterations, row, col)
	Precondition: Observer object must have statesSummaryAllPatchesAllTime
	Parameters: States, iterations
	Output: a single line plot
	Agnostic of the states*/

	double xRay[iterations], SData[iterations], IData[iterations], RData[iterations];

	std::string title1 = ""; // sections of the title
	//double StatesData2D0[row][col];

	//1. Setup X axis
	for(int i=0; i< iterations; i++){
		xRay[i] = i;
	}
	//2. Check if the State is to be plotted
	//2. Turn 2D StatesSummary to an array of total single state info
	if(stateS==1){
		title1 = title1+"S: blue, ";
		for(int i=0; i< iterations; i++){
			SData[i]=0; //to prevent having gibberish numbers in the array
			for(int j=0; j<patchMax; j++){
				SData[i] += GetSxy(i,j) ;
			}
		}
	} else std::cout << "stateS is not included" << std::endl;
	if(stateI==1){
		title1 = title1+"I: red, ";
		for(int i=0; i< iterations; i++){
			IData[i]=0; //to prevent having gibberish numbers in the array
			for(int j=0; j<patchMax; j++){
				IData[i] += GetIxy(i,j) ;
			}
		}
	} else std::cout << "stateI is not included" << std::endl;
	if(stateR==1){
		title1 = title1+"R: black, ";
		for(int i=0; i< iterations; i++){
			RData[i]=0; //to prevent having gibberish numbers in the array
			for(int j=0; j<patchMax; j++){
				RData[i] += GetRxy(i,j) ;
			}
		}
	} else std::cout << "stateR is not included" << std::endl;


	//3. Plot*/
	const char* title = title1.c_str(); //change normal string to c string

	Dislin d;
	d.setfil("plot.png");
	d.metafl("PNG");
	d.scrmod ("revers");

	d.disini ();
	d.pagera();
	d.complx();


	d.axspos(450,1800);
	d.axslen(2200,1200);

	d.name("Time (unit)", "X");
	d.name("No. of Individuals", "Y");

	d.labdig(-1,"X");
	d.ticks(10, "XY");

	d.titlin("No. of Individuals over time", 1);
	d.titlin(title, 3);

	d.graf(0.,iterations,0.,5.,0.,humanMax*.8,0.,humanMax*.1);
	d.title();

	if(stateS==1){
		d.color("BLUE");
		d.curve(xRay,SData,iterations);
	}
	if(stateI==1){
			d.color("RED");
			d.curve(xRay,IData,iterations);
		}
	if(stateR==1){
			d.color("FORE");
			d.curve(xRay,RData,iterations);
		}

	//d.color("FORE");
	//d.dash();
	//d.xaxgit();

	//d.messag ("This is a test", 100, 100);
	d.disfin ();
}

} /* namespace io */
