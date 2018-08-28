// FaceTracking.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LuxandFaceSDK.h"
#include <vector>

char facialFeaturesName[100][FSDK_FACIAL_FEATURE_COUNT] =
{
	"FSDKP_LEFT_EYE",
	"FSDKP_RIGHT_EYE",
	"FSDKP_NOSE_TIP",
	"FSDKP_MOUTH_RIGHT_CORNER",
	"FSDKP_MOUTH_LEFT_CORNER",
	"FSDKP_FACE_CONTOUR2",
	"FSDKP_FACE_CONTOUR12",
	"FSDKP_FACE_CONTOUR1",
	"FSDKP_FACE_CONTOUR13",
	"FSDKP_CHIN_LEFT",
	"FSDKP_CHIN_RIGHT",
	"FSDKP_CHIN_BOTTOM",//11
	"FSDKP_LEFT_EYEBROW_OUTER_CORNER",
	"FSDKP_LEFT_EYEBROW_INNER_CORNER",
	"FSDKP_RIGHT_EYEBROW_INNER_CORNER",
	"FSDKP_RIGHT_EYEBROW_OUTER_CORNER",
	"FSDKP_LEFT_EYEBROW_MIDDLE",
	"FSDKP_RIGHT_EYEBROW_MIDDLE",
	"FSDKP_LEFT_EYEBROW_MIDDLE_LEFT",
	"FSDKP_LEFT_EYEBROW_MIDDLE_RIGHT",
	"FSDKP_RIGHT_EYEBROW_MIDDLE_LEFT",
	"FSDKP_RIGHT_EYEBROW_MIDDLE_RIGHT",
	"FSDKP_NOSE_BRIDGE",
	"FSDKP_LEFT_EYE_OUTER_CORNER",
	"FSDKP_LEFT_EYE_INNER_CORNER",
	"FSDKP_RIGHT_EYE_INNER_CORNER",
	"FSDKP_RIGHT_EYE_OUTER_CORNER",
	"FSDKP_LEFT_EYE_LOWER_LINE2",
	"FSDKP_LEFT_EYE_UPPER_LINE2",
	"FSDKP_LEFT_EYE_LEFT_IRIS_CORNER",
	"FSDKP_LEFT_EYE_RIGHT_IRIS_CORNE",
	"FSDKP_RIGHT_EYE_LOWER_LINE2",//31
	"FSDKP_RIGHT_EYE_UPPER_LINE2",
	"FSDKP_RIGHT_EYE_LEFT_IRIS_CORNER",
	"FSDKP_RIGHT_EYE_RIGHT_IRIS_CORNER",
	"FSDKP_LEFT_EYE_UPPER_LINE1",
	"FSDKP_LEFT_EYE_UPPER_LINE3",
	"FSDKP_LEFT_EYE_LOWER_LINE3",
	"FSDKP_LEFT_EYE_LOWER_LINE1",
	"FSDKP_RIGHT_EYE_UPPER_LINE3",
	"FSDKP_RIGHT_EYE_UPPER_LINE1",
	"FSDKP_RIGHT_EYE_LOWER_LINE1",
	"FSDKP_RIGHT_EYE_LOWER_LINE3",
	"FSDKP_NOSE_LEFT_WING",
	"FSDKP_NOSE_RIGHT_WING",
	"FSDKP_NOSE_LEFT_WING_OUTER",
	"FSDKP_NOSE_RIGHT_WING_OUTER",
	"FSDKP_NOSE_LEFT_WING_LOWER",
	"FSDKP_NOSE_RIGHT_WING_LOWER",
	"FSDKP_NOSE_BOTTOM",
	"FSDKP_NASOLABIAL_FOLD_LEFT_UPPER",
	"FSDKP_NASOLABIAL_FOLD_RIGHT_UPPER",
	"FSDKP_NASOLABIAL_FOLD_LEFT_LOWER",
	"FSDKP_NASOLABIAL_FOLD_RIGHT_LOWER",
	"FSDKP_MOUTH_TOP",
	"FSDKP_MOUTH_BOTTOM",
	"FSDKP_MOUTH_LEFT_TOP",
	"FSDKP_MOUTH_RIGHT_TOP",
	"FSDKP_MOUTH_LEFT_BOTTOM",
	"FSDKP_MOUTH_RIGHT_BOTTOM",
	"FSDKP_MOUTH_LEFT_TOP_INNER",
	"FSDKP_MOUTH_TOP_INNER",
	"FSDKP_MOUTH_RIGHT_TOP_INNER",
	"FSDKP_MOUTH_LEFT_BOTTOM_INNER",
	"FSDKP_MOUTH_BOTTOM_INNER",
	"FSDKP_MOUTH_RIGHT_BOTTOM_INNER",
	"FSDKP_FACE_CONTOUR14",
	"FSDKP_FACE_CONTOUR15",
	"FSDKP_FACE_CONTOUR16",
	"FSDKP_FACE_CONTOUR17"
};

int num_array[58] = { 0,13,19,16,18,12,//左眉
					  0,14,20,17,21,15,//右眉
					  0,24,36,28,35,23,37,27,38,24,//左目
					  0,25,39,32,40,26,42,31,41,25,//右目
					  0,45,50,52,//左ほうれい線
					  0,46,51,53,//右ほうれい線
					  0,3,56,54,57,4,62,61,60,3,63,64,65,4,59,55,58,3//口
					};


void SavefacialFeatures(FSDK_Features facialFeatures)
{
	for (int i = 0; i < FSDK_FACIAL_FEATURE_COUNT; i++)
	{
		printf("%s: (%d, %d)\n", facialFeaturesName[i], facialFeatures[i].x, facialFeatures[i].y);
	}
}

bool find_angle_each_parts(int i, int j, FSDK_Features facialFeatures, FSDK_Features model_facialFeatures) {
	double angle = atan2(facialFeatures[i].y - facialFeatures[j].y, facialFeatures[i].x - facialFeatures[j].x) * 180.0 / (3.14159265358979323);
	double model_angle = atan2(model_facialFeatures[i].y - model_facialFeatures[j].y, model_facialFeatures[i].x - model_facialFeatures[j].x) * 180.0 / (3.14159265358979323);

	if (abs(model_angle - angle) <= 15) { return true; }
	else return false;
}

void drawingLine(HDC dc, HPEN FeatureLinePen, HBRUSH FeatureLineBrush, HPEN FeatureLinePen_gap, HBRUSH FeatureLineBrush_gap, FSDK_Features facialFeatures, FSDK_Features model_facialFeatures)
{

	for (int i = 0; i < 58; i++) {
		if (num_array[i] == 0) {
				i++;
				MoveToEx(dc, model_facialFeatures[num_array[i]].x, 16 + model_facialFeatures[num_array[i]].y, NULL);
		}
		else {
			if (find_angle_each_parts(num_array[i], num_array[i - 1], facialFeatures, model_facialFeatures)) {
				SelectObject(dc, FeatureLinePen);
				SelectObject(dc, FeatureLineBrush);
				LineTo(dc, model_facialFeatures[num_array[i]].x, 16 + model_facialFeatures[num_array[i]].y);
			}
			else {
				SelectObject(dc, FeatureLinePen_gap);
				SelectObject(dc, FeatureLineBrush_gap);
				LineTo(dc, model_facialFeatures[num_array[i]].x, 16 + model_facialFeatures[num_array[i]].y);
			}
		}

	}
	/*
	//左眉
	MoveToEx(dc, facialFeatures[13].x, 16+facialFeatures[13].y, NULL);
	LineTo(dc, facialFeatures[19].x, 16+facialFeatures[19].y);
	LineTo(dc, facialFeatures[16].x, 16+facialFeatures[16].y);
	LineTo(dc, facialFeatures[18].x, 16+facialFeatures[18].y);
	LineTo(dc, facialFeatures[12].x, 16+facialFeatures[12].y);

	//右眉
	MoveToEx(dc, facialFeatures[14].x, 16 + facialFeatures[14].y, NULL);
	LineTo(dc, facialFeatures[20].x, 16 + facialFeatures[20].y);
	LineTo(dc, facialFeatures[17].x, 16 + facialFeatures[17].y);
	LineTo(dc, facialFeatures[21].x, 16 + facialFeatures[21].y);
	LineTo(dc, facialFeatures[15].x, 16 + facialFeatures[15].y);

	//左目
	MoveToEx(dc, facialFeatures[24].x, 16 + facialFeatures[24].y, NULL);
	LineTo(dc, facialFeatures[36].x, 16 + facialFeatures[36].y);
	LineTo(dc, facialFeatures[28].x, 16 + facialFeatures[28].y);
	LineTo(dc, facialFeatures[35].x, 16 + facialFeatures[35].y);
	LineTo(dc, facialFeatures[23].x, 16 + facialFeatures[23].y);
	LineTo(dc, facialFeatures[37].x, 16 + facialFeatures[37].y);
	LineTo(dc, facialFeatures[27].x, 16 + facialFeatures[27].y);
	LineTo(dc, facialFeatures[38].x, 16 + facialFeatures[38].y);
	LineTo(dc, facialFeatures[24].x, 16 + facialFeatures[24].y);

	//右目
	MoveToEx(dc, facialFeatures[25].x, 16 + facialFeatures[25].y, NULL);
	LineTo(dc, facialFeatures[39].x, 16 + facialFeatures[39].y);
	LineTo(dc, facialFeatures[32].x, 16 + facialFeatures[32].y);
	LineTo(dc, facialFeatures[40].x, 16 + facialFeatures[40].y);
	LineTo(dc, facialFeatures[26].x, 16 + facialFeatures[26].y);
	LineTo(dc, facialFeatures[42].x, 16 + facialFeatures[42].y);
	LineTo(dc, facialFeatures[31].x, 16 + facialFeatures[31].y);
	LineTo(dc, facialFeatures[41].x, 16 + facialFeatures[41].y);
	LineTo(dc, facialFeatures[25].x, 16 + facialFeatures[25].y);

	//左ほうれい線
	MoveToEx(dc, facialFeatures[45].x, 16 + facialFeatures[45].y, NULL);
	LineTo(dc, facialFeatures[50].x, 16 + facialFeatures[50].y);
	LineTo(dc, facialFeatures[52].x, 16 + facialFeatures[52].y);

	//右ほうれい線
	MoveToEx(dc, facialFeatures[46].x, 16 + facialFeatures[46].y, NULL);
	LineTo(dc, facialFeatures[51].x, 16 + facialFeatures[51].y);
	LineTo(dc, facialFeatures[53].x, 16 + facialFeatures[53].y);

	//口
	MoveToEx(dc, facialFeatures[3].x, 16 + facialFeatures[3].y, NULL);
	LineTo(dc, facialFeatures[56].x, 16 + facialFeatures[56].y);
	LineTo(dc, facialFeatures[54].x, 16 + facialFeatures[54].y);
	LineTo(dc, facialFeatures[57].x, 16 + facialFeatures[57].y);
	LineTo(dc, facialFeatures[4].x, 16 + facialFeatures[4].y);
	LineTo(dc, facialFeatures[62].x, 16 + facialFeatures[62].y);
	LineTo(dc, facialFeatures[61].x, 16 + facialFeatures[61].y);
	LineTo(dc, facialFeatures[60].x, 16 + facialFeatures[60].y);
	LineTo(dc, facialFeatures[3].x, 16 + facialFeatures[3].y);
	LineTo(dc, facialFeatures[63].x, 16 + facialFeatures[63].y);
	LineTo(dc, facialFeatures[64].x, 16 + facialFeatures[64].y);
	LineTo(dc, facialFeatures[65].x, 16 + facialFeatures[65].y);
	LineTo(dc, facialFeatures[4].x, 16 + facialFeatures[4].y);
	LineTo(dc, facialFeatures[59].x, 16 + facialFeatures[59].y);
	LineTo(dc, facialFeatures[55].x, 16 + facialFeatures[55].y);
	LineTo(dc, facialFeatures[58].x, 16 + facialFeatures[58].y);
	LineTo(dc, facialFeatures[3].x, 16 + facialFeatures[3].y);
	*/

}


std::vector<double> Get_Angle(FSDK_Features facialFeatures) {
	std::vector<double> rad;
	//左眉
	rad.push_back(atan2(facialFeatures[18].y - facialFeatures[12].y, facialFeatures[18].x - facialFeatures[12].x));
	rad.push_back(atan2(facialFeatures[16].y - facialFeatures[18].y, facialFeatures[16].x - facialFeatures[18].x));
	rad.push_back(atan2(facialFeatures[19].y - facialFeatures[16].y, facialFeatures[19].x - facialFeatures[16].x));
	rad.push_back(atan2(facialFeatures[13].y - facialFeatures[19].y, facialFeatures[13].x - facialFeatures[19].x));

	//右眉
	rad.push_back(atan2(facialFeatures[20].y - facialFeatures[14].y, facialFeatures[20].x - facialFeatures[14].x));
	rad.push_back(atan2(facialFeatures[17].y - facialFeatures[20].y, facialFeatures[17].x - facialFeatures[20].x));
	rad.push_back(atan2(facialFeatures[21].y - facialFeatures[17].y, facialFeatures[21].x - facialFeatures[17].x));
	rad.push_back(atan2(facialFeatures[15].y - facialFeatures[21].y, facialFeatures[15].x - facialFeatures[21].x));

	//左目
	rad.push_back(atan2(facialFeatures[35].y - facialFeatures[23].y, facialFeatures[35].x - facialFeatures[23].x));
	rad.push_back(atan2(facialFeatures[28].y - facialFeatures[35].y, facialFeatures[28].x - facialFeatures[35].x));
	rad.push_back(atan2(facialFeatures[36].y - facialFeatures[28].y, facialFeatures[36].x - facialFeatures[28].x));
	rad.push_back(atan2(facialFeatures[24].y - facialFeatures[36].y, facialFeatures[24].x - facialFeatures[36].x));
	rad.push_back(atan2(facialFeatures[37].y - facialFeatures[23].y, facialFeatures[37].x - facialFeatures[23].x));
	rad.push_back(atan2(facialFeatures[27].y - facialFeatures[37].y, facialFeatures[27].x - facialFeatures[37].x));
	rad.push_back(atan2(facialFeatures[38].y - facialFeatures[27].y, facialFeatures[38].x - facialFeatures[27].x));
	rad.push_back(atan2(facialFeatures[24].y - facialFeatures[38].y, facialFeatures[24].x - facialFeatures[38].x));

	//右目
	rad.push_back(atan2(facialFeatures[39].y - facialFeatures[25].y, facialFeatures[39].x - facialFeatures[25].x));
	rad.push_back(atan2(facialFeatures[32].y - facialFeatures[39].y, facialFeatures[32].x - facialFeatures[39].x));
	rad.push_back(atan2(facialFeatures[40].y - facialFeatures[32].y, facialFeatures[40].x - facialFeatures[32].x));
	rad.push_back(atan2(facialFeatures[26].y - facialFeatures[40].y, facialFeatures[26].x - facialFeatures[40].x));
	rad.push_back(atan2(facialFeatures[41].y - facialFeatures[25].y, facialFeatures[41].x - facialFeatures[25].x));
	rad.push_back(atan2(facialFeatures[31].y - facialFeatures[41].y, facialFeatures[31].x - facialFeatures[41].x));
	rad.push_back(atan2(facialFeatures[42].y - facialFeatures[31].y, facialFeatures[42].x - facialFeatures[31].x));
	rad.push_back(atan2(facialFeatures[26].y - facialFeatures[42].y, facialFeatures[26].x - facialFeatures[42].x));

	//左ほうれい線
	rad.push_back(atan2(facialFeatures[50].y - facialFeatures[45].y, facialFeatures[50].x - facialFeatures[45].x));
	rad.push_back(atan2(facialFeatures[52].y - facialFeatures[50].y, facialFeatures[52].x - facialFeatures[50].x));

	//右ほうれい線
	rad.push_back(atan2(facialFeatures[51].y - facialFeatures[46].y, facialFeatures[51].x - facialFeatures[46].x));
	rad.push_back(atan2(facialFeatures[53].y - facialFeatures[51].y, facialFeatures[53].x - facialFeatures[51].x));

	//口
	rad.push_back(atan2(facialFeatures[56].y - facialFeatures[3].y, facialFeatures[56].x - facialFeatures[3].x));
	rad.push_back(atan2(facialFeatures[54].y - facialFeatures[56].y, facialFeatures[54].x - facialFeatures[56].x));
	rad.push_back(atan2(facialFeatures[57].y - facialFeatures[54].y, facialFeatures[57].x - facialFeatures[54].x));
	rad.push_back(atan2(facialFeatures[4].y - facialFeatures[57].y, facialFeatures[4].x - facialFeatures[57].x));
	rad.push_back(atan2(facialFeatures[58].y - facialFeatures[3].y, facialFeatures[58].x - facialFeatures[3].x));
	rad.push_back(atan2(facialFeatures[55].y - facialFeatures[58].y, facialFeatures[55].x - facialFeatures[58].x));
	rad.push_back(atan2(facialFeatures[59].y - facialFeatures[55].y, facialFeatures[59].x - facialFeatures[55].x));
	rad.push_back(atan2(facialFeatures[4].y - facialFeatures[59].y, facialFeatures[4].x - facialFeatures[59].x));

	for (int i = 0; i < rad.size(); i++) {
		rad[i] = rad[i] * 180.0 / (3.14159265358979323);
		printf("%lf \n", rad[i]);
	}
	printf("-----------------------------------\n");

	return rad;
}

void show_AngleDifference(FSDK_Features facialFeatures, FSDK_Features model_facialFeatures)
{
	std::vector<double> rad = Get_Angle(facialFeatures);
	std::vector<double> model_rad = Get_Angle(model_facialFeatures);

	for (int i = 0; i < rad.size(); i++) {
		printf("%lf \n", model_rad[i] - rad[i]);
	}
	printf("-----------------------------------\n");
}

bool make_model(HWND hwnd, FSDK_Features &model_facialFeatures)
{
	TFacePosition facePosition;
	HImage ResizedImageHandle;
	FSDK_CreateEmptyImage(&ResizedImageHandle);
	bool ImageOpened = false;
	int FaceDetected = -1;
	int width, height;

	RECT ClientRect;
	GetClientRect(hwnd, &ClientRect);

	HImage imageHandle;
	OPENFILENAMEA oFile;
	char szPath[MAX_PATH];
	char szDir[MAX_PATH];
	ZeroMemory(&oFile, sizeof(oFile));
	GetCurrentDirectoryA(sizeof(szDir), szDir);
	lstrcpyA(szPath, "");
	oFile.lStructSize = sizeof(oFile);
	oFile.hwndOwner = hwnd;
	oFile.hInstance = NULL;
	oFile.lpstrFilter = "Images(*.jpg;*.jpeg;*.jpe;*.jfif;*.bmp;*.png)\0*.jpg;*.jpeg;*.jpe;*.jfif;*.bmp;*.png\0\0";
	oFile.lpstrFile = szPath;
	oFile.nMaxFile = sizeof(szPath);
	oFile.lpstrInitialDir = szDir;
	oFile.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	oFile.lpstrDefExt = NULL;
	if (GetOpenFileNameA(&oFile) && FSDKE_OK == FSDK_LoadImageFromFile(&imageHandle, oFile.lpstrFile))
	{
		FaceDetected = FSDK_DetectFace(imageHandle, &facePosition);
		if (FaceDetected == FSDKE_OK)
			FSDK_DetectFacialFeaturesInRegion(imageHandle, &facePosition, &model_facialFeatures);

		FSDK_GetImageWidth(imageHandle, &width);
		FSDK_GetImageHeight(imageHandle, &height);
		double resizeCoefficient = min(ClientRect.right / (double)width, (ClientRect.bottom - 16) / (double)height);

		FSDK_FreeImage(ResizedImageHandle);
		FSDK_CreateEmptyImage(&ResizedImageHandle);
		FSDK_ResizeImage(imageHandle, resizeCoefficient, ResizedImageHandle);

		FSDK_GetImageWidth(ResizedImageHandle, &width);
		FSDK_GetImageHeight(ResizedImageHandle, &height);

		FSDK_FreeImage(imageHandle);// delete the FSDK image handle

		if (FaceDetected == FSDKE_OK)
		{
			facePosition.xc = (int)(resizeCoefficient * facePosition.xc);
			facePosition.yc = (int)(resizeCoefficient * facePosition.yc);
			facePosition.w = (int)(resizeCoefficient * facePosition.w);
			for (int i = 0; i < FSDK_FACIAL_FEATURE_COUNT; i++)
			{
				model_facialFeatures[i].x = (int)(resizeCoefficient * model_facialFeatures[i].x);
				model_facialFeatures[i].y = (int)(resizeCoefficient * model_facialFeatures[i].y);
			}
		}

		ImageOpened = true;
		InvalidateRect(hwnd, NULL, TRUE);

		return true;
	}

	return false;
}

void ReArrangement(FSDK_Features facialFeatures, FSDK_Features model_facialFeatures, FSDK_Features &mag_facialFeatures) {
	double magnification;
	magnification = (double)(facialFeatures[67].x - facialFeatures[66].x) / (model_facialFeatures[67].x - model_facialFeatures[66].x);
	int gap_x[FSDK_FACIAL_FEATURE_COUNT],gap_y[FSDK_FACIAL_FEATURE_COUNT];
	for (int i = 0; i < FSDK_FACIAL_FEATURE_COUNT; i++)
	{
		gap_x[i] = (model_facialFeatures[i].x - model_facialFeatures[2].x)*magnification;
		mag_facialFeatures[i].x = facialFeatures[2].x + gap_x[i];
		gap_y[i] = (model_facialFeatures[i].y - model_facialFeatures[2].y)*magnification;
		mag_facialFeatures[i].y = facialFeatures[2].y + gap_y[i];
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	if (FSDKE_OK != FSDK_ActivateLibrary("tmzQl5fZlwQDYjMHyIW4GCUbwj7fRdtsu5q+LN6JhXUi40jlPyyUGPEEtULkMnYNXfCAtoPGorAkNKQHk0cPZXfNj5QGPcsRy3gHLfU24HTlNYUbjceF7iJjk0O+p1S1Yv/jd0Jjoh+Z8iPyt+wPzYCyVWH30ZggBF6O5bjl+UY=")) {
		MessageBox(0, L"Please run the License Key Wizard (Start - Luxand - FaceSDK - License Key Wizard)\n", L"Error activating FaceSDK", MB_ICONERROR | MB_OK);
		exit(-1);
	}
	FSDK_Initialize((char*)"");
	FSDK_InitializeCapturing();

	int CameraCount;
	wchar_t ** CameraList;
	if (0 == FSDK_GetCameraList(&CameraList, &CameraCount))
		for (int i = 0; i < CameraCount; i++)
			wprintf(L"camera: %s\n", CameraList[i]);

	if (0 == CameraCount) {
		MessageBox(0, L"Please attach a camera", L"Error", MB_ICONERROR | MB_OK);
		return -1;
	}

	int CameraIdx = 0; // choose the first camera
	int VideoFormatCount = 0;
	FSDK_VideoFormatInfo * VideoFormatList = 0;
	FSDK_GetVideoFormatList(CameraList[CameraIdx], &VideoFormatList, &VideoFormatCount);
	for (int i = 0; i < VideoFormatCount; i++)
		printf("format %d: %dx%d, %d bpp\n", i, VideoFormatList[i].Width, VideoFormatList[i].Height, VideoFormatList[i].BPP);

	int VideoFormat = 0; // choose a video format
	int width = VideoFormatList[VideoFormat].Width;
	int height = VideoFormatList[VideoFormat].Height;
	int bitsPerPixel = VideoFormatList[VideoFormat].BPP;
	FSDK_SetVideoFormat(CameraList[CameraIdx], VideoFormatList[VideoFormat]);

	printf("Trying to open the first camera...\n");
	int cameraHandle = 0;
	if (FSDKE_OK != FSDK_OpenVideoCamera(CameraList[CameraIdx], &cameraHandle)) {
		MessageBox(0, L"Error opening the first camera", L"Error", MB_ICONERROR | MB_OK);
		return -2;
	}

	// creating a Tracker
	HTracker tracker = 0;
	FSDK_CreateTracker(&tracker);

	int err = 0; // set realtime face detection parameters
	FSDK_SetTrackerMultipleParameters(tracker, "RecognizeFaces=false; DetectFacialFeatures=true; HandleArbitraryRotations=false; DetermineFaceRotationAngle=false; InternalResizeWidth=100; FaceDetectionThreshold=5;", &err);

	// creating a window
	HWND hwnd = CreateWindowEx(WS_EX_TOOLWINDOW, L"LISTBOX", L"LiveFacialFeatures", 0, 0, 0, 0, 0, 0, 0, 0, 0);
	HDC dc = GetDC(hwnd);
	SetWindowPos(hwnd, 0, 0, 0, 6 + width, 6 + 32 + (height), SWP_NOZORDER | SWP_NOMOVE);
	ShowWindow(hwnd, SW_SHOW);

	HPEN FaceRectanglePen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HBRUSH FaceRectangleBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	HPEN FeatureLinePen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HBRUSH FeatureLineBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	HPEN FeatureLinePen_model = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	HBRUSH FeatureLineBrush_model = (HBRUSH)GetStockObject(NULL_BRUSH);

	HPEN FeatureCirclesPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	LOGBRUSH brush;
	brush.lbColor = RGB(255, 255, 255);
	brush.lbStyle = BS_SOLID;
	HBRUSH FeatureCirclesBrush = CreateBrushIndirect(&brush);

	SendMessage(hwnd, LB_ADDSTRING, 0, (LPARAM)(L"Press Esc to exit ..."));

	MSG msg = { 0 };
	bool model_flag = false;
	while (msg.message != WM_QUIT) {
		HImage imageHandle;
		HImage backupHandle;
		FSDK_CreateEmptyImage(&backupHandle);
		FSDK_Features facialFeatures;
		FSDK_Features model_facialFeatures;
		FSDK_Features mag_facialFeatures;//お手本の倍率変更版
		TFacePosition facePosition;
		if (FSDK_GrabFrame(cameraHandle, &imageHandle) == FSDKE_OK && FSDK_MirrorImage(imageHandle, TRUE) == FSDKE_OK) { // grab the current frame from the camera
			long long IDs[256];
			long long faceCount = 0;
			FSDK_FeedFrame(tracker, 0, imageHandle, &faceCount, IDs, sizeof(IDs));

			HBITMAP hbitmapHandle; // to store the HBITMAP handle
			FSDK_SaveImageToHBitmap(imageHandle, &hbitmapHandle);

			DrawState(dc, NULL, NULL, (LPARAM)hbitmapHandle, NULL, 0, 16, width, height, DST_BITMAP | DSS_NORMAL);

			for (int i = 0; i < faceCount; i++) {

				FSDK_GetTrackerFacePosition(tracker, 0, IDs[i], &facePosition);
				FSDK_GetTrackerFacialFeatures(tracker, 0, IDs[i], &facialFeatures);

				int x1 = facePosition.xc - (int)(facePosition.w*0.6);
				int y1 = facePosition.yc - (int)(facePosition.w*0.5);
				int x2 = facePosition.xc + (int)(facePosition.w*0.6);
				int y2 = facePosition.yc + (int)(facePosition.w*0.7);

				SelectObject(dc, FaceRectanglePen);
				SelectObject(dc, FaceRectangleBrush);
				Rectangle(dc, x1, 16 + y1, x2, 16 + y2);

				//リアルタイムの線と点
				//drawingLine(dc, FeatureLinePen, FeatureLineBrush, facialFeatures);
				//SelectObject(dc, FeatureCirclesPen);
				//SelectObject(dc, FeatureCirclesBrush);
				//for (int i = 0; i < FSDK_FACIAL_FEATURE_COUNT; i++)
					//Ellipse(dc, model_facialFeatures[i].x - 2, 16 + model_facialFeatures[i].y - 2, model_facialFeatures[i].x + 2, 16 + model_facialFeatures[i].y + 2);


				if (model_flag) {
					ReArrangement(facialFeatures, model_facialFeatures, mag_facialFeatures);
					drawingLine(dc, FeatureLinePen, FeatureLineBrush, FeatureLinePen_model, FeatureLineBrush_model, facialFeatures, mag_facialFeatures);
					SelectObject(dc, FeatureCirclesPen);
					SelectObject(dc, FeatureCirclesBrush);
					for (int i = 0; i < FSDK_FACIAL_FEATURE_COUNT; i++)
						Ellipse(dc, mag_facialFeatures[i].x - 2, 16 + mag_facialFeatures[i].y - 2, mag_facialFeatures[i].x + 2, 16 + mag_facialFeatures[i].y + 2);
				}


			}
			FSDK_CopyImage(imageHandle, backupHandle);

			DeleteObject(hbitmapHandle); // delete the HBITMAP object
			FSDK_FreeImage(imageHandle);// delete the FSDK image handle
		}


		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_KEYDOWN && msg.wParam == VK_RETURN)
			{
				SavefacialFeatures(facialFeatures);
				FSDK_SaveImageToFile(backupHandle, "capture.jpg");
			}

			else if (msg.message == WM_KEYDOWN && msg.wParam == VK_SPACE)
			{
				Get_Angle(facialFeatures);
				FSDK_SaveImageToFile(backupHandle, "capture.jpg");
			}

			else if (msg.message == WM_KEYDOWN && msg.wParam == VK_SHIFT)
			{
				model_flag = false;
				if (make_model(hwnd, model_facialFeatures)) { model_flag = true; }
			}
			else if (msg.message == WM_KEYDOWN && msg.wParam == VK_CONTROL)
			{
				if (model_flag) {
					show_AngleDifference(facialFeatures, model_facialFeatures);
					ReArrangement(facialFeatures, model_facialFeatures, mag_facialFeatures);
					FSDK_SaveImageToFile(backupHandle, "capture.jpg");
				}
			}

			else if (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE)
				break;


		}
	}

	ReleaseDC(hwnd, dc);
	FSDK_FreeTracker(tracker);

	if (FSDKE_OK != FSDK_CloseVideoCamera(cameraHandle)) {
		MessageBox(0, L"Error closing camera", L"Error", MB_ICONERROR | MB_OK);
		return -5;
	}
	FSDK_FreeVideoFormatList(VideoFormatList);
	FSDK_FreeCameraList(CameraList, CameraCount);

	FSDK_FinalizeCapturing();
	FSDK_Finalize();
	return 0;
}
