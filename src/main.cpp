#include <stdio.h>
#include <iostream>

#include "cvwrapper/Capture.hpp"
#include "cvwrapper/Detector.hpp"
#include "cvwrapper/Window.hpp"
#include "cvwrapper/Image.hpp"
#include "brain/Machine.hpp"

int main() {

	brain::Machine machine;

	machine.train("data.json");


	IplImage *img_happy = cvLoadImage("data/happy.jpg");
	IplImage *img_sad = cvLoadImage("data/sad.jpg");

	cvwrapper::Detector detector;
	cvwrapper::Capture capture;
	cvwrapper::Window mainWindow("emotion detector");
	cvwrapper::Window mouthWindow("your mouth", 670, 0);
	cvwrapper::Window smileyWindow("your emotion", 670, 200);

	// counters used for frame capture
	int happy_count = 0;
	int sad_count = 0;

	while(1)
	{
		// Get one frame
		IplImage *img = capture.queryFrame();

		// read the keyboard
		int c = cvWaitKey(50);
		if((c & 255) == 27) break; // quit the program when ESC is pressed

		// find the mouth
		CvRect *roi = detector.detectBestFace(img);
		if (roi == NULL) {
			std::cout << "No face detected..." << std::endl;
			mainWindow.display(img);
			continue;
		}
		mainWindow.drawRect(img, roi, CV_RGB(200,50,50));

		// Get the mouse and set it in black and white
		IplImage *mouth = cvwrapper::equalizeImage(
				cvwrapper::ajustImage(img, roi, 0.7, 0.6));

		switch(c) // capture a frame when H (happy) or S (sad) is pressed
		{
			char file[32];
			case 'h':
				sprintf(file, "data/happy%02d.png", happy_count);
				cvSaveImage(file, mouth);
				happy_count++;
				cvWaitKey(1000);
				break;
			case 's':
				sprintf(file, "data/sad%02d.png", sad_count);
				cvSaveImage(file, mouth);
				sad_count++;
				cvWaitKey(1000);
				break;
		}

		smileyWindow.display(machine.isSmile(mouth) ? img_happy : img_sad);
		mouthWindow.display(mouth);
		mainWindow.display(img);

	}
	return 0;
}
