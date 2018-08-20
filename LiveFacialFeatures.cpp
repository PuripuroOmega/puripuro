// FaceTracking.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LuxandFaceSDK.h"
#include <math.h>

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


void SavefacialFeatures(FSDK_Features facialFeatures)
{
	for (int i = 0; i < FSDK_FACIAL_FEATURE_COUNT; i++)
	{
		printf("%s: (%d, %d)\n", facialFeaturesName[i], facialFeatures[i].x, facialFeatures[i].y);
	}
}

void drawingLine(HDC dc, HPEN FeatureLinePen, HBRUSH FeatureLineBrush, FSDK_Features facialFeatures)
{
	SelectObject(dc, FeatureLinePen);
	SelectObject(dc, FeatureLineBrush);

	//左眉
	MoveToEx(dc, facialFeatures[FSDKP_LEFT_EYEBROW_INNER_CORNER].x, 16+facialFeatures[FSDKP_LEFT_EYEBROW_INNER_CORNER].y, NULL);
	LineTo(dc, facialFeatures[FSDKP_LEFT_EYEBROW_MIDDLE_RIGHT].x, 16+facialFeatures[FSDKP_LEFT_EYEBROW_MIDDLE_RIGHT].y);
	LineTo(dc, facialFeatures[FSDKP_LEFT_EYEBROW_MIDDLE].x, 16+facialFeatures[FSDKP_LEFT_EYEBROW_MIDDLE].y);
	LineTo(dc, facialFeatures[FSDKP_LEFT_EYEBROW_MIDDLE_LEFT].x, 16+facialFeatures[FSDKP_LEFT_EYEBROW_MIDDLE_LEFT].y);
	LineTo(dc, facialFeatures[FSDKP_LEFT_EYEBROW_OUTER_CORNER].x, 16+facialFeatures[FSDKP_LEFT_EYEBROW_OUTER_CORNER].y);

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

}

void Get_Angle(FSDK_Features facialFeatures){
	double rad[36] ;

	//左眉
	rad[0] = atan2(facialFeatures[18].y - facialFeatures[12].y, facialFeatures[18].x - facialFeatures[12].x);
	rad[1] = atan2(facialFeatures[16].y - facialFeatures[18].y, facialFeatures[16].x - facialFeatures[18].x);
	rad[2] = atan2(facialFeatures[19].y - facialFeatures[16].y, facialFeatures[19].x - facialFeatures[16].x);
	rad[3] = atan2(facialFeatures[13].y - facialFeatures[19].y, facialFeatures[13].x - facialFeatures[19].x);

	//右眉
	rad[4] = atan2(facialFeatures[20].y - facialFeatures[14].y, facialFeatures[20].x - facialFeatures[14].x);
	rad[5] = atan2(facialFeatures[17].y - facialFeatures[20].y, facialFeatures[17].x - facialFeatures[20].x);
	rad[6] = atan2(facialFeatures[21].y - facialFeatures[17].y, facialFeatures[21].x - facialFeatures[17].x);
	rad[7] = atan2(facialFeatures[15].y - facialFeatures[21].y, facialFeatures[15].x - facialFeatures[21].x);

	//左目
	rad[8] = atan2(facialFeatures[35].y - facialFeatures[23].y, facialFeatures[35].x - facialFeatures[23].x);
	rad[9] = atan2(facialFeatures[28].y - facialFeatures[35].y, facialFeatures[28].x - facialFeatures[35].x);
	rad[10] = atan2(facialFeatures[36].y - facialFeatures[28].y, facialFeatures[36].x - facialFeatures[28].x);
	rad[11] = atan2(facialFeatures[24].y - facialFeatures[36].y, facialFeatures[24].x - facialFeatures[36].x);
	rad[12] = atan2(facialFeatures[37].y - facialFeatures[23].y, facialFeatures[37].x - facialFeatures[23].x);
	rad[13] = atan2(facialFeatures[27].y - facialFeatures[37].y, facialFeatures[27].x - facialFeatures[37].x);
	rad[14] = atan2(facialFeatures[38].y - facialFeatures[27].y, facialFeatures[38].x - facialFeatures[27].x);
	rad[15] = atan2(facialFeatures[24].y - facialFeatures[38].y, facialFeatures[24].x - facialFeatures[38].x);

	//右目
	rad[16] = atan2(facialFeatures[39].y - facialFeatures[25].y, facialFeatures[39].x - facialFeatures[25].x);
	rad[17] = atan2(facialFeatures[32].y - facialFeatures[39].y, facialFeatures[32].x - facialFeatures[39].x);
	rad[18] = atan2(facialFeatures[40].y - facialFeatures[32].y, facialFeatures[40].x - facialFeatures[32].x);
	rad[19] = atan2(facialFeatures[26].y - facialFeatures[40].y, facialFeatures[26].x - facialFeatures[40].x);
	rad[20] = atan2(facialFeatures[41].y - facialFeatures[25].y, facialFeatures[41].x - facialFeatures[25].x);
	rad[21] = atan2(facialFeatures[31].y - facialFeatures[41].y, facialFeatures[31].x - facialFeatures[41].x);
	rad[22] = atan2(facialFeatures[42].y - facialFeatures[31].y, facialFeatures[42].x - facialFeatures[31].x);
	rad[23] = atan2(facialFeatures[26].y - facialFeatures[42].y, facialFeatures[26].x - facialFeatures[42].x);

	//左ほうれい線
	rad[24] = atan2(facialFeatures[50].y - facialFeatures[45].y, facialFeatures[50].x - facialFeatures[45].x);
	rad[25] = atan2(facialFeatures[52].y - facialFeatures[50].y, facialFeatures[52].x - facialFeatures[50].x);

	//右ほうれい線
	rad[26] = atan2(facialFeatures[51].y - facialFeatures[46].y, facialFeatures[51].x - facialFeatures[46].x);
	rad[27] = atan2(facialFeatures[53].y - facialFeatures[51].y, facialFeatures[53].x - facialFeatures[51].x);

	//口
	rad[28] = atan2(facialFeatures[56].y - facialFeatures[3].y, facialFeatures[56].x - facialFeatures[3].x);
	rad[29] = atan2(facialFeatures[54].y - facialFeatures[56].y, facialFeatures[54].x - facialFeatures[56].x);
	rad[30] = atan2(facialFeatures[57].y - facialFeatures[54].y, facialFeatures[57].x - facialFeatures[54].x);
	rad[31] = atan2(facialFeatures[4].y - facialFeatures[57].y, facialFeatures[4].x - facialFeatures[57].x);
	rad[32] = atan2(facialFeatures[58].y - facialFeatures[3].y, facialFeatures[58].x - facialFeatures[3].x);
	rad[33] = atan2(facialFeatures[55].y - facialFeatures[58].y, facialFeatures[55].x - facialFeatures[58].x);
	rad[34] = atan2(facialFeatures[59].y - facialFeatures[55].y, facialFeatures[59].x - facialFeatures[55].x);
	rad[35] = atan2(facialFeatures[4].y - facialFeatures[59].y, facialFeatures[4].x - facialFeatures[59].x);

	for (int i = 0; i < 36; i++) {
		rad[i]= rad[i]  * 180.0/(3.14159265358979323);
		printf("%d %lf \n",i, rad[i]);
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

	HPEN FeatureLinePen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HBRUSH FeatureLineBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	HPEN FeatureCirclesPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	LOGBRUSH brush;
	brush.lbColor = RGB(0, 0, 255);
	brush.lbStyle = BS_SOLID;
	HBRUSH FeatureCirclesBrush = CreateBrushIndirect(&brush);

	SendMessage(hwnd, LB_ADDSTRING, 0, (LPARAM)(L"Press Esc to exit ..."));

	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		HImage imageHandle;
		FSDK_Features facialFeatures;
		if (FSDK_GrabFrame(cameraHandle, &imageHandle) == FSDKE_OK) { // grab the current frame from the camera
			long long IDs[256];
			long long faceCount = 0;
			FSDK_FeedFrame(tracker, 0, imageHandle, &faceCount, IDs, sizeof(IDs));

			HBITMAP hbitmapHandle; // to store the HBITMAP handle
			FSDK_SaveImageToHBitmap(imageHandle, &hbitmapHandle);

			DrawState(dc, NULL, NULL, (LPARAM)hbitmapHandle, NULL, 0, 16, width, height, DST_BITMAP | DSS_NORMAL);

			for (int i = 0; i < faceCount; i++) {
				TFacePosition facePosition;

				FSDK_GetTrackerFacePosition(tracker, 0, IDs[i], &facePosition);
				FSDK_GetTrackerFacialFeatures(tracker, 0, IDs[i], &facialFeatures);

				int x1 = facePosition.xc - (int)(facePosition.w*0.6);
				int y1 = facePosition.yc - (int)(facePosition.w*0.5);
				int x2 = facePosition.xc + (int)(facePosition.w*0.6);
				int y2 = facePosition.yc + (int)(facePosition.w*0.7);

				SelectObject(dc, FaceRectanglePen);
				SelectObject(dc, FaceRectangleBrush);
				Rectangle(dc, x1, 16 + y1, x2, 16 + y2);

				drawingLine(dc, FeatureLinePen, FeatureLineBrush, facialFeatures);

				SelectObject(dc, FeatureCirclesPen);
				SelectObject(dc, FeatureCirclesBrush);
				for (int i = 0; i < FSDK_FACIAL_FEATURE_COUNT; i++)
					Ellipse(dc, facialFeatures[i].x - 2, 16 + facialFeatures[i].y - 2, facialFeatures[i].x + 2, 16 + facialFeatures[i].y + 2);

			}

			DeleteObject(hbitmapHandle); // delete the HBITMAP object
			FSDK_FreeImage(imageHandle);// delete the FSDK image handle
		}


		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_KEYDOWN && msg.wParam == VK_RETURN)
			{
				//SavefacialFeatures(facialFeatures);
				Get_Angle(facialFeatures);
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
