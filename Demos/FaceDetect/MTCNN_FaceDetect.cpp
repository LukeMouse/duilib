#include <string>
#include <vector>
#include <unistd.h>
// ncnn
#include "net.h"

#include "mtcnn.h"
#include "MTCNN_FaceDetect.h"

using namespace std;

#ifdef ANDROID
#include "AndroidLog.h"
#else
#define LOGD 
#endif

static MTCNN *mtcnn;

//sdk是否初始化成功
bool detection_sdk_init_ok = false;

bool MTCNN_FaceDetectionModelInit( const char* faceDetectionModelPath) 
{
     //LOGD("JNI开始人脸检测模型初始化");
    //如果已初始化则直接返回
    if (detection_sdk_init_ok) {
        //  LOGD("人脸检测模型已经导入");
        return true;
    }

	string tFaceModelDir;
    //获取MTCNN模型的绝对路径的目录（不是/aaa/bbb.bin这样的路径，是/aaa/)
    if (NULL == faceDetectionModelPath) {
		char szworDir[260] = { 0 };
		getcwd(szworDir, 260);
		tFaceModelDir = szworDir;
    }
	else
	{
		tFaceModelDir = faceDetectionModelPath;
	}

	//string tLastChar = tFaceModelDir.substr(tFaceModelDir.length() - 1, 1);
	//LOGD("init, tFaceModelDir last =%s", tLastChar.c_str());

    LOGD("FaceModelPath =%s", tFaceModelDir.c_str());

    mtcnn = new MTCNN(tFaceModelDir);
    if(mtcnn->isInited){
		detection_sdk_init_ok = true;
    }else{
		detection_sdk_init_ok = false;
	}
    
    return detection_sdk_init_ok;
}

#if 0
int  MTCNN_FaceDetect(int image_num, const THID_Image *images, THID_Face **faces, int *face_counts,
	int min_face_size = 0, int max_face_size = 0, const THID_Rect *rois = 0)
{
	//  LOGD("JNI开始检测人脸");
	if (!detection_sdk_init_ok){
		LOGD("人脸检测MTCNN模型SDK未初始化，直接返回空");
		return 8;
	}

	if (nImgWidth<20 || nImgHeight<20){
		LOGD("导入数据的宽和高小于20，直接返回空");
		return -99;
	}

	mtcnn->SetMinFace(nMinFaceSize);

	ncnn::Mat ncnn_img;
	if (images[0].channel == 1)
	{
		ncnn_img = ncnn::Mat::from_pixels(images[0].raw, ncnn::Mat::PIXEL_GRAY2RGB, images[0].width, images[0].height);
	}
	else if (images[0].channel == 3)
	{
		ncnn_img.create(images[0].width, images[0].height, images[0].channel);
		for (int c = 0; c < images[0].channel; c++){
			float*pDst = ncnn_img.channel(c);
			const unsigned char *pSrc = images[0].raw + (images[0].width*images[0].height*c);
			for (int i = 0; i < images[0].width*images[0].height; i++){
				pDst[i] = pSrc[i];
			}
		}
	}
	else
	{
		LOGD("image channel error\n");
		return -99;
	}

	std::vector<Bbox> finalBbox;
	mtcnn->detect(ncnn_img, finalBbox);

	int32_t num_face = static_cast<int32_t>(finalBbox.size());
	
	LOGD("检测到的人脸数目：%d\n", num_face);
	face_counts[0] = num_face< face_counts[0] ? num_face : face_counts[0];
	//printf("facenum =%d\n",*facenum );
	for (int i = 0; i < face_counts[0]; i++)
	{
		faces[0][i].rect.left = finalBbox[i].x1;//left
		faces[0][i].rect.left.top = finalBbox[i].y1;//left
		faces[0][i].rect.left.right = finalBbox[i].x2;//left
		faces[0][i].rect.left.bottom = finalBbox[i].y2;//left
		faces[0][i].rect.left.confidence = finalBbox[i].score * 100;

		faces[0][i].feature_points.point_count = 5;
		for (int j = 0; j < 5; j++)
		{
			faces[0][i].feature_points.points[j].x = finalBbox[i].ppoint[j * 2];  // float
			faces[0][i].feature_pointspoints[j].y = finalBbox[i].ppoint[j * 2 + 1];  // float
		}
	}
	//printf("over\n" );fflush(stdout);
	return 0;
}
#endif

int MTCNN_FaceDetect(const unsigned char *pbyRGbImage, const unsigned char *pbyGrayImage, int nImgWidth,
int nImgHeight, int nMinFaceSize, int nMaxFaceSize, THIDFace *pFace, int *facenum)
{
    //  LOGD("JNI开始检测人脸");
    if(!detection_sdk_init_ok){
        LOGD("FaceDetect MTCNN NotInited");
        return 8;
    }

    if(nImgWidth<20||nImgHeight<20){
        LOGD("nImgWidth,nImgHeight TooSmall(<20)");
        return -99;
    }

    int channel = 3;
    if( NULL == pbyRGbImage ){
		if( NULL != pbyGrayImage )
			channel = 1;
		else
			return -99;
    }

    ncnn::Mat ncnn_img;
    if( 1 == channel )
    {		
        ncnn_img = ncnn::Mat::from_pixels(pbyGrayImage, ncnn::Mat::PIXEL_GRAY2RGB, nImgWidth, nImgHeight);
    }else{
	ncnn_img.create( nImgWidth, nImgHeight, 3 );
	for(int c=0; c<3; c++){
		float*pDst = ncnn_img.channel(c);
		 const unsigned char *pSrc = pbyRGbImage+(nImgWidth*nImgHeight*c);
		for(int i=0; i<nImgWidth*nImgHeight; i++){
			pDst[i] = pSrc[i];
		}
	}
    }

    std::vector<Bbox> finalBbox;
	//满足条件（有人脸且最大脸最小脸固定为24）的直接进入Det2，输入原图像及长宽
	if (0 < *facenum && nMinFaceSize == 24 && nMaxFaceSize == 24 ) {
		Bbox bbox = { 0 };
		memset(&bbox, 0, sizeof(bbox));
		bbox.score = 0.9f;
		for (int i = 0; i < *facenum; i++) {
			bbox.x1 = pFace[i].face_rect.left;
			bbox.y1 = pFace[i].face_rect.top;
			bbox.x2 = pFace[i].face_rect.right;
			bbox.y2 = pFace[i].face_rect.bottom;
			bbox.area = (bbox.x2 - bbox.x1) * (bbox.y2 - bbox.y1);
			finalBbox.push_back(bbox);
		}
		
	}

    //满足条件（有人脸且最大脸最小脸固定为24）的直接进入Det3，图像要裁剪成正方形
    if( 1 == *facenum && nMinFaceSize == 48 && nMaxFaceSize == 48 && nImgWidth == nImgHeight ){
		Bbox bbox={0.7, 0, 0, nImgWidth, nImgHeight, (float)nImgWidth*nImgHeight};
		finalBbox.push_back(bbox);		
    }
	
    mtcnn->detect(ncnn_img, nMinFaceSize,  nMaxFaceSize, finalBbox);

    int32_t num_face = static_cast<int32_t>(finalBbox.size());
    LOGD("MTCNN FaceNum：%d\n", num_face);


		*facenum = num_face<*facenum ? num_face : *facenum;
//printf("facenum =%d\n",*facenum );
		for (int i = 0; i < *facenum; i++)
		{
			pFace[i].face_rect.left = finalBbox[i].x1;//left
			pFace[i].face_rect.top = finalBbox[i].y1;//left
			pFace[i].face_rect.right = finalBbox[i].x2;//left
			pFace[i].face_rect.bottom = finalBbox[i].y2;//left
			pFace[i].face_rect.confidence = finalBbox[i].score * 100;

			pFace[i].feat_count = 5;
			for (int j = 0; j < 5; j++)
			{
				pFace[i].feat_point[j].x = finalBbox[i].ppoint[j ];  // float
				pFace[i].feat_point[j].y = finalBbox[i].ppoint[j  + 5];  // float
			}
		}
//printf("over\n" );fflush(stdout);
    return 0;
}

bool MTCNN_FaceDetectionModelUnInit() {
    if(!detection_sdk_init_ok){
        LOGD("FaceDetect MTCNN Already Inited");
        return true;
    }
    bool tDetectionUnInit = false;
    delete mtcnn;


    detection_sdk_init_ok=false;
    tDetectionUnInit = true;
    LOGD("FaceDetect MTCNN reset");
    return tDetectionUnInit;

}
