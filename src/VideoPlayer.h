#pragma once
#include "common.h"
#include <string>
using namespace std;
#ifndef _VIDEO_PLAYER_H
#define _VIDEO_PLAYER_H
class VideoPlayer {
private :
	string stringPath;
	string for_window_label;
	bool Playing;
	bool Stopped;
	CvCapture *video;
	IplImage *frame;
	double PlayingPosition;
public :
	VideoPlayer::VideoPlayer(string strPath, string strWin) :stringPath(strPath), for_window_label(strWin),PlayingPosition(0) ,Playing(true), Stopped(false), video(cvCreateFileCapture(this->stringPath.c_str())) {};
	~VideoPlayer();
	void Play();
	void Stop();
	void Pause();
	bool isPlaying() { return Playing; }
	bool isStopped() { return Stopped; }
	double getPlayerPosition();
	IplImage *getFrame();
	void left();
	void right();
};
#endif