//
// Created by Lonqi on 2017/11/18.
//
#pragma once

#ifndef __MTCNN_NCNN_H__
#define __MTCNN_NCNN_H__
#include "net.h"
//#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;
//using namespace cv;
struct Bbox
{
    float score;
    int x1;
    int y1;
    int x2;
    int y2;
    float area;
    float ppoint[10];
    float regreCoord[4];
};


class MTCNN {

public:
	MTCNN(const string &model_path);
    MTCNN(const std::vector<std::string> param_files, const std::vector<std::string> bin_files);
    ~MTCNN();
	
	void SetMinFace(int minSize);
    void detect(ncnn::Mat& img_, int minsize, int maxsize, std::vector<Bbox>& finalBbox);
  //  void detection(const cv::Mat& img, std::vector<cv::Rect>& rectangles);
      int isInited=0;
  
private:
    void generateBbox(ncnn::Mat score, ncnn::Mat location, vector<Bbox>& boundingBox_, float scale);
    void nms(vector<Bbox> &boundingBox_, const float overlap_threshold, string modelname="Union");
    void refine(vector<Bbox> &vecBbox, const int &height, const int &width, bool square);
    void PNet(ncnn::Mat& img, int minsize, int maxsize, std::vector<Bbox> &firstBbox_);
    void RNet(ncnn::Mat& img, std::vector<Bbox> &firstBbox_, std::vector<Bbox> &secondBbox_);
    void ONet(ncnn::Mat& img, std::vector<Bbox> &secondBbox_, std::vector<Bbox> &thirdBbox_);
    ncnn::Net Pnet, Rnet, Onet;
    //ncnn::Mat img;
    const float nms_threshold[3] = {0.5f, 0.7f, 0.7f};
   
    const float mean_vals[3] = {127.5, 127.5, 127.5};
    const float norm_vals[3] = {0.0078125, 0.0078125, 0.0078125};
	const int MIN_DET_SIZE = 12;
    //std::vector<Bbox> firstBbox_, secondBbox_,thirdBbox_;
    //int img_w, img_h;
	
private://部分可调参数
	const float threshold[3] = { 0.8f, 0.8f, 0.7f };
	const float pre_facetor = 0.709f;
	
};


#endif //__MTCNN_NCNN_H__
