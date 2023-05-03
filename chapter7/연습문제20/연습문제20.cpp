#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
using namespace cv;
using namespace std;

// void image_read(int no) {
    
// }
// int main()
// {
// 	while(1)
// 	{
//         int no = 0;
//         int key = waitKey(100);
//         // if (key == 27) break;
//         if (key == 38) break;

//         switch (key) {
//             case 0x260000: no += 1;
//             case 0x280000: no -= 1;
//         }

// 		string fname = format("../test_car/%02d.jpg", no);
// 		Mat image = imread(fname, 1); 
// 		if (image.empty()) {
// 			cout << to_string(no) + "번 영상 파일이 없습니다. " << endl;
// 			continue;
// 		}

// 		Mat gray, sobel, th_img, morph;
// 		Mat kernel(5, 31, CV_8UC1, Scalar(1));		// 닫임 연산 마스크
// 		cvtColor(image, gray, CV_BGR2GRAY);		// 명암도 영상 변환

// 		blur(gray, gray, Size(5, 5));					// 블러링
// 		Sobel(gray, gray, CV_8U, 1, 0, 3);			// 소벨 에지 검출

// 		threshold(gray, th_img, 120, 255, THRESH_BINARY);	// 이진화 수행
// 		morphologyEx(th_img, morph, MORPH_CLOSE, kernel);	// 열림 연산 수행

// 		imshow("image", image);
// 		imshow("이진 영상", th_img), imshow("열림 연산", morph);
// 		// waitKey();
// 	} 
// 	return 0;
// }

#include <opencv2/imgproc/types_c.h>
int main()
{
   while (1)
   {
      int no;
      cout << "차량 영상 번호( 0:종료 ) : ";
      cin >> no;      // 차량 번호 입력
      if (no == 0) break;

      string fname = format("../test_car/%02d.jpg", no);   // 영상 파일 이름 구성
      Mat image = imread(fname, 1);
      if (image.empty()) {      // 영상 파일 예외처리
         cout << to_string(no) + "번 영상 파일이 없습니다. " << endl;
         continue;
      }
      Mat gray, sobel, th_img, morph;
      Mat kernel(5, 25, CV_8UC1, Scalar(1));   // 열림 연산 마스크
      cvtColor(image, gray, CV_BGR2GRAY);      // 명암도 영상 변환

      blur(gray, gray, Size(5, 5));         // 블러링
      Sobel(gray, gray, CV_8U, 1, 0, 3);      // 소벨 에지 검출

      threshold(gray, th_img, 120, 255, THRESH_BINARY);   // 이진화 수행
      morphologyEx(th_img, morph, MORPH_CLOSE, kernel);   // 열림 연산 수행

      imshow("image", image);
      imshow("이진 영상", th_img);
      imshow("열림 영상", morph);
      waitKey(0);

      char key = waitKey(0);
      if (key == 27) break; // ESC 키 누르면 종료
      else if (key == 81 || key == 83) no += key == 81 ? -1 : 1; // ←, → 키로 이전, 다음 영상 로드
   }
   return 0;
}