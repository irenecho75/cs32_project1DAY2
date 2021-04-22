/* ZJW simple C++ code to write out a PPM file representing an ellipse(s) */

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "ppmR.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include "cat.h"

using namespace std;


/*write out PPM data, using the defined implicit equation 
  interior points write a differnt color then exterior points */

void writeOut(ostream& out, ppmR& theWriter, cat inputC) {

	float res;
	color inC;
	color drawC;
	color background(12, 34, 56);
	bool inTrue = false;
	double curDepth = -1.0;

	//for every point in the 2D space
	for (int y=0; y < theWriter.height; y++) {
		for (int x =0; x < theWriter.width; x++) {

			inTrue = false;
			curDepth = -1;
			//iterate through all possible equations (note 'front' determined by order in vector)

			//naive draw that 'always' draws face (extension could modify to return fragment)
			//only overwrite if not background
			drawC = inputC.eval(x, y, background);
			if (drawC == background) {
				//do nothing
			} else {
				inTrue = true;
				inC = drawC;
			}
			
			if (inTrue) {			
				theWriter.writePixel(out, x, y, inC);
			}
			else
				theWriter.writePixel(out, x, y, background);
		}
		theWriter.writeNewLine(out);
	}
}


/*read command line arguments and write out new ascii file of given size */
int main(int argc, char *argv[]) {

	ofstream outFile;
	int sizeX, sizeY;


	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
		exit(0);
	}
	string outFilename;
	sizeX = stoi(argv[1]);
	sizeY = stoi(argv[2]);
	ppmR theWriter(sizeX, sizeY);

	cat sammy;


	outFile.open(argv[3]);
	if (outFile) {
		cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
		theWriter.writeHeader(outFile);
		writeOut(outFile, theWriter, sammy);
	} else {
		cout << "Error cannot open outfile" << endl;
		exit(0);
	}

}
