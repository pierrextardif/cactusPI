
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
string port = "/dev/ttyACM0";
int			arduinoVal [4];
string 		aStrings [8];
ofFile text,t;

string originalPath = "/home/pierre101/Documents/OF/apps/myApps/kinectCactusPI__All_01/bin/data/";
string arduinoPath = "arduino/"; 
string kinectPath = "frames/";
int angle = 0;
std::stringstream ss;
vector <string> kinectDepthData;
uint64_t ofGetElapsedTimeMillis();
  //ports on the 0-coast :
  //d for dynamic
  //s for slope EOC
  //r for random gen
  //e for EON

//--------------------------------------------------------------
void cactusPI::setup() {
    ofSetWindowShape(1024, 768);
    ofSetWindowPosition(100, 100);
	ofSetLogLevel(OF_LOG_VERBOSE);
	setPath(kinectPath);
	aStrings[0] = "d";
	aStrings[1] = "s";
	aStrings[2] = "r";
	aStrings[3] = "e";
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0);
	font.load("steiner.otf", 10);
	serial.setup(port, 9600);
	serial.startContinuousRead();
	ofAddListener(serial.NEW_MESSAGE,this,&cactusPI::onNewMessage);

	
	message="";
	
	kinect.setRegistration(true);
    
	kinect.init();
	
	kinect.open();
	if(kinect.isConnected()) {
		ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
		ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
		ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
		ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
	}
	
#ifdef USE_TWO_KINECTS
	kinect2.init();
	kinect2.open();
#endif
	
	colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
	
	ofSetFrameRate(60);
	frame = 0;
}

//--------------------------------------------------------------
void cactusPI::update() {
	ofBackground(100, 100, 100);
	kinect.update();
}

//--------------------------------------------------------------
void cactusPI::draw() {
	
	ofSetColor(255, 255, 255);
	easyCam.begin();
	drawPointCloud();
	easyCam.end();

	string msg;
	msg += "arduino values are:\n";
	msg += aStrings[0] + " = " + to_string(arduinoVal[0])+ "\n";
	msg += aStrings[1] + " = " + to_string(arduinoVal[1])+ "\n";
	msg += aStrings[2] + " = " + to_string(arduinoVal[2])+ "\n";
	msg += aStrings[3] + " = " + to_string(arduinoVal[3])+ "\n";
	font.drawString(msg, 20,50);
}
void cactusPI::drawPointCloud(){
	std::string fileName ="frame_"+to_string(frame)+"testingDepth.json";
	text.open(fileName,ofFile::WriteOnly);
	int w = 640;
	int h = 480;
	int step = 2;
	int index = 0;
	frame +=1;
	ss <<"	{ \"timeStamp\" : "<<ofGetElapsedTimeMillis() <<",\n 	\"data\"	:[";
		for(int y = 0; y < h; y += step) {
			for(int x = 0; x < w; x += step) {
				index = x * y;
				if(kinect.getDistanceAt(x, y) < 50000){
					WriteDepth(kinect.getColorAt(x,y),kinect.getWorldCoordinateAt(x, y));
				}
			}
		}
	ExitFile();
}
//writes a json file every new frame,
//structured like that : 
// { "timeStamp" : 79533,
//  	"data"	:[{	"x"		:	-0,
// 		"y"		:	-0,
// 		"z"		:	0,
// 		"c" 	:	196868
// 				},
// {	"x"		:	-0,
// 		"y"		:	-0,
// 		"z"		:	0,
// 		"c" 	:	196886
// 				}
// ]}
void cactusPI::WriteDepth(ofColor cXYZ, ofVec3f vXYZ){
		ss << "{" <<"	"<< "\"x\"		:	" << *(vXYZ.getPtr())<<",\n"<<"	"<<"	"<< "\"y\"		:	" << *(vXYZ.getPtr()+1)<<",\n"<<"	"<<"	"<< "\"z\"		:	" << *(vXYZ.getPtr()+2) <<",\n"<<"	"<<"	"<< "\"c\" 	:	"<< ofToString(cXYZ.getHex()) << "\n"<< "				},\n";
}
void cactusPI::WriteFastDepth(ofColor cXYZ, ofVec3f vXYZ, int index){
	// #include <stdio.h>
// const unsigned long long size = 8ULL*1024ULL*1024ULL;
// unsigned long long a[size];

// int main()
// {
//     FILE* pFile;
//     pFile = fopen("file.binary", "wb");
//     for (unsigned long long j = 0; j < 1024; ++j){
//         //Some calculations to fill a[]
//         fwrite(a, 1, size*sizeof(unsigned long long), pFile);
//     }
//     fclose(pFile);
//     return 0;
// }
}
void cactusPI::ExitFile(){
	string s = ss.str();
	s.erase(s.end() -2,s.end()-1);
	s += "]}";
	text << s;
	text.close();
	ss.str("");
}

//--------------------------------------------------------------
void cactusPI::exit() {
	// kinect.setCameraTiltAngle(0);
	wrapArduinoJSON();
	kinect.close();
	ExitFile();
	
#ifdef USE_TWO_KINECTS
	kinect2.close();
#endif
}

//--------------------------------------------------------------
void cactusPI::keyPressed (int key) {
	switch (key) {
		case OF_KEY_UP:
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;
			
		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;
	}
}
bool cactusPI::checkFileExist(string fileName){
	bool bFileThere = false;  
	fstream fin;  
	string fileNameInOF = ofToDataPath(fileName); // since OF files are in the data directory, we need to do this  
	fin.open(fileNameInOF.c_str(),ios::in);  
	if ( fin.is_open() ) {  
	    bFileThere =true;  
	}  
	fin.close();
	return bFileThere;
}
//messages sent from the arduino are looking like that : 
// d:100*
// s:45*
// r:22*
// e:150*
//writes a new arduino file every frame.
void cactusPI::onNewMessage(string & message)
{	
	// setPath(arduinoPath);
	std::stringstream s;
	std::string fileName ="arduino_"+to_string(frame)+".json";
	if(checkFileExist(fileName)){
		t.open(fileName,ofFile::Append);
		s << ",\n";
	}else{
		t.open(fileName,ofFile::WriteOnly);
		s << "[";
	}
	s << "{ \"timeStamp\" : "<<ofGetElapsedTimeMillis()<<",\n";
	if(message.find("*") != std::string::npos){
		vector<string> cleanedInput = ofSplitString(message, "*");
		if(cleanedInput[0].find(":") != std::string::npos){
			vector<string> input = ofSplitString(cleanedInput[0], ":");
			for(int i = 0;i<4;i++){
				if(!is_number(input[0])){
					if(input[0] == aStrings[i]){
						arduinoVal[i] = stof(input[1]);
						s << "  \""<<aStrings[i] << "\" : " << input[1]<<"}";
						t << s.str();
						t.close();
					}
				}
			}
		}			
	}
	// setPath(kinectPath);
}
bool cactusPI::is_number( std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
bool cactusPI::contains_particularString( std::string& s1, std::string& s2){
	return(s1.find(s2) != std::string::npos);
}
void cactusPI::setPath(string path){
	ofSetDataPathRoot(originalPath+path);
}
//can't modify content of OFfile the same way as a streamstring:
//it is less elegant, but works fine this way (json structure is respected, with a ] closing the list)
void cactusPI::wrapArduinoJSON(){
	for(int i = 0;i<10000;i++){
		std::stringstream sT;
		ofFile t;
		string name = "frames/arduino_"+to_string(i)+".json";
		if(checkFileExist(name)){
			t.open(name,ofFile::Append);
			t << "]";
			t.close();
		}
	}
}