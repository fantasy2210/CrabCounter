#pragma once
#include "stdafx.h"
#ifdef _MANAGED
#else
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#endif


#define GetTGMTcamera TGMTcamera::GetInstance

class TGMTcamera
{
	static TGMTcamera* instance;
	cv::VideoCapture mCap;
	std::vector<cv::VideoCapture*> m_vcaps;
	bool m_loadConfigSuccess = false;
	std::vector<std::string> m_camSources;
	std::vector<cv::Rect> m_frameOriginSizes;
	std::vector<cv::Size> m_frameResizes;
	std::vector<cv::Mat> m_frames;
	std::vector<std::thread*> m_threads;
	std::atomic<bool> m_isRunning = false;
	std::mutex m_mutex;

#ifdef _MANAGED
#else
	std::thread m_threadGrab;
	std::thread m_threadUpdate;
#endif
	
	void CameraGrabbed();
	void CaptureFrame(int camID);
	bool IsValidCamera(int camID);
	bool IsValidCamera(std::string camLink);
	void Update();
public:
	static TGMTcamera* GetInstance()
	{
		if (!instance)
			instance = new TGMTcamera();
		return instance;
	}
	TGMTcamera();
	~TGMTcamera();

	//only for test camera
	void PlayCamera(int cameraID = 0, int delayMilisecond = 30);

	
	cv::Mat GetImageFromCamera(int cameraID = 0);

	//get images from loaded camera
	std::vector<cv::Mat> GetImages();

#ifdef _MANAGED
#else
	std::function<void(cv::Mat)> OnNewFrame;
	std::function<void(std::vector<cv::Mat>)> OnNewFrames;
	std::function<void()> OnStopped;
	std::function<void(int key)> OnKeyEvent;
#endif

	bool LoadConfig();

	void StartCamera(int cameraID = 0);
	void StartCamera(std::string cameraURL);
	void StartCameras(std::vector<std::string> camSources);

	//start with config value
	void Start();	
	void StopCamera();

	

	//record video from camera
	void RecordVideo(int cameraID, std::string videoFileOutputPath);

	//return number of camera success loaded
	int GetNumOfCamera();

	cv::Rect GetFrameSize(int camID);
	bool IsCameraRunning();
};

