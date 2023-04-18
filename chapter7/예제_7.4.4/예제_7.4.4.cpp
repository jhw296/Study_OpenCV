#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
using namespace cv;
using namespace std;

int main() {
    while(1){
        int no;
        cout << "차량 영상 번호( 0:종료 ) : ";
        cin >> no;
        if(no == 0) break;

        string frame = format("./test_car/%02d.jpg", no);
        Mat image = imread(frame, 1);
        if(image.empty()) {
            cout << to_string(no) + "번 영상 파일이 없습니다. " << endl;
            continue;
        }

        Mat gray, sobel, th_img, morph;
        Mat kernel(5, 25, CV_8UC1, Scalar(1));
        cvtColor(image, gray, CV_BGR2GRAY);
        blur(gray, gray, Size(5, 5));
        Sobel(gray, gray, CV_8U, 1, 0, 3);

        threshold(gray, th_img, 120, 255, THRESH_BINARY);
        morphologyEx(th_img, morph, MORPH_CLOSE, kernel);

        imshow("image", image);
        imshow("binary vedio", th_img), imshow("open operate", morph);

        waitKey(0);
    }
    return 0;
}