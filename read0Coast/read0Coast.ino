
//------------------------------------------------------------//
//                                                            //
//                         Sample code                        //
//                extracted from this project                 //
//   http://www.codingcoolsh.it/creativeCoding.html#0coast    //
//              it is a Openframeworks sample,                //
//            for R-Pi, to record frame by frame              //
//          data from a kinect 1414 and an arduino            //
//                                                            //
//                                                            //
//                              *                             //
//                             * *                            //
//                                                            //
//                  the 0-coast from make noise               //
//   (http://www.makenoisemusic.com/synthesizers/ohcoast)     //
//                  was used for this project,                //
//            and the ports are assigned as follow :          //
//                                                            //
//  physical mini jack   |     arduino      |   serial msg    // 
//     on the synth :    |  analog port :   |       name :    //
//                                                            //
//      dynamic         ->        0         ->        d       //
//      Slope           ->        1         ->        s       //
//      random Value    ->        2         ->        r       //
//      EON             ->        3         ->        e       //
//                                                            //
//------------------------------------------------------------//


int analogPin0 = 0;
int analogPin1 = 1;
int analogPin2 = 2;
int analogPin3 = 3;
int PUL=7; //define Pulse pin
int DIR=6; //define Direction pin
int ENA=5; //define Enable Pin

int sizeArray = 3;
float val[3];           // variable to store the value read
float* oldVal[3];           // variable to store the value read

bool reverse;

void setup()

{
  for(int i = 0 ; i <= sizeArray; i++){
    *oldVal[i] = val[i] = 0;
  }  
    Serial.begin(9600);          //  setup serial
    
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode (ENA, OUTPUT);
  reverse = true;

}



void loop()

{
  readAll();
}

void readAll(){
  val[0] = analogRead(analogPin0); 
  val[1] = analogRead(analogPin1);
  val[2] = analogRead(analogPin2);
  val[3] = analogRead(analogPin3);
  readVal(0,50,"d");
  readVal(1,90,"s");
  readVal(2,120,"r");
  readVal(3,100,"e");
}

void readVal(float val,int threshold,String yo){
  if(val > threshold){
    Serial.print(yo);
    Serial.print(":");
    Serial.print(val);
    Serial.println("*");
  }
}
void readChangingVal(int x, int threshold, String yo){
  if(diffValRecieved(oldVal[x], val[x])){
    readVal(val[x], threshold, yo);
  }
}
bool diffValRecieved(float * oldVal, float val){
  bool b = false;
  if(val != *oldVal){
    b = true;
    *oldVal = val;
  }
  return b;
}

