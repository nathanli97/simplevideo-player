#include "common.h"
string UnicodeToANSI(const wstring& str)
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_ACP,
		0,
		str.c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	::WideCharToMultiByte(CP_ACP,
		0,
		str.c_str(),
		-1,
		pElementText,
		iTextLen,
		NULL,
		NULL);
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}
int _stdcall wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int nCmdShow
) {
	MessageBox(NULL, TEXT("By:LiXingru,Beifang University of Nationalities.\nq:quit,\np:play/pause,\nn:show playing position,\na:Rewind\nd:Fast forward"), TEXT("VideoPlayer Usage"), MB_OK);
	if(lstrlen(lpCmdLine)==0) MessageBox(NULL, TEXT("ERROR:NO INPUT FILE"), TEXT("VideoPlayer ERROR"), MB_OK);
	cvNamedWindow("VideoPlayer",CV_WINDOW_AUTOSIZE);
	VideoPlayer player(UnicodeToANSI(lpCmdLine), "VideoPlayer");
	IplImage *frame;
	LPWSTR str = new wchar_t[10];
	while (1) {
		if (player.isPlaying()) {
			frame = player.getFrame();
			if (frame == NULL) break;
			cvShowImage("VideoPlayer", frame);
		}
		char c = cvWaitKey(33);
		switch (c) {
		case 'q': 
			player.Stop();
			exit(0);
		case ' ':
			if (player.isPlaying()) player.Pause();
			else player.Play();
			break;
		case 'n':
			swprintf(str, TEXT("Position:%.5lf%%"), player.getPlayerPosition());
			MessageBox(NULL, str , TEXT("Position"), MB_OK);
			if (!player.isPlaying()) Sleep(500);
		case 'a':
			player.left();
			Sleep(100);
			break;
		case 'd':
			player.right();
			Sleep(100);
			break;
		}
	}
	return 0;
}