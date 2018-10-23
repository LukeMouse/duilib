#ifndef _THID_FACE_DETECT_MTCNN_H_
#define _THID_FACE_DETECT_MTCNN_H_


//typedef struct THIDFaceRect;
//typedef struct THIDPointF
//struct THIDFace;

#ifndef _THIDFACERECT
#define _THIDFACERECT
typedef struct THIDFaceRect
{
	int left;			// ������ԭʼͼ���еľ���λ��
	int top;
	int right;
	int bottom;
	float confidence;	// ��������������Ŷȣ�ȡֵ��Χ[0��100]
}THIDFaceRect;
#endif	//	_THIDFACERECT



#ifndef _THIDPOINTF
#define _THIDPOINTF
typedef struct THIDPointF		//������������Ϣ
{
	float x;					//��������ԭʼͼ���е�x����
	float y;					//��������ԭʼͼ���е�y����
}THIDPointF;
#endif	//	_THIDPOINTF




#ifndef _THIDFACE_
#define _THIDFACE_
typedef struct THIDFace
{
	THIDFaceRect  face_rect;
	int           feat_count; //�ܹ�������������������Ϊ5, 68, 88, 168�ȵ�
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