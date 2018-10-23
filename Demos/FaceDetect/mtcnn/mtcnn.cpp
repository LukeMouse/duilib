//
// Created by Longqi on 2017/11/18..
// Modifed by Caizhwen on 2018/02/28
//

#include "mtcnn.h"
#include <math.h>
#ifdef ANDROID
#include <android/log.h>
#define TAG "Think"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)
#define printf LOGD
#endif
#include <fcntl.h>
#include <unistd.h> 

#define printf

static const int NUM_THREADS = 0;

static bool cmpScore(Bbox lsh, Bbox rsh) {
	if (lsh.score < rsh.score)
		return true;
	else
		return false;
}

//判断路径是否可用
static  int CheckFileAccess(const char *InPath)
{
       //是否是文件且可读写
        if(access(InPath, R_OK | W_OK | F_OK) == 0)
        {
             printf("file exsit and W&R!\n");
             return 0;
        }
        else
        {
            return -1;
        } 
}

//MTCNN::MTCNN(){}
MTCNN::MTCNN(const string &model_path) {
	int nRet = 0;

	if ( 0 == CheckFileAccess(model_path.c_str() ) ){//打包单个资源文件
		FILE*fp = fopen(model_path.c_str(), "rb");
		nRet = Pnet.load_param_bin(fp);
		nRet = Pnet.load_model(fp);
		nRet = Rnet.load_param_bin(fp);
		nRet = Rnet.load_model(fp);
		nRet = Onet.load_param_bin(fp);
		nRet = Onet.load_model(fp);
		fclose(fp);
	}else{  //目录分散多个资源文件
		std::vector<std::string> param_files = {
			model_path + "/det1.param",
			model_path + "/det2.param",
			model_path + "/det3.param"
		};

		std::vector<std::string> bin_files = {
			model_path + "/det1.bin",
			model_path + "/det2.bin",
			model_path + "/det3.bin"
		};
		nRet = Pnet.load_param(param_files[0].data());
		nRet = Pnet.load_model(bin_files[0].data());
		nRet = Rnet.load_param(param_files[1].data());
		nRet = Rnet.load_model(bin_files[1].data());
		nRet = Onet.load_param(param_files[2].data());
		nRet = Onet.load_model(bin_files[2].data());
	}

	if (0 == nRet)
		isInited = 1;
}

MTCNN::MTCNN(const std::vector<std::string> param_files, const std::vector<std::string> bin_files){
	int nRet = 0;
	nRet = Pnet.load_param(param_files[0].data());
	nRet = Pnet.load_model(bin_files[0].data());
	nRet = Rnet.load_param(param_files[1].data());
	nRet = Rnet.load_model(bin_files[1].data());
	nRet = Onet.load_param(param_files[2].data());
	nRet = Onet.load_model(bin_files[2].data());
	if (0 == nRet)
		isInited = 1;
}


MTCNN::~MTCNN(){
    Pnet.clear();
    Rnet.clear();
    Onet.clear();
	isInited = 0;
}

void MTCNN::generateBbox(ncnn::Mat score, ncnn::Mat location, std::vector<Bbox>& boundingBox_, float scale){
    const int stride = 2;
    const int cellsize = 12;
    //score p
    float *p = score.channel(1);//score.data + score.cstep;
    //float *plocal = location.data;
    Bbox bbox;
    float inv_scale = 1.0f/scale;
    for(int row=0;row<score.h;row++){
        for(int col=0;col<score.w;col++){
            if(*p>threshold[0]){
                bbox.score = *p;
                bbox.x1 = round((stride*col+1)*inv_scale);
                bbox.y1 = round((stride*row+1)*inv_scale);
                bbox.x2 = round((stride*col+1+cellsize)*inv_scale);
                bbox.y2 = round((stride*row+1+cellsize)*inv_scale);
                bbox.area = (bbox.x2 - bbox.x1) * (bbox.y2 - bbox.y1);
                const int index = row * score.w + col;
                for(int channel=0;channel<4;channel++){
                    bbox.regreCoord[channel]=location.channel(channel)[index];
                }
                boundingBox_.push_back(bbox);
            }
            p++;
            //plocal++;
        }
    }
}
void MTCNN::nms(std::vector<Bbox> &boundingBox_, const float overlap_threshold, string modelname){
    if(boundingBox_.empty()){
        return;
    }
    sort(boundingBox_.begin(), boundingBox_.end(), cmpScore);
    float IOU = 0;
    float maxX = 0;
    float maxY = 0;
    float minX = 0;
    float minY = 0;
    std::vector<int> vPick;
    int nPick = 0;
    std::multimap<float, int> vScores;
    const int num_boxes = boundingBox_.size();
	vPick.resize(num_boxes);
	for (int i = 0; i < num_boxes; ++i){
		vScores.insert(std::pair<float, int>(boundingBox_[i].score, i));
	}
    while(vScores.size() > 0){
        int last = vScores.rbegin()->second;
        vPick[nPick] = last;
        nPick += 1;
        for (std::multimap<float, int>::iterator it = vScores.begin(); it != vScores.end();){
            int it_idx = it->second;
            maxX = std::max(boundingBox_.at(it_idx).x1, boundingBox_.at(last).x1);
            maxY = std::max(boundingBox_.at(it_idx).y1, boundingBox_.at(last).y1);
            minX = std::min(boundingBox_.at(it_idx).x2, boundingBox_.at(last).x2);
            minY = std::min(boundingBox_.at(it_idx).y2, boundingBox_.at(last).y2);
            //maxX1 and maxY1 reuse 
            maxX = ((minX-maxX+1)>0)? (minX-maxX+1) : 0;
            maxY = ((minY-maxY+1)>0)? (minY-maxY+1) : 0;
            //IOU reuse for the area of two bbox
            IOU = maxX * maxY;
            if(!modelname.compare("Union"))
                IOU = IOU/(boundingBox_.at(it_idx).area + boundingBox_.at(last).area - IOU);
            else if(!modelname.compare("Min")){
                IOU = IOU/((boundingBox_.at(it_idx).area < boundingBox_.at(last).area)? boundingBox_.at(it_idx).area : boundingBox_.at(last).area);
            }
            if(IOU > overlap_threshold){
                it = vScores.erase(it);
            }else{
                it++;
            }
        }
    }
    
    vPick.resize(nPick);
    std::vector<Bbox> tmp_;
    tmp_.resize(nPick);
    for(int i = 0; i < nPick; i++){
        tmp_[i] = boundingBox_[vPick[i]];
    }
    boundingBox_ = tmp_;
}
void MTCNN::refine(vector<Bbox> &vecBbox, const int &height, const int &width, bool square){
    if(vecBbox.empty()){
        cout<<"Bbox is empty!!"<<endl;
        return;
    }
    float bbw=0, bbh=0, maxSide=0;
    float h = 0, w = 0;
    float x1=0, y1=0, x2=0, y2=0;
    for(vector<Bbox>::iterator it=vecBbox.begin(); it!=vecBbox.end();it++){
        bbw = (*it).x2 - (*it).x1 + 1;
        bbh = (*it).y2 - (*it).y1 + 1;
        x1 = (*it).x1 + (*it).regreCoord[0]*bbw;
        y1 = (*it).y1 + (*it).regreCoord[1]*bbh;
        x2 = (*it).x2 + (*it).regreCoord[2]*bbw;
        y2 = (*it).y2 + (*it).regreCoord[3]*bbh;

        
        
        if(square){
            w = x2 - x1 + 1;
            h = y2 - y1 + 1;
            maxSide = (h>w)?h:w;
            x1 = x1 + w*0.5 - maxSide*0.5;
            y1 = y1 + h*0.5 - maxSide*0.5;
            (*it).x2 = round(x1 + maxSide - 1);
            (*it).y2 = round(y1 + maxSide - 1);
            (*it).x1 = round(x1);
            (*it).y1 = round(y1);
        }

        //boundary check
        if((*it).x1<0)(*it).x1=0;
        if((*it).y1<0)(*it).y1=0;
        if((*it).x2>width)(*it).x2 = width - 1;
        if((*it).y2>height)(*it).y2 = height - 1;

        it->area = (it->x2 - it->x1)*(it->y2 - it->y1);
    }
}
void MTCNN::PNet(ncnn::Mat& img, int minsize, int maxsize, std::vector<Bbox> &firstBbox_){
	int img_w = img.w;
	int img_h = img.h;

	firstBbox_.clear();
    float minl = maxsize;
    float m = (float)MIN_DET_SIZE/minsize;
    minl *= m;
    float factor = pre_facetor;
    vector<float> scales_;
    while(minl>MIN_DET_SIZE){
        scales_.push_back(m);
        minl *= factor;
        m = m*factor;
    }
    for (size_t i = 0; i < scales_.size(); i++) {
        int hs = (int)ceil(img_h*scales_[i]);
        int ws = (int)ceil(img_w*scales_[i]);
        ncnn::Mat in;
        resize_bilinear(img, in, ws, hs);
        ncnn::Extractor ex = Pnet.create_extractor();
        ex.set_num_threads(NUM_THREADS);
        ex.set_light_mode(true);
        ex.input(0, in); //"data"
        ncnn::Mat score_, location_;
        ex.extract(12, score_);//"prob1"
        ex.extract(11, location_);//"conv4-2"
        std::vector<Bbox> boundingBox_;
        generateBbox(score_, location_, boundingBox_, scales_[i]);
        nms(boundingBox_, nms_threshold[0]);
        firstBbox_.insert(firstBbox_.end(), boundingBox_.begin(), boundingBox_.end());
        boundingBox_.clear();
    }
}
void MTCNN::RNet(ncnn::Mat& img, std::vector<Bbox> &firstBbox_, std::vector<Bbox> &secondBbox_){
	int img_w = img.w;
	int img_h = img.h;

    secondBbox_.clear();
    int count = 0;
    for(vector<Bbox>::iterator it=firstBbox_.begin(); it!=firstBbox_.end();it++){
        ncnn::Mat tempIm;
        copy_cut_border(img, tempIm, (*it).y1, img_h-(*it).y2, (*it).x1, img_w-(*it).x2);
        ncnn::Mat in;
        resize_bilinear(tempIm, in, 24, 24);
        ncnn::Extractor ex = Rnet.create_extractor();
        ex.set_num_threads(NUM_THREADS);
        ex.set_light_mode(true);
        ex.input(0, in);//"data"
        ncnn::Mat score, bbox;
        ex.extract(15, score);//"prob1"
        ex.extract(14, bbox);//"conv5-2"
        if(*((float*)score.data+score.cstep) > threshold[1]){
            for(int channel=0;channel<4;channel++){
                it->regreCoord[channel]=bbox.channel(channel)[0];//*(bbox.data+channel*bbox.cstep);
            }
            it->area = (it->x2 - it->x1)*(it->y2 - it->y1);
            it->score = score.channel(1)[0];//*(score.data+score.cstep);
            secondBbox_.push_back(*it);
        }
    }
}
void MTCNN::ONet(ncnn::Mat& img, std::vector<Bbox> &secondBbox_, std::vector<Bbox> &thirdBbox_){
	int img_w = img.w;
	int img_h = img.h;

    thirdBbox_.clear();
    for(vector<Bbox>::iterator it=secondBbox_.begin(); it!=secondBbox_.end();it++){
        ncnn::Mat tempIm;
        copy_cut_border(img, tempIm, (*it).y1, img_h-(*it).y2, (*it).x1, img_w-(*it).x2);
        ncnn::Mat in;
        resize_bilinear(tempIm, in, 48, 48);
        ncnn::Extractor ex = Onet.create_extractor();
        ex.set_num_threads(NUM_THREADS);
        ex.set_light_mode(true);
        ex.input(0, in);//"data"
        ncnn::Mat score, bbox, keyPoint;
        ex.extract(21, score);//"prob1"
        ex.extract(19, bbox);//"conv6-2"
        ex.extract(20, keyPoint);//"conv6-3"
        if(score.channel(1)[0] > threshold[2]){
            for(int channel = 0; channel < 4; channel++){
                it->regreCoord[channel]=bbox.channel(channel)[0];
            }
            it->area = (it->x2 - it->x1) * (it->y2 - it->y1);
            it->score = score.channel(1)[0];
            for(int num=0;num<5;num++){
                (it->ppoint)[num] = it->x1 + (it->x2 - it->x1) * keyPoint.channel(num)[0];
                (it->ppoint)[num+5] = it->y1 + (it->y2 - it->y1) * keyPoint.channel(num+5)[0];
            }

            thirdBbox_.push_back(*it);
        }
    }
}
void MTCNN::detect(ncnn::Mat& img_, int minsize, int maxsize, std::vector<Bbox>& finalBbox_) {
	std::vector<Bbox> firstBbox_, secondBbox_, thirdBbox_;
	int img_w = img_.w;
	int img_h = img_.h;

	img_.substract_mean_normalize(mean_vals, norm_vals);

	bool isSkipPNet = false;
	bool isSkipRNet = false;
	bool isSkipONet = false;

	if( finalBbox_.size() > 0 )
	{
		if (24 == minsize && 24 == maxsize) {
			firstBbox_ = finalBbox_;
			printf("input firstBbox_.size()=%u\n", firstBbox_.size());
			isSkipPNet = true;
			isSkipONet = true;
		} else if (1 == finalBbox_.size() && 48 == minsize && 48 == maxsize) {
			secondBbox_ = finalBbox_;
			printf("input secondBbox_.size()=%u\n", secondBbox_.size());
			isSkipPNet = true;
			isSkipRNet = true;
		}
	} 
	
	if (!isSkipPNet)
	{
		PNet(img_, minsize, maxsize, firstBbox_);
		printf("firstBbox_.size()=%u\n", firstBbox_.size());
		//the first stage's nms
		if (firstBbox_.size() < 1) return;
		nms(firstBbox_, nms_threshold[0]);
		refine(firstBbox_, img_h, img_w, true);
		printf("firstBbox_.size()=%u nms\n", firstBbox_.size());
	}

	if (!isSkipRNet){
		//second stage
		RNet(img_, firstBbox_, secondBbox_);
		printf("secondBbox_.size()=%u\n", secondBbox_.size());
		if (secondBbox_.size() < 1) return;
		nms(secondBbox_, nms_threshold[1]);
		refine(secondBbox_, img_h, img_w, true);
		printf("secondBbox_.size()=%u nms\n", secondBbox_.size());
		if (isSkipONet)finalBbox_ = secondBbox_;
	}
		
	if (!isSkipONet) {
		//third stage 
		ONet(img_, secondBbox_, thirdBbox_);
		printf("thirdBbox_.size()=%u\n", thirdBbox_.size());
		if (thirdBbox_.size() < 1) return;
		refine(thirdBbox_, img_h, img_w, true);
		nms(thirdBbox_, nms_threshold[2], "Min");
		finalBbox_ = thirdBbox_;
	}
	printf("finalBbox_.size()=%u nms\n", thirdBbox_.size());
}

//void MTCNN::detection(const cv::Mat& img, std::vector<cv::Rect>& rectangles){
//    ncnn::Mat ncnn_img = ncnn::Mat::from_pixels(img.data, ncnn::Mat::PIXEL_BGR2RGB, img.cols, img.rows);
//    std::vector<Bbox> finalBbox;
//    detect(ncnn_img, finalBbox);
//    const int num_box = finalBbox.size();
//    rectangles.resize(num_box);
//    for(int i = 0; i < num_box; i++){
//        rectangles[i] = cv::Rect(finalBbox[i].x1, finalBbox[i].y1, finalBbox[i].x2 - finalBbox[i].x1 + 1, finalBbox[i].y2 - finalBbox[i].y1 + 1);
//    }
//}
