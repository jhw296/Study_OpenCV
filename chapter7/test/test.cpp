#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// ch4 8
// int main()
// {
//     Mat image(300, 400, CV_8UC3, Scalar(255, 255, 255));
//     Point pt1(50, 130), pt2(200, 300);
//     Rect rect(pt1, Size(100, 150));

//     line(image, pt1, Point(100, 200), Scalar(0, 0, 0));
//     line(image, pt1, Point(300, 400), Scalar(100, 100, 100));
//     rectangle(image, pt1, pt2, Scalar(255, 0, 255));
//     rectangle(image, rect, Scalar(0, 0, 255));

//     imshow("line & rect", image);
//     waitKey(0);
    
// 	return 0;
// }

// ch5 6-1
// int main()
// {
//     Matx23f m1(1, 2, 3, 1, 2, 3);
//     Matx23f m2(3, 3, 4, 2, 2, 3);
//     Mat m3 = m1 + m2;
//     Mat m4 = m1 * m2;

//     cout << "[m1] = " << endl << m1 << endl;
//     cout << "[m2] = " << endl << m2 << endl;
//     cout << "[m3] = " << endl << m3 << endl;
//     cout << "[m4] = " << endl << m4 << endl;
    
// 	return 0;
// }

// ch5 6-2
// int main()
// {
//     int data[] = {
//         1, 2, 3, 4, 5, 6, 7, 8, 9, 10
//     };
//     Mat m1(2, 3, CV_8UC2, data);
//     vector<Mat> sp_mat;
//     split(m1, sp_mat);
//     cout << sp_mat[1] << endl;
    
// 	return 0;
// }

// ch5 6-3
// int main()
// {
//     Mat_<uchar> m1(2, 3), m2(2, 3);
//     Mat_<uchar> m3(2, 3), m4(1, 3);

//     m1 << 1, 1, 2, 2, 3, 3;
//     m2 << 2, 1, 3, 1, 4, 1;

//     subtract(m1, m2, m3);
//     reduce(m1, m4, 0, REDUCE_MAX);

//     cout << "[m3] = " << endl << m3 << endl;
//     cout << "[m4] = " << endl << m4 << endl;
//     cout << "sum(m1) = " << endl << sum(m1) << endl;
//     cout << "mean(m2) = " << endl << mean(m2) << endl;

// 	return 0;
// }

// ch6 9-1
// int main()
// {
//     Mat_<uchar> m1(2, 3), m2(2, 3);
//     Mat_<uchar> m3(2, 3), m4(1, 3);

//     m1 << 1, 1, 2, 2, 3, 3;
//     m2 << 2, 1, 3, 1, 4, 1;

//     subtract(m1, m2, m3);
//     reduce(m1, m4, 0, REDUCE_MAX);

//     cout << "[m3] = " << endl << m3 << endl;
//     cout << "[m4] = " << endl << m4 << endl;
//     cout << "sum(m1) = " << endl << sum(m1) << endl;
//     cout << "mean(m2) = " << endl << mean(m2) << endl;

// 	return 0;
// }


int main()
{
    Mat image(300, 400, CV_8U);
    image.setTo(100);

    namedWindow("window", WINDOW_NORMAL);
    moveWindow("window", 100, 200);
    imshow("window", image);
    waitKey();    
}