# cactusPI

## Description

This is an **example of code** extracted from a project I finished in December 2017.
The code is writen in **[Openframeworks](http://openframeworks.cc/)**, and runs on raspberry-Pi 3.
It consists in recording *depth data* from a kinect 1414, and record electrical pulses from my modular synth.

You can find it on my website : **[http://www.codingcoolsh.it](http://www.codingcoolsh.it/creativeCoding.html#0coast)**.

There is a second part of the project consisting in the parsing of the frames, which is not ready yet.

![Image of the result](https://github.com/pierrextardif/cactusPI/blob/master/result.gif)

Results of the first iteration of the program : 
[VIDEO](https://vimeo.com/246690522)


The program generates 2 *json files* per frames, with around 10 to 40 frames per seconds.


## How to use it

1. Set up Openframeworks on Raspberry-Pi 3, following the guide from [here](http://openframeworks.cc/setup/raspberrypi/raspberry-pi-getting-started/).

2. Download and extract the content of this repository into your Openframeworks apps folder: `/home/pi/openFrameworks/apps/myapps/`

3. Copy your MakeFile from your empty template example into the folder of the project:
in a new terminal window, enter : 
`cp /home/pi/openFrameworks/examples/empty/emptyExample/{Makefile,config.make} /home/pi/openFrameworks/apps/myApps/cactusPI/`

4. Add the addon to read the serail ports:
Download ofxSimpleSerial from [here](https://github.com/LeoColomb/ofxSimpleSerial).
Extract the content into your addons folder situated here : /home/pi/openFrameworks/addons/ :
`unzip /home/pi/Downloads/ofxSimpleSerial-master.zip -d /home/pi/openFrameworks/addons/`
if you need to install zip type the following comand (fresh PI install does not include zip)
`sudo apt-get install unzip`
You should now have a ofXSimpleSerial folder in your addons folder. 

4. Upload the arduino code on the arduino uno:
	From the the repository folder, open the file called `read0Coast.ino`, situed in the read0Coast folder ( directly from the root of the repository).
	Upload it on the arduino, using the [arduino IDE](https://www.arduino.cc/en/Main/Software).
	Plug some wires on the analog ports 0 -> 4. 
	Here I used a make noise [0-coast](http://www.makenoisemusic.com/synthesizers/ohcoast), cutting some jacks cables and plugged several ports on the arduino, using the following : 



		//----------------------------------------------------------------------------------------------//
		//      			                                                      		//
		//				physical mini jack   |     arduino      |   serial msg		// 
		//				   on the synth :    |  analog port :   |       name :		//
		//                                                            					//
		//      			dynamic         ->        0         ->        d       		//
		//      			Slope           ->        1         ->        s       		//
		//      			random Value    ->        2         ->        r       		//
		//      			EON             ->        3         ->        e       		//
		//      			                                                      		//
		//----------------------------------------------------------------------------------------------//

	Each jack cable has a tension divider, resulting in a lower tension entering the arduino (mV). 
	I used standards values for the resistors.


5. Plug arduino and kinect 1414 to the raspberry-Pi

6. Run it using : 

 `make`

 `make RunRelease`


7. Retrieve json content folder for further use : 
` scp -r pi@raspberrypi.local:/home/pi/openFrameworks/apps/myApps/cactusPI/bin/data/frames/ /home/folderpath/`