#include <stdio.h>
#include <iostream>

#include "cvwrapper/Capture.hpp"
#include "cvwrapper/Detector.hpp"
#include "cvwrapper/Window.hpp"
#include "cvwrapper/Image.hpp"
#include "brain/Machine.hpp"

// OpenCV
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <cvaux.h>

// number of training images
#define M 6
// dimention of the image vector (computed later)
static int N = 0;

using namespace cv;
using namespace std;

int main () {

	brain::Machine machine;

	// machine.train("data.json");


	IplImage *img_happy = cvLoadImage("data/happy.jpg");
	IplImage *img_sad = cvLoadImage("data/sad.jpg");

	// read the images size
	CvSize sz = cvGetSize(cvLoadImage("data/happy00.png"));
	N = sz.width * sz.height; // compute the vector image length

	// read the training set images
	char file[64];
	Mat I = Mat(N, M, CV_32FC1);
	Mat S = Mat::zeros(N, 1, CV_32FC1);
	for(int i = 0; i < M/2; i++)
	{
		std::cout << "Load data/happy0" << i << ".png" << std::endl;
		sprintf(file, "data/happy%02d.png", i);
		Mat m = cvLoadImageM(file, CV_LOAD_IMAGE_GRAYSCALE);
		m = m.t();
		m = m.reshape(1, N);
		m.convertTo(m, CV_32FC1);
		m.copyTo(I.col(i));
		S = S + m;
	}
	for(int i = 0; i < M/2; i++)
	{
		std::cout << "Load data/sad0" << i << ".png" << std::endl;
		sprintf(file, "data/sad%02d.png", i);
		Mat m = cvLoadImageM(file, CV_LOAD_IMAGE_GRAYSCALE);
		m = m.t();
		m = m.reshape(1, N);
		m.convertTo(m, CV_32FC1);
		m.copyTo(I.col(i + M/2));
		S = S + m;
	}

	// calculate eigenvectors
	Mat Mean = S / (float)M;
	Mat A = Mat(N, M, CV_32FC1);
	for(int i = 0; i < M; i++) A.col(i) = I.col(i) - Mean;
	Mat C = A.t() * A;
	Mat V, L;
	eigen(C, L, V);

	// compute projection matrix Ut
	Mat U = A * V;
	Mat Ut = U.t();

	// project the training set to the faces space
	Mat trainset = Ut * A;

	cvwrapper::Detector detector;
	cvwrapper::Capture capture;
	cvwrapper::Window result("result");
	cvwrapper::Window face("face", 670, 0);
	cvwrapper::Window logo("logo", 670, 200);

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

		// find the face
		CvRect *roi = detector.detectBestFace(img);
		if (roi == NULL) {
			std::cout << "No face detected..." << std::endl;
			result.display(img);
			continue;
		}
		result.drawRect(img, roi, CV_RGB(200,50,50));

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

		// recognize mood
		double min = 1000000000000000.0;
		int mini;
		Mat subimgmat = mouth;
		subimgmat = subimgmat.t();
		subimgmat = subimgmat.reshape(1, N);
		subimgmat.convertTo(subimgmat, CV_32FC1);
		Mat proj = Ut * subimgmat;

		// find the minimum distance vector
		for(int i = 0; i < M; i++)
		{
			double n = norm(proj - trainset.col(i));
			if(min > n)
			{
				min = n;
				mini = i;
			}
		}

		logo.display(mini == 1 ? img_sad : img_happy);

		// show resultsmov
		face.display(mouth);
		result.display(img);

	}
	return 0;
}
