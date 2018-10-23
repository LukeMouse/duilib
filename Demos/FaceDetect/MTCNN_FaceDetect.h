#ifndef _THID_FACE_DETECT_MTCNN_H_
#define _THID_FACE_DETECT_MTCNN_H_


//typedef struct THIDFaceRect;
//typedef struct THIDPointF
//struct THIDFace;

#ifndef _THIDFACERECT
#define _THIDFACERECT
typedef struct THIDFaceRect
{
	int left;			// 人脸在原始图像中的矩形位置
	int top;
	int right;
	int bottom;
	float confidence;	// 人脸检测结果的置信度，取值范围[0，100]
}THIDFaceRect;
#endif	//	_THIDFACERECT



#ifndef _THIDPOINTF
#define _THIDPOINTF
typedef struct THIDPointF		//描述特征点信息
{
	float x;					//特征点在原始图像中的x坐标
	float y;					//特征点在原始图像中的y坐标
}THIDPointF;
#endif	//	_THIDPOINTF




#ifndef _THIDFACE_
#define _THIDFACE_
typedef struct THIDFace
{
	THIDFaceRect  face_rect;
	int           feat_count; //总共的特征点数量，可能为5, 68, 88, 168等等
	THIDPointF    feat_point[168];

}THIDFace;
#endif //_THIDFACE_




//extern "C"{
	bool MTCNN_FaceDetectionModelInit(const char* faceDetectionModelPath);
	int  MTCNN_FaceDetect(const unsigned char *pbyRGbImage, const unsigned char *pbyGrayImage, int nImgWidth,
		int nImgHeight, int nMinFaceSize, int nMaxFaceSize, THIDFace *pFace, int *facenum);

	bool MTCNN_FaceDetectionModelUnInit();
//}




#endif //_THID_FACE_DETECT_MTCNN_H_