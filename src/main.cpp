
//----------------------------------------------------------//
//															//
//						Sample code 						//
//				extracted from this project					//
//	http://www.codingcoolsh.it/creativeCoding.html#0coast 	//
//				it is a Openframeworks sample, 				//
//				for R-Pi, to record frame by frame 			//
// 				data from a kinect 1414 and an arduino 		//
// 															//
// 															//
//----------------------------------------------------------//

#include "cactusPI.h"
#include "ofAppNoWindow.h"

int main() {
	ofSetupOpenGL(400, 400, OF_WINDOW);
	ofRunApp(new cactusPI());
}
