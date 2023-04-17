#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#include <opencv2/imgproc/types_c.h>

// 전역 변수
bool drawing = false;
int ix, iy, cx, cy;
Mat img;
string title1 = "problem 17";
string title2 = "ROI";

// 마우스 이벤트 콜백 함수
void draw_rectangle(int event, int x, int y, int flags, void* param) {
   switch (event) 
   {
   case EVENT_LBUTTONDOWN:
       drawing = true;
       ix = x;
       iy = y;
       break;
   
   case EVENT_MOUSEMOVE:
       if (drawing) {
           Mat img_copy;
           img.copyTo(img_copy);
           rectangle(img_copy, Point(ix, iy), Point(x, y), Scalar(0, 255, 0), 2);
           imshow(title1, img_copy);
       }
       break;
   
   case EVENT_LBUTTONUP:
       drawing = false;
       cx = x;
       cy = y;
       Mat img_copy;
       img.copyTo(img_copy);
       rectangle(img_copy, Point(ix, iy), Point(cx, cy), Scalar(0, 255, 0), 2);

       // 선택된 영역 반전
       Mat roi(img_copy, Rect(ix, iy, cx - ix, cy - iy));
	   imshow(title2, roi);
       bitwise_not(roi, roi);

       imshow(title1, img_copy);
       break;
   }
}

// 히스토그램 계산 함수
void  calc_Histo(const Mat& image, Mat& hist, int bins, int range_max = 256)
{
  int      histSize[] = { bins };         // 히스토그램 계급개수
  float   range[] = { 0, (float)range_max };      // 히스토그램 범위
  int      channels[] = { 0 };            // 채널 목록
  int      dims = image.channels();;
  const float* ranges[] = { range };

  calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
}

// hue 채널에 대한 색상 팔레트 행렬 생성
Mat  make_palatte(int rows)
{
  Mat hsv(rows, 1, CV_8UC3);
  for (int i = 0; i < rows; i++)
  {
     uchar hue = saturate_cast<uchar>((float)i / rows * 180);
     hsv.at<Vec3b>(i) = Vec3b(hue, 255, 255);
  }
  cvtColor(hsv, hsv, CV_HSV2BGR);
  return hsv;
}

// 색상으로 히스토그램 그리기
void draw_histo_hue(Mat hist, Mat& hist_img, Size size = Size(256, 200))
{
  Mat hsv_palatte = make_palatte(hist.rows);

  hist_img = Mat(size, CV_8UC3, Scalar(255, 255, 255));
  float  bin = (float)hist_img.cols / hist.rows;
  normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);

  for (int i = 0; i < hist.rows; i++)
  {
     float start_x = (i * bin);
     float  end_x = (i + 1) * bin;
     Point2f pt1(start_x, 0);
     Point2f pt2(end_x, hist.at <float>(i));


     Scalar color = hsv_palatte.at<Vec3b>(i);            // 색상팔레트 색지정
     if (pt2.y > 0) rectangle(hist_img, pt1, pt2, color, -1);   // 팔레트 색 그리기   
  }
  flip(hist_img, hist_img, 0);
}

int main() {
   // 이미지 파일 읽기
   img = imread("../../image/color_space.jpg", 1);
   CV_Assert(!img.empty());

   // 윈도우 생성 및 마우스 이벤트 콜백 함수 설정
   namedWindow(title1);
   setMouseCallback(title1, draw_rectangle);

   Mat HSV_img, HSV_arr[3];
  cvtColor(img, HSV_img, CV_BGR2HSV);
  split(HSV_img, HSV_arr);

  Mat hue_hist, hue_hist_img;
  calc_Histo(HSV_arr[0], hue_hist, 18, 180);// Hue 채널 히스토그램 계산
  draw_histo_hue(hue_hist, hue_hist_img, Size(360, 200)); // 히스토그램 그래프

   imshow(title1, img);
   imshow("Histogram", hue_hist_img);

   waitKey();
   return 0;
}