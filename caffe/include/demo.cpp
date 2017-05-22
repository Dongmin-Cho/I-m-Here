//============================================================================
// Name        : demo.cpp
// Author      : Young Kyoo Hwang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <caffe/caffe.hpp>

#ifdef USE_OPENCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif  // USE_OPENCV

#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <time.h>
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include "classification.h"

using namespace std;

int extract_feature()
{
	string trained = "/home/wj/work/caffe2/include/vgg_face.caffemodel";
	string deply = "/home/wj/work/caffe2/include/deploy.caffemodel";
	string meandata = "/home/wj/work/caffe2/include/mean.binaryproto";
    string blobname = "fc7";
    Classifier classifier(deply, trained, meandata);
    int ndepth = 1;
    int ndim = 4096;
    int nimsz = 224;
    cv::Mat faceimg = cv::imread("/home/wj/work/caffe2/include/ak.png");
    cv::Mat input;
    cv::resize(faceimg, input, cv::Size(nimsz, nimsz));
    float *blob = NULL;
    blob = classifier.Extract_Feature(faceimg, blobname, ndim, ndepth, 1, false);
    delete[] blob;
	return 1;
}
int main() {
	extract_feature();
	//track_landmark_video_YUV();
	//DetectLN_still_images();
	//eval();
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
