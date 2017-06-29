#include "common.h"
void VideoPlayer::Play() {
		this->Playing = true;
		this->Stopped = false;
}
void VideoPlayer::Stop() {
		this->Playing = false;
		this->Stopped = true;
		this->PlayingPosition = 0;
}
double VideoPlayer::getPlayerPosition() { return this->PlayingPosition; };
void VideoPlayer::Pause(){
	this->Playing = false;
}
VideoPlayer::~VideoPlayer() {
	cvRetrieveFrame(video);
}
IplImage *VideoPlayer::getFrame() {
	IplImage *tmp=NULL;
	if (this->Playing) {
		tmp=cvQueryFrame(video);
		this->PlayingPosition=(cvGetCaptureProperty(video, CV_CAP_PROP_POS_FRAMES)/cvGetCaptureProperty(video,CV_CAP_PROP_FRAME_COUNT)*100);
		if (tmp == NULL) {
			this->Stop();
		}
		return tmp;
	}return NULL;
}

void VideoPlayer::left()
{
	double tmp = cvGetCaptureProperty(video, CV_CAP_PROP_POS_FRAMES);
	if (tmp - 50 >= 0) {
		cvSetCaptureProperty(video, CV_CAP_PROP_POS_FRAMES, tmp - 50);
	}
}

void VideoPlayer::right()
{
	double tmp = cvGetCaptureProperty(video, CV_CAP_PROP_POS_FRAMES);
	if (tmp + 50 <= cvGetCaptureProperty(video, CV_CAP_PROP_FRAME_COUNT)) {
		cvSetCaptureProperty(video, CV_CAP_PROP_POS_FRAMES, tmp + 50);
	}
}
