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
//#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "classification.h"

using namespace std;

int extract_feature(string in_file_path, string out_file_path)
{
	string in_file = in_file_path;
	string out_file = out_file_path;
	string trained = "/home/wj/work/caffe/extract_descriptor/vgg_face.caffemodel";
	string deply = "/home/wj/work/caffe/extract_descriptor/vgg_face_deploy.prototxt";
	string meandata = "/home/wj/work/caffe/extract_descriptor/mean.binaryproto";
    string blobname = "fc6";
    Classifier classifier(deply, trained, meandata, "none");
    int ndepth = 1;
    int ndim = 4096;
    int nimsz = 224;
    cv::Mat faceimg = cv::imread(in_file);
    cv::Mat input;
    cv::resize(faceimg, input, cv::Size(nimsz, nimsz));
    float *blob = NULL;
    blob = classifier.Extract_Feature(faceimg, blobname, ndim, ndepth, 1, false);
	//int search_dot = in_file.find(".");
	in_file = in_file.substr(in_file.find_last_of("/"),in_file.find_last_of(".")); //remove all except file name
	out_file = out_file + in_file +".txt";
	std::ofstream out(out_file.c_str());
	if(out.is_open())
	{
		for(int i = 0; i < 4096; i++)
			out << blob[i] << endl;
	}
	delete[] blob;
	out.close();
	return 1;
}
int main(int argc, char** argv) {//argv[1] = out put folder, argv[2] = input file path *.jpg

	if(argc == 1)
	{
		cout << "call like this" << endl;
		cout << "./extract_descriptor output_folder input_files" << endl;
		return -1;
	}
	for(int i=2; i<argc; i++)
	{
		extract_feature(argv[i], argv[1]);
	}
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
