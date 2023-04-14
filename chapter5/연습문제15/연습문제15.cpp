#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
// int main()
// {
//     vector<Point3f> rect_pt1, rect_pt2;
//     rect_pt1.push_back(Point3f(200, 50, 1)), rect_pt1.push_back(Point3f(400, 50, 1));
//     rect_pt1.push_back(Point3f(400, 250, 1)), rect_pt1.push_back(Point3f(200, 250, 1));

//     // 회전 변환 행렬 : 3x3
//     float theta = 45 * CV_PI / 180;
//     Matx33f m;
//     m << cos(theta), -sin(theta), sin(theta), cos(theta), 0, 0, 0, 1;

//     // 평행이동 행렬
//     Mat t1 = Mat::eye(3, 3, CV_32F);
//     Mat t2 = Mat::eye(3, 3, CV_32F);

//     // 중심점 좌표 계산
//     Point3f delta = (rect_pt1[2] - rect_pt1[0] / 2.0f);
//     Point3f center = rect_pt1[0] + delta;

//     Mat image(400, 500, CV_8UC3, Scalar(255, 255, 255));
//     for(int i = 0; i < 4; i++) {
//         Point pt1(rect_pt1[i].x, rect_pt1[i].y);
//         Point pt2(rect_pt1[(i + 1) % 4].x, rect_pt1[(i + 1) % 4].y);
//         Point pt3(rect_pt2[i].x, rect_pt2[i].y);
//         Point pt4(rect_pt2[(i + 1) % 4].x, rect_pt2[(i + 1) % 4].y);

//         line(image, pt1, pt2, Scalar(0, 0, 0), 2);
//         line(image, pt3, pt4, Scalar(255, 0, 0), 2);

//         cout << "rect_pt1[" + to_string(i) + "]=" << rect_pt1[i] << "\t";
//         cout << "rect_pt2[" + to_string(i) + "]=" << rect_pt2[i] << "\t";
//     }
//     imshow("image", image);
//     waitKey();
//     return 0;
// }

int main() {
    vector<Point3f> rect_pt1, rect_pt2;
    rect_pt1.push_back(Point3f(200, 50, 1)), rect_pt1.push_back(Point3f(400, 50, 1));
    rect_pt1.push_back(Point3f(400, 250, 1)), rect_pt1.push_back(Point3f(200, 250, 1));

    // 중심점 계산
    Point3f delta = (rect_pt1[2] - rect_pt1[0]) / 2.0f;
    Point3f center = rect_pt1[0] + delta;

    // 회전 변환 행렬 계산
    float theta = 45 * CV_PI / 180;
    Matx33f m(cos(theta), -sin(theta), center.x * (1 - cos(theta)) + center.y * sin(theta),
        sin(theta), cos(theta), center.y * (1 - cos(theta)) - center.x * sin(theta),
        0, 0, 1);

    Mat image(400, 500, CV_8UC3, Scalar(255, 255, 255));
    for (int i = 0; i < 4; i++) {
        Point2f pt1(rect_pt1[i].x, rect_pt1[i].y);
        Point2f pt2(rect_pt1[(i + 1) % 4].x, rect_pt1[(i + 1) % 4].y);

        // 회전 변환 적용
        Point3f pt3 = m * rect_pt1[i];
        Point3f pt4 = m * rect_pt1[(i + 1) % 4];

        // 화면에 그리기 위해 Point2f로 변환
        Point2f pt5(pt3.x, pt3.y);
        Point2f pt6(pt4.x, pt4.y);

        line(image, pt1, pt2, Scalar(0, 0, 0), 2);
        line(image, pt5, pt6, Scalar(255, 0, 0), 2);
    }

    imshow("image", image);
    waitKey();
    return 0;
}