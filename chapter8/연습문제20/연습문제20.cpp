#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void draw_bar(Mat& img, int A, int B, int C, Point center)
{
  int small_interval = (int)(C / 24); // 괘 끼리의 사이 간격
  int big_interval = (int)(C / 4); // 괘와 원 사이의 간격
  int all_bar_width = (int)(C / 3); // 괘 전체의 길이
  int bar_width = (int)(C / 12); // 괘 가로길이
  int bar_height = (int)(C / 2); // 괘 세로 길이
  int small_bar_height = (int)((bar_height - small_interval) / 2); // 작은 괘의 세로길이
  int circle_radius = (int)(C / 2); // 태극무늬의 반지름
  int bar_next_interval = bar_width + small_interval; // 괘에서 다음괘의 사이 간격

  Mat img2(img.size(), img.type());
  img2.setTo(255); // 바탕은 흰색

  Rect gun[3], gon[6], gam[5], ri[4];

  // 건
  gun[0] = Rect(center.x - circle_radius - big_interval - all_bar_width,
     center.y - (int)(bar_height / 2),
     bar_width,
     bar_height);
  gun[1] = Rect(gun[0].x + bar_next_interval, gun[0].y, bar_width, bar_height);
  gun[2] = Rect(gun[1].x + bar_next_interval, gun[0].y, bar_width, bar_height);

  // 곤
  gon[0] = Rect(center.x + circle_radius + big_interval + all_bar_width - bar_width,
     gun[0].y, bar_width, small_bar_height);
  gon[1] = Rect(gon[0].x - bar_next_interval, gun[0].y, bar_width, small_bar_height);
  gon[2] = Rect(gon[1].x - bar_next_interval, gun[0].y, bar_width, small_bar_height);
  gon[3] = Rect(gon[0].x, center.y + (int)(small_interval / 2), bar_width, small_bar_height);
  gon[4] = Rect(gon[1].x, gon[3].y, bar_width, small_bar_height);
  gon[5] = Rect(gon[2].x, gon[3].y, bar_width, small_bar_height);

  // 감
  gam[0] = gon[2];
  gam[1] = gon[5];
  gam[2] = Rect(gon[1].x, gon[1].y, bar_width, bar_height);
  gam[3] = gon[0];
  gam[4] = gon[3];

  // 리
  ri[0] = gun[0];
  ri[1] = Rect(gun[1].x, gun[1].y, bar_width, small_bar_height);
  ri[2] = Rect(gun[1].x, gun[1].y + small_bar_height + small_interval, bar_width, small_bar_height);
  ri[3] = gun[2];

  Scalar black(0, 0, 0);
  // 건
  for (auto r : gun)
     rectangle(img, r, black, -1);
  // 곤
  for (auto r : gon)
     rectangle(img, r, black, -1);
  // 감
  for (auto r : gam)
     rectangle(img2, r, black, -1);
  // 리
  for (auto r : ri)
     rectangle(img2, r, black, -1);


  Mat rotation_mat = getRotationMatrix2D(center, -30, 1); // 회전행렬 구하기 태극뮈늬와 건곤을 -30도 회전
  Mat rotation_mat2 = getRotationMatrix2D(center, 30, 1); // 감리 를 30도 회전
  Mat dst;
  Mat dst2;

  // 회전 변화 수행
  //WARP_FILL_OUTLIERS : warpAffine 함수의 flags로 여백공간의 색상을 정할 수 있다.
  // 여기서는 흰색으로 정한다.
  warpAffine(img, dst, rotation_mat, img.size(), WARP_FILL_OUTLIERS, 0, Scalar(255, 255, 255)); // 회전 수행
  warpAffine(img2, dst2, rotation_mat2, img2.size(), WARP_FILL_OUTLIERS, 0, Scalar(255, 255, 255));

  // 회전하는 각도가 다른 두 영상을 하나로 합친다.
  img = dst & dst2; // 두 영상을 합친다.

}

int main(void)
{
  int A, B; // 너비, 길이
  int C; // 지름

  // 태극문양 지름을 입력받기
  cout << "지름을 입력하세요 : ";
  cin >> C;
  // 길이 정보 계산
  A = 2 * C;
  B = (int)(A * 1.5);

  // 영상
  Mat img(A, B, CV_8UC3, Scalar(255, 255, 255));

  // 태극 그리기

  Scalar blue(255, 0, 0), red(0, 0, 255); // 색상
  Point center(B / 2, A / 2); // 태극 중심 좌표
  Size circle_Big(C / 2, C / 2), circle_small(C / 4, C / 4); // 태극 문양을 그리기 위한 두개의 원

  // 빨강과 파란색의 반원을 아래위로 그린다.
  ellipse(img, center, circle_Big, 0, 0, 180, blue, -1);
  ellipse(img, center, circle_Big, 0, 180, 360, red, -1);
  // 작은 반원을 아래 위로 그려준다.
  ellipse(img, Point(center.x - circle_small.width, center.y), circle_small, 0, 0, 180, red, -1);
  ellipse(img, Point(center.x + circle_small.width, center.y), circle_small, 0, 180, 360, blue, -1);

  // 건곤감리 그리기 함수 호출
  draw_bar(img, A, B, C, center);

  // 영상출력
  imshow("korea", img);
  waitKey();

  return 0;
}