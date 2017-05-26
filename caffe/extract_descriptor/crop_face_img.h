/*
	*	@brief					facial frontalization with non reflection similarity transform \n
	*	@param [in]				inIm				input image \n
	*	@param [in]				EyelocL				Left Eye Position, opencv structure \n
	*	@param [in]				EyelocR				Right Eye Position, opencv structure \n
	*	@param [in]				cropWidth			Width to be cropped image \n
	*	@param [in]				cropHeight			Height to be cropped image  \n
	*	@param [in]				eye_hLevel			eye height position (pixel) in the cropped image (ex. n: ¾ó±¼ÀÇ 1/n À§Ä¡¿¡ ´« À§Ä¡, dafault = 3) \n
	*	@return					Cropped and frontalized \n
	*/
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
#include <string>
#include <sstream>
#include <dlib/opencv.h>
using namespace cv;
Mat _cropFaceImagebyEYE(Mat inIm, Point2f EyelocL, Point2f EyelocR, int cropWidth, int cropHeight, float feyewidRatio = 0.4f, float feyehLevel = 0.38f);
Mat _eye2cvMat(Point2f lp, Point2f rp);
