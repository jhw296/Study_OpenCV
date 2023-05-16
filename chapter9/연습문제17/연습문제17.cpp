#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
  Mat image = imread("../../image/mine2.jpg", 0);
  CV_Assert(image.data);

  Mat fimage;
  image.convertTo(fimage, CV_32F, 1.0 / 255);
  imshow("origin", image);

  Mat dimage;
  dct(fimage, dimage);

  imshow("DCT image", dimage);

  Mat dimage2;
  dct(dimage, dimage2, DCT_INVERSE);
  imshow("idct", dimage2);
  waitKey();

  return 0;
}