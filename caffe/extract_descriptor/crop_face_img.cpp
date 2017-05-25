/*
	*	@brief					facial frontalization with non reflection similarity transform \n
	*	@param [in]				inIm				input image \n
	*	@param [in]				EyelocL				Left Eye Position, opencv structure \n
	*	@param [in]				EyelocR				Right Eye Position, opencv structure \n
	*	@param [in]				cropWidth			Width to be cropped image \n
	*	@param [in]				cropHeight			Height to be cropped image  \n
	*	@param [in]				eye_hLevel			eye height position (pixel) in the cropped image (ex. n: 얼굴의 1/n 위치에 눈 위치, dafault = 3) \n
	*	@return					Cropped and frontalized \n
	*/
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

Mat _cropFaceImagebyEYE(Mat inIm, Point2f EyelocL, Point2f EyelocR, int cropWidth, int cropHeight, float feyewidRatio, float feyehLevel)
{
	Mat cropFace, gim, tim;
	float tCropWidth, tCropHeight;

	// Calculate a center of eyes
	float eCenterX = (EyelocL.x + EyelocR.x) / 2;
	float eCenterY = (EyelocL.y + EyelocR.y) / 2;

	// Rotate images by axis of eyes
	double L = sqrtf((float)((EyelocL.x - EyelocR.x)*(EyelocL.x - EyelocR.x) + (EyelocL.y - EyelocR.y)*(EyelocL.y - EyelocR.y)));
	double deg = acos((EyelocR.x - EyelocL.x) / L) * (180 / 3.141592653);

	tCropWidth = L*4.f;
	tCropHeight = L*4.f;

	Point2f sp; sp.x = (eCenterX - tCropWidth * .5f); sp.y = (eCenterY - tCropHeight * .5f);
	
	if (sp.x < 0){
		sp.x = 0.f;
	}
	if (sp.y < 0){
		sp.y = 0.f;
	}

	float xgut = sp.x + tCropWidth - 1;
	float ygut = sp.y + tCropHeight - 1;
	if (xgut >= inIm.cols) tCropWidth = inIm.cols - sp.x - 1;
	if (ygut >= inIm.rows) tCropHeight = inIm.rows - sp.y - 1;

	Rect faceArea(sp.x, sp.y, tCropWidth, tCropHeight);

	tim = inIm(faceArea);

	if (tim.channels() == 3){
		gim = tim.clone();
	}
	else if (tim.channels() == 1){
		cvtColor(tim, gim, CV_GRAY2BGR);
	}
	else{
		return cropFace;
	}

	EyelocL.x = EyelocL.x - sp.x;
	EyelocL.y = EyelocL.y - sp.y;
	EyelocR.x = EyelocR.x - sp.x;
	EyelocR.y = EyelocR.y - sp.y;
	eCenterX = eCenterX - sp.x;
	eCenterY = eCenterY - sp.y;

	Mat sImg0, rotateImg; //원본 img와 1.5배 img
	float tscale = 1.2f;
	float scale = float(cropWidth * feyewidRatio) / float(L);
	int oWidth = gim.cols;
	int oHeight = gim.rows;
	int nWidth = floor(oWidth*scale);
	int nHeight = floor(oHeight*scale);
	cv::resize(gim, sImg0, Size(nWidth, nHeight));
	cv::resize(sImg0, rotateImg, Size(floor(nWidth*tscale), floor(nHeight*tscale)));

	eCenterX = eCenterX*scale;
	eCenterY = eCenterY*scale;

	float tEx = eCenterX*tscale, tEy = eCenterY*tscale;

	EyelocL.x = EyelocL.x*scale;
	EyelocL.y = EyelocL.y*scale;
	EyelocR.x = EyelocR.x*scale;
	EyelocR.y = EyelocR.y*scale;

	float dx = tEx - eCenterX, dy = tEy - eCenterY;

	EyelocL.x = EyelocL.x + dx;
	EyelocL.y = EyelocL.y + dy;
	EyelocR.x = EyelocR.x + dx;
	EyelocR.y = EyelocR.y + dy;

	eCenterX = eCenterX + dx;
	eCenterY = eCenterY + dy;

	Rect trect(dx, dy, sImg0.cols, sImg0.rows);
	//sImg15(trect) = sImg0;
	sImg0.copyTo(rotateImg(trect));

	if (EyelocL.y < EyelocR.y)
		deg = -deg;
	Point2f src_center(eCenterX, eCenterY);
	Mat rotateMat = getRotationMatrix2D(src_center, -deg, 1.0);
	//warpAffine(gim, rotateImg, rotateMat, cv::Size(100,100),2);
	warpAffine(rotateImg, rotateImg, rotateMat, rotateImg.size(), 2);

	Mat Rot_coEye = rotateMat*_eye2cvMat(EyelocL, EyelocR);

	/*circle(rotateImg, Point2d(eCenterX,eCenterY), 1, Scalar(0, 255, 0));*/
	/*circle(rotateImg, EyelocL, 1, Scalar(0,255,0));
	circle(rotateImg, EyelocR, 1, Scalar(0, 255, 0));*/

	int nx, ny;
	/*nx = floor((EyelocL.x + EyelocR.x) / 2 - cropWidth / 2);
	ny = floor(nHeight / 2 - cropHeight / eye_hLevel);*/
	float ftmp = (1.f - feyewidRatio)*0.5;
	nx = floor(EyelocL.x - cropWidth * ftmp);
	ny = floor(EyelocL.y - cropHeight * feyehLevel);
	Rect nFaceRect; nFaceRect.x = nx; nFaceRect.y = ny; nFaceRect.width = cropWidth; nFaceRect.height = cropHeight;
	if (nx < 0 || ny < 0 || nx + cropWidth > rotateImg.cols || ny + cropHeight > rotateImg.rows){
		return cropFace;
	}
	Mat temp = rotateImg(nFaceRect);
	cropFace = temp.clone();

	return cropFace;
}


Mat _eye2cvMat(Point2f lp, Point2f rp)
{
	//Mat co = Mat::ones(3, 68, CV_32FC1);
	Mat_<double> co(3, 2);

	co.at<double>(0, 0) = lp.x;
	co.at<double>(1, 0) = lp.y;
	co.at<double>(2, 0) = 1.f;

	co.at<double>(0, 1) = rp.x;
	co.at<double>(1, 1) = rp.y;
	co.at<double>(2, 1) = 1.f;

	return co;
}