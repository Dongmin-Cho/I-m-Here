#include <caffe/caffe.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
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
//#include "demoutil.h"

//#define CPU_ONLY

using namespace caffe;  // NOLINT(build/namespaces)  
using std::string;

//struct allandmark
//{
//    float fx[68];
//    float fy[68];
//};

/* Pair (label, confidence) representing a prediction. */
typedef std::pair<string, float> Prediction;

class Classifier {
 public:
  Classifier(const string& model_file,
             const string& trained_file,
             const string& mean_file,
             const string& label_file);

  Classifier(const string& model_file,
      const string& trained_file,
      const string& label_file = "none");

  std::vector<Prediction> Classify(const cv::Mat& img, int N = 5);
  float *Extract_Feature(const cv::Mat& img, std::string blob_name, int ndim, int ndepth, float fscale = 1.0, bool buseMean = false);

  void Go(const cv::Mat& img, float fscale, bool buseMean);

  float *Get_Feature(std::string blob_name, int ndim, int ndepth);

 private:
  void SetMean(const string& mean_file);

  std::vector<float> Predict(const cv::Mat& img);

  void WrapInputLayer(std::vector<cv::Mat>* input_channels);

  void Preprocess(const cv::Mat& img,
                  std::vector<cv::Mat>* input_channels);
  

 private:
  boost::shared_ptr<Net<float> > net_;
  cv::Size input_geometry_;
  int num_channels_;
  cv::Mat mean_;
  std::vector<string> labels_;
  void _ExtFeat(const cv::Mat& img, const string blob_name, const int ndim, const int ndepth, float *fblob);

  void Preprocess(const cv::Mat& img, std::vector<cv::Mat>* input_channels, float fscale, bool bisMean);
};
