
//----------------------------------------------------------//
//															//
//						Sample code 						//
//				extracted from this project					//
//	http://www.codingcoolsh.it/creativeCoding.html#0coast 	//
//				it is a Openframeworks sample, 				//
//				for R-Pi, to record frame by frame 			//
// 				data from a kinect and an arduino 			//
// 															//
// 															//
//----------------------------------------------------------//

#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxSimpleSerial.h"
#include <vector>
#include "ofUtils.h"

class cactusPI : public ofBaseApp {
public:
	
	void 		setup();
	void 		update();
	void 		draw();
	void 		exit();
	void 		drawPointCloud();
	void 		keyPressed(int key);
	void 		readTxt();
	void 		WriteDepth(ofColor cXYZ, ofVec3f vXYZ);
	void 		WriteFastDepth(ofColor cXYZ, ofVec3f vXYZ, int index);
	void		onNewMessage( string & message);
	bool 		is_number( std::string& s);
	bool		contains_particularString( std::string& s1, std::string& s2);
	void 		setPath(string path);
	bool 		checkFileExist(string fileName);
	void 		ExitFile();
	void 		wrapArduinoJSON();
	
	ofxKinect 			kinect;
	ofxCvColorImage 	colorImg;
	ofxCvGrayscaleImage grayImage;
	ofxCvGrayscaleImage grayThreshNear;
	ofxCvGrayscaleImage grayThreshFar;
	ofxCvContourFinder 	contourFinder;
	
	int 				angle;
	int 				frame;
	bool 				trueSerial;
	ofEasyCam 			easyCam;
	ofFile 				text;
	vector<ofVec3f> 	vect3D;
	ofxSimpleSerial		serial;
	string				message;
	ofTrueTypeFont		font;
};
