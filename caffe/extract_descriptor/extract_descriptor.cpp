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
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include <dlib/image_io.h>

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
#include <dlib/opencv.h>
#include "classification.h"
#include "crop_face_img.h"
using namespace dlib;
using namespace std;
int extract_feature(string in_file_path, string out_file_path)
{
	string in_file = in_file_path;
	string out_file = out_file_path;
	string trained = "/home/wj/work/Im_Here/caffe/extract_descriptor/fitnet.caffemodel";
	string deply = "/home/wj/work/Im_Here/caffe/extract_descriptor/deploy.prototxt";
	string meandata = "/home/wj/work/Im_Here/caffe/extract_descriptor/mean.binaryproto";
    string blobname = "fc7";
    Classifier classifier(deply, trained, meandata, "none");
    int ndepth = 1;
    int ndim = 4096;
    int nimsz = 224;
    cv::Mat faceimg = cv::imread(in_file);
    
    frontal_face_detector detector = get_frontal_face_detector();
    shape_predictor sp;
    deserialize("../../../face_recognition/src/shape_predictor_68_face_landmarks.dat") >> sp;

    array2d<rgb_pixel> img;
	assign_image(img, cv_image<rgb_pixel>(faceimg));
    //load_image(img, in_file_path); 
    
    pyramid_up(img);

    std::vector<dlib::rectangle> dets = detector(img);

    std::vector<full_object_detection> shapes;
    std::vector<dlib::rectangle> rect;

    for (unsigned long j = 0; j < dets.size(); ++j)
    {
        full_object_detection shape = sp(img, dets[j]);
        shapes.push_back(shape);
    }

	for (size_t k = 0; k < shapes.size(); k++)
	{
		float sum_left_x = 0;
		float sum_left_y = 0;
		for(size_t left = 36; left <= 41; left ++)
		{
			sum_left_x += shapes[k].part(left).x();
			sum_left_y += shapes[k].part(left).y();
		}
		float sum_right_x = 0;
		float sum_right_y = 0;
		for(size_t right = 42; right <= 47; right ++)
		{
			sum_right_x += shapes[k].part(right).x();
			sum_right_y += shapes[k].part(right).y();
		}
		cv::Point2f eye_loc_L(sum_left_x/6, sum_left_y/6), eye_loc_R(sum_right_x/6, sum_right_y/6);
		//faceimg = toMat(img);
		cv::Mat input;
		faceimg = toMat(img);
		faceimg = _cropFaceImagebyEYE(faceimg, eye_loc_L, eye_loc_R, nimsz, nimsz, 0.4f, 0.38f);
		float *blob = NULL;
		blob = classifier.Extract_Feature(faceimg, blobname, ndim, ndepth, 1, false);
		in_file = in_file.substr(in_file.find_last_of("/")+1,in_file.find_last_of(".")-in_file.find_last_of("/")-1); //remove all except file name
		out_file = out_file + in_file +".txt";
		//cv::imwrite(out_file+".png",faceimg);
		std::ofstream out(out_file.c_str());
		if(out.is_open())
		{
			for(int i = 0; i < 4096; i++)
				out << blob[i] << endl;
		}
		delete[] blob;
		out.close();
	}
		return 1;
}
int main(int argc, char** argv) 
{//argv[1] = out put folder, argv[2] = input file path *.jpg

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
