#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#include <opencv2/imgproc/types_c.h>
int main() {
  Mat BGR_img = imread("../../image/color_space.jpg", 1);
  CV_Assert(BGR_img.data);

  /*Mat YCC_img, RGB_recovered_img;
  cvtColor(BGR_img, YCC_img, CV_BGR2YCrCb);
  cvtColor(YCC_img, RGB_recovered_img, CV_YCrCb2BGR);

  imshow("Original", BGR_img);
  imshow("YCbCr", YCC_img);
  imshow("Restored", RGB_recovered_img);*/
  
  // YCbCr 컬러 공간변환
  Mat YCC_img(BGR_img.size(), BGR_img.type());
  for (int i = 0; i < BGR_img.rows; i++) {
     for (int j = 0; j < BGR_img.cols; j++) {
        Vec3b bgr = BGR_img.at<Vec3b>(i, j);
        
        int Y = 0.299 * bgr[2] + 0.587 * bgr[1] + 0.114 * bgr[0];
        int Cb = (bgr[2] - Y) * 0.564 + 128;
        int Cr = (bgr[0] - Y) * 0.713 + 128;

        YCC_img.at<Vec3b>(i, j) = Vec3b(Y, Cb, Cr);
     }
  }

  // BGR 컬러 공간변환
  Mat BGR_recovered_img(YCC_img.size(), YCC_img.type());
  for (int i = 0; i < YCC_img.rows; i++) {
     for (int j = 0; j < YCC_img.cols; j++) {
        Vec3b ycc = YCC_img.at<Vec3b>(i, j);
        int R = ycc[0] + 1.403 * (ycc[2] - 128);
        int G = ycc[0] - 0.714 * (ycc[1] - 128) - 0.344 * (ycc[1] - 128);
        int B = ycc[0] + 1.773 * (ycc[1] - 128);
        BGR_recovered_img.at<Vec3b>(i, j) = Vec3b(R, G, B);
     }
  }
  imshow("Original", BGR_img);
  imshow("YCbCr", YCC_img);
  imshow("Recovered", BGR_recovered_img);

  waitKey();
  return 0;
}