#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#include  "fft.hpp"

Mat		image, dft_coef, spectrum_img;
int		radius, thres = 120;

void remove_moire(int  value, void*  userdata)
{
	Mat remove_mask, remv_dft_coef , spectrum_tmp;

	// 주파수 제거 위한 마스크 생성
	threshold(spectrum_img, remove_mask, thres, 255, THRESH_TOZERO_INV);
	threshold(remove_mask, remove_mask, 1, 255, THRESH_BINARY);
	circle(remove_mask, remove_mask.size() / 2, radius, Scalar(255), -1);

	dft_coef.copyTo(remv_dft_coef, remove_mask);
	log_mag(remv_dft_coef, spectrum_tmp);				// 모아레 제거된 스펙트럼
	
	Rect img_rect(Point(0, 0), image.size());
	imshow("remove", spectrum_tmp);
	imshow("result", IFFT(remv_dft_coef, image.size()));
}

int main()
{
	image = imread("../../image/mo3.jpg", 0);
	CV_Assert(image.data);

	FFT(image, dft_coef, spectrum_img);
	radius = dft_coef.rows / 4;

	imshow("image", image);
	imshow("remove", spectrum_img);
	createTrackbar("radius", "remove", &radius, 255, remove_moire);
	createTrackbar("value", "remove", &thres , 255, remove_moire);
	waitKey();
	return 0;
}