/*! 
* 	\file    haloCapture.cpp
* 	\author  Gabriel Urbain <gurbain@mit.edu> - Visiting student at MIT SSL
* 	\date    September 2014
* 	\version 0.1
* 	\brief   Example showing how to capture and display ORF and STEREO images together
*
* 	License: The MIT License (MIT)
* 	Copyright (c) 2014, Massachussets Institute of Technology
*/

// Project libs
#include "../main.h"
#include "../utils.h"
#include "../defines.h"
#include "../halo.h"

using namespace std;
using namespace cv;


// Allocate variables
Halo halo;

// Create a CTRL-C handler
void exit_handler(int s){
	halo.close();
	exit(1);
}

int main(int argc, char **argv) {
	
	init();
	
	// For catching a CTRL-C
	signal(SIGINT,exit_handler);
	
	// Initialize
	int retVal = halo.init();
	if (retVal !=0 )
		exit_handler(0);
	
	// Capturing loop
	while(true) {
		// Capture everything
		Mat iL, iR, iT, cT, dT;
		retVal = halo.captureAllRectifiedImages(iL, iR, dT, iT, cT);
		if (retVal !=0 )
			exit_handler(0);
		
		// Display everything
		imshow("Depth", dT);
		imshow("Intensity", iT);
		imshow("Confidency", cT);
		imshow("Left", iL);
		imshow("Right", iR);
		
		// Handle pause/unpause and ESC
		int c = cvWaitKey(1);
		if(c == 'p') {
			DEBUG<<"Acquisition is now paused"<<endl;
			c = 0;
			while(c != 'p' && c != 27){
				c = cvWaitKey(250);
			}
			DEBUG<<"Acquisition is now unpaused"<<endl;
		}
		if(c == 27) {
			DEBUG<<"Acquisition has been stopped by user"<<endl;
			break;
		}
	}
	
	// Close cameras
	halo.close();
	
	return 0;
}