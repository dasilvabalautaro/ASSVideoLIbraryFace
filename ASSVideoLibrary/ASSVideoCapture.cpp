#include "ASSVideoCapture.h"


ASSVideoCapture::ASSVideoCapture(ASSVideoConfig* config)
{
	_asvideoConfig = config;
	//GdiplusStartupInput gdiplusStartupInput;
	///*ULONG_PTR gdiplusToken;*/
	//GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

}

ASSVideoCapture::~ASSVideoCapture()
{
	//GdiplusShutdown(gdiplusToken);
}

string ASSVideoCapture::GetNameFileImage() {
	return nameFileImageTemp;
}

string ASSVideoCapture::GetNameWindow() {
	return _asvideoConfig->getNameWindow();
}

int ASSVideoCapture::getFps() {
	return fps_camera;
}

void ASSVideoCapture::setFps(VideoCapture cap) {
	if (_asvideoConfig->getFps().empty()) {
		fps_camera = (int)(cap.get(CAP_PROP_FPS));
		if (fps_camera < 0) {
			cap.set(CAP_PROP_FPS, FPS);
			fps_camera = FPS;
		}
	}
	else {
		string value = _asvideoConfig->getFps();
		fps_camera = atoi(value.c_str());
	}
}

void ASSVideoCapture::processVideo() {

	if (buildPathVideo()) {
		VideoCapture capture;
		if (_deviceId != -1) {
			capture.open(_deviceId);
		}
		else {
			capture.open(_urlVideo);
		}

		if (!capture.isOpened()) {
			cout << "Unable to open video file: " << _urlVideo << endl;
			return;
		}
		setFps(capture);
		while (flagCapture) {
			if (!capture.read(_frame)) {
				cout << "Unable to read next frame." << endl;
				cout << "Exiting..." << endl;
				return;
			}
			else {
				sendFrame(_frame);
				if (waitKey(1000 / fps_camera) >= 0) {
					flagCapture = false;
				}
			}
		}
		capture.release();
	}

}

Mat ASSVideoCapture::readImage(string fileName) {
	return imread(fileName, IMREAD_COLOR);
}

int ASSVideoCapture::getCountBatch() {
	return _countBatch;
}
void ASSVideoCapture::resetCountBatch() {
	_countBatch = 0;
}

void ASSVideoCapture::writeImageBatch(Mat frame) {

	_countBatch++;
	string fileTemp = to_string(_countBatch) + nameFileImageTemp;
	imwrite(fileTemp, frame);
	if (_countBatch == _quantityBatch)
	{
		_countBatch = 0;
	}

}

void ASSVideoCapture::writeImage(Mat frame) {
	imwrite(nameFileImageTemp, frame);
}

void ASSVideoCapture::setQuantityBach(int value) {
	_quantityBatch = value;
}

unsigned char* ASSVideoCapture::getBytesFromMat(Mat frame) {

	return frame.data;
}

//void ASSVideoCapture::getBitmapFromMat(Mat i_Mat) {
//
//	Mat i_MatBgr;
//	cv::cvtColor(i_Mat, i_MatBgr, cv::COLOR_RGB2BGR);
//
//	PixelFormat e_Format;
//	switch (i_MatBgr.channels())
//	{
//	case 1: e_Format = PixelFormat8bppIndexed; break;
//	case 3: e_Format = PixelFormat24bppRGB;    break;
//	case 4: e_Format = PixelFormat32bppARGB;   break;
//	default: cout << "Image format not supported." << endl;
//
//	}
//
//
//	cv::Size size = i_MatBgr.size();
//	Bitmap* pi_Bmp = new Bitmap(size.width, size.height, i_MatBgr.step1(), e_Format, i_MatBgr.data);
//
//	Gdiplus::BitmapData i_Data;
//	Gdiplus::Rect k_Rect(0, 0, i_MatBgr.cols, i_MatBgr.rows);
//
//	switch (pi_Bmp->LockBits(&k_Rect, ImageLockModeWrite, e_Format, &i_Data))
//	{
//	case Ok:  cout << "Ok LockBits." << endl; break;
//	case GenericError: cout << "GenericError." << endl; break;
//	case InvalidParameter: cout << "Invalid Parameter." << endl; break;
//	default: cout << "Other problem." << endl; break;
//	}
//
//
//	if (i_MatBgr.elemSize1() == 1) // 1 Byte per channel (8 bit gray scale palette)
//	{
//
//		BYTE* u8_Src = i_MatBgr.data;
//		BYTE* u8_Dst = (BYTE*)i_Data.Scan0;
//
//		int s32_RowLen = i_MatBgr.cols * i_MatBgr.channels(); // != i_Mat.step !!
//
//														// The Windows Bitmap format requires all rows to be DWORD aligned (always!)
//														// while OpenCV by default stores bitmap data sequentially.
//		for (int R = 0; R < i_MatBgr.rows; R++)
//		{
//			memcpy(u8_Dst, u8_Src, s32_RowLen);
//			u8_Src += i_MatBgr.step;    // step may be e.g 3729
//			u8_Dst += i_Data.Stride; // while Stride is 3732
//		}
//	}
//
//	// Add the grayscale palette if required.
//	if (e_Format == PixelFormat8bppIndexed)
//	{
//		BYTE* copy = new BYTE[sizeof(ColorPalette) + 256 * sizeof(ARGB)];
//		ColorPalette* pk_Palette = (ColorPalette*)copy;
//
//		pk_Palette->Count = 256;
//		pk_Palette->Flags = PaletteFlagsGrayScale;
//
//		ARGB* pk_Color = &pk_Palette->Entries[0];
//		for (int i = 0; i < 256; i++)
//		{
//			pk_Color[i] = Color::MakeARGB(255, i, i, i);
//		}
//
//		if (Ok != pi_Bmp->SetPalette(pk_Palette))
//		{
//			delete pi_Bmp;
//			throw L"Error setting grayscale palette.";
//		}
//	}
//
//	pi_Bmp->UnlockBits(&i_Data);
//
//	if (pi_Bmp->GetLastStatus() == Gdiplus::Ok)
//	{
//		bitmapGlobal = new Gdiplus::Bitmap(
//			pi_Bmp->GetWidth(),
//			pi_Bmp->GetHeight());
//		Gdiplus::Graphics g(bitmapGlobal);
//		g.DrawImage(
//			pi_Bmp,
//			0,
//			0,
//			pi_Bmp->GetWidth(),
//			pi_Bmp->GetHeight());
//	}
//	delete pi_Bmp;
//}
//
//unsigned char* ASSVideoCapture::getCharFromMat(Mat i_Mat) {
//	Mat i_MatBgr;
//	cv::cvtColor(i_Mat, i_MatBgr, cv::COLOR_RGB2BGR);
//
//	PixelFormat e_Format;
//	switch (i_MatBgr.channels())
//	{
//	case 1: e_Format = PixelFormat8bppIndexed; break;
//	case 3: e_Format = PixelFormat24bppRGB;    break;
//	case 4: e_Format = PixelFormat32bppARGB;   break;
//	default: cout << "Image format not supported." << endl;
//
//	}
//
//	cv::Size size = i_MatBgr.size();
//	Bitmap* pi_Bmp = new Bitmap(size.width, size.height, i_MatBgr.step1(), e_Format, i_MatBgr.data);
//
//	Gdiplus::BitmapData bitmapData;
//	Gdiplus::Rect k_Rect(0, 0, i_MatBgr.cols, i_MatBgr.rows);
//
//	switch (pi_Bmp->LockBits(&k_Rect, ImageLockModeWrite, e_Format, &bitmapData))
//	{
//	case Ok:  cout << "Ok LockBits." << endl; break;
//	case GenericError: cout << "GenericError." << endl; break;
//	case InvalidParameter: cout << "Invalid Parameter." << endl; break;
//	default: cout << "Other problem." << endl; break;
//	}
//	BYTE* ptr = (BYTE*)bitmapData.Scan0;
//	int bytes = abs(bitmapData.Stride) * pi_Bmp->GetHeight();
//	BYTE* rgbValues = new byte[bytes];
//	for (int row = 0; row < bitmapData.Height; ++row) {
//		for (int col = 0; col < bitmapData.Width; ++col) {
//			rgbValues[row * pi_Bmp->GetWidth() + col] = ptr[row * bitmapData.Stride / 4 + col];
//		}
//	}
//
//	pi_Bmp->UnlockBits(&bitmapData);
//	unsigned char * data = (unsigned char*)rgbValues;
//	return data;
//}
//
//unsigned char* ASSVideoCapture::getBufferFromBitmap(Bitmap* img) {
//
//	BitmapData bitmapData;
//	
//	cout << "PIXEL FORMAT " << img->GetPixelFormat() << endl;
//
//	img->LockBits(&Gdiplus::Rect(0, 0, img->GetWidth(),
//		img->GetHeight()), ImageLockModeWrite, img->GetPixelFormat(), &bitmapData);
//
//	
//	BYTE* ptr = (BYTE*)bitmapData.Scan0;
//	
//	int bytes = abs(bitmapData.Stride) * img->GetHeight();
//	BYTE* rgbValues = new byte[bytes];
//	
//
//	for (int row = 0; row < bitmapData.Height; ++row) {
//		for (int col = 0; col < bitmapData.Width; ++col) {
//			rgbValues[row * img->GetWidth() + col] = ptr[row * bitmapData.Stride / 4 + col];
//		}
//	}
//
//	img->UnlockBits(&bitmapData);
//	unsigned char * data = (unsigned char*)rgbValues;
//	return data;
//	
//}

void ASSVideoCapture::sendFrame(Mat inputImg) {

	frameout.on_next(inputImg);
}

bool ASSVideoCapture::buildPathVideo() {
	string path = _asvideoConfig->getPath();
	nameFileImageTemp = _asvideoConfig->getImageTemp();
	if (!path.empty()) {
		if (isPositiveInteger(path)) {
			_deviceId = stoi(path);
		}
		else if (searchProtocol(path)) {
			_urlVideo = buildUrl(path);
		}
		else {
			_urlVideo = path;
		}
		return true;
	}
	else {
		return false;
	}
}

bool ASSVideoCapture::isPositiveInteger(string &device) {
	return !device.empty() &&
		(std::count_if(device.begin(), device.end(), std::isdigit) == device.size());
}


bool ASSVideoCapture::searchProtocol(string &device) {
	string word = "http://";
	if (device.find(word) == string::npos) {
		return false;
	}
	else {
		return true;
	}
}

string ASSVideoCapture::buildUrl(string device) {
	device.replace(0, 7, "");
	string url = "http://" + _asvideoConfig->getUser() + ":" +
		_asvideoConfig->getPassword() + "@" +
		device + "/axis-cgi/mjpg/video.cgi?resolution=" +
		_asvideoConfig->getResolution() + "&req_fps=30&.mjpg";
	return url;
}
