#include "OpenCV/CamSelectCore.h"

using namespace OpenCV;

OpenCV::CamSelectCore * OpenCV::CamSelectCore::mCamSelectCore;

OpenCV::CamSelectCore::CamSelectCore( QApplication* app)
{
	mCamSelectCore = this;
	this->app=app;
	int max=this->countCameras();
	if (max>1) max--;
	for (int i=0;i<max;i++){
		camlist.push_back(new OpenCV::CapVideo(i,0,0));
	}
}


OpenCV::CapVideo *OpenCV::CamSelectCore::selectCamera()
{
	// Vytvorenie stringu pre vypis dat o kamere
	QString data;
	for(int i=0; i < camlist.size(); i++){
		data.append(QString::number(camlist[i]->getDeviceId()));
		data.append(",");
		if (camlist[i]->isOpened()){
			data.append("yes");data.append(",");
			data.append(QString::number((int)camlist[i]->getWidth()));
			data.append(",");
			data.append(QString::number((int)camlist[i]->getHeight()));
		} else{
			data.append("no");data.append(",");
			data.append("0");
			data.append(",");
			data.append("0");
		}
		if (i<camlist.size()-1) data.append(";");
	}
	//std::cout << data.toUtf8().constData();
	OpenCV::CamSelectWindow *csw = new OpenCV::CamSelectWindow(AppCore::Core::getInstance(this->app)->getCoreWindow(),this->app,data);

	csw->exec();
	if (camlist[device_id]->isOpened()){
		return camlist[device_id];
	}
	return NULL;

}

OpenCV::CamSelectCore * OpenCV::CamSelectCore::getInstance(QApplication *app)
{
	if(mCamSelectCore == NULL)
	{
		mCamSelectCore = new OpenCV::CamSelectCore(app);
	}
	return mCamSelectCore;
}

int OpenCV::CamSelectCore::countCameras()
{
	int max = 10;
	for (int i = 0; i < max; i++){
		cv::VideoCapture temp(i);
		if (!temp.isOpened()){
			temp.release();
			temp.~VideoCapture();
			return i;
		}
		temp.release();
		temp.~VideoCapture();
	}
	return max;
}

void OpenCV::CamSelectCore::setCam(int dev_id, int width, int height){

	camlist[dev_id]->startCamera(width,height);
	this->device_id=dev_id;
}
