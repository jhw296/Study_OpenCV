#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
using namespace cv;
using namespace std;

void hough_coord(Mat image, Mat& acc_mat, double rho, double theta)
{
    int acc_h = int((image.rows + image.cols) * 2 / rho);
    int acc_w = int(180 / theta);

    acc_mat = Mat(acc_h, acc_w, CV_32S, Scalar(0));

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++)
        {
            Point pt(j, i);
            if (image.at<uchar>(pt) > 0) {

                for (int t = 0; t < acc_w; t++)
                {
                    double radian = t * theta * CV_PI / 180;
                    double r = pt.x * cos(radian) + pt.y * sin(radian);
                    r = cvRound(r / rho + acc_mat.rows / 2.0);
                    acc_mat.at<int>((int)r, t)++;
                }
            }
        }
    }
}

void acc_mask(Mat acc_mat, Mat& acc_dst, Size size, int thresh)
{
    acc_dst = Mat(acc_mat.size(), CV_32S, Scalar(0));
    Point h_m = size / 2;    // 마스크 크기 절반

    for (int r = h_m.y; r < acc_mat.rows - h_m.y; r++) {
        for (int t = h_m.x; t < acc_mat.cols - h_m.x; t++)
        {
            Point center = Point(t, r) - h_m;
            int c_value = acc_mat.at<int>(center);    // 중심화소
            if (c_value >= thresh)
            {
                double maxVal = 0;
                for (int u = 0; u < size.height; u++) {
                    for (int v = 0; v < size.width; v++)
                    {
                        Point start = center + Point(v, u);
                        if (start != center && acc_mat.at<int>(start) > maxVal)
                            maxVal = acc_mat.at<int>(start);
                    }
                }

                Rect rect(center, size);
                if (c_value >= maxVal)
                {
                    acc_dst.at<int>(center) = c_value;
                    acc_mat(rect).setTo(0);
                }
            }
        }
    }
}

void thres_lines(Mat acc_dst, Mat& lines, double _rho, double theta, int thresh)
{
    for (int r = 0; r < acc_dst.rows; r++) {
        for (int t = 0; t < acc_dst.cols; t++)
        {
            float value = (float)acc_dst.at<int>(r, t);            // 누적값
            if (value >= thresh)                                // 직선 길이 임계값
            {
                float rho = (float)((r - acc_dst.rows / 2) * _rho);        // 수직거리
                float radian = (float)(t * theta * CV_PI / 180);                        // 각도

                Matx13f line(rho, radian, value);                 // 단일 직선
                lines.push_back((Mat)line);
            }
        }
    }
}

void sort_lines(Mat lines, vector<Vec2f>& s_lines)
{
    Mat acc = lines.col(2), idx;
    sortIdx(acc, idx, SORT_EVERY_COLUMN + SORT_DESCENDING);

    for (int i = 0; i < idx.rows; i++)
    {
        int id = idx.at<int>(i);
        float rho = lines.at<float>(id, 0);        // 수직거리
        float radian = lines.at<float>(id, 1);
        s_lines.push_back(Vec2f(rho, radian));
    }
}

void houghLines(Mat src, vector<Vec2f>& s_lines, double rho, double theta, int thresh)
{
    Mat acc_mat, acc_dst, lines;
    hough_coord(src, acc_mat, rho, theta);
    acc_mask(acc_mat, acc_dst, Size(3, 7), thresh);

    thres_lines(acc_dst, lines, rho, theta, thresh);
    sort_lines(lines, s_lines);
}

void draw_houghLines(Mat image, Mat& dst, vector<Vec2f> lines, int nline, int lineThickness)
{
    image.copyTo(dst);

    for (int i = 0; i < min((int)lines.size(), nline); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        Point pt1(cvRound(x0 + 1000 * (-b)), cvRound(y0 + 1000 * (a)));
        Point pt2(cvRound(x0 - 1000 * (-b)), cvRound(y0 - 1000 * (a)));

        line(dst, pt1, pt2, Scalar(0, 255, 0), lineThickness, LINE_AA);
    }
}

int main()
{
    Mat image = imread("../../image/hough_test3.jpg");
    CV_Assert(image.data);

    Mat canny, dst1, dst2;
    cvtColor(image, canny, COLOR_BGR2GRAY);
    GaussianBlur(canny, canny, Size(5, 5), 2, 2);
    Canny(canny, canny, 100, 150, 3);

    double rho = 1, theta = 2;
    int thresh = 100;
    int maxLines = 10;
    int lineThickness = 2;

    vector<Vec2f> lines1, lines2;
    houghLines(canny, lines1, rho, theta, thresh);
    HoughLines(canny, lines2, rho, theta * CV_PI / 180, thresh);
    draw_houghLines(image, dst1, lines1, maxLines, lineThickness);
    draw_houghLines(image, dst2, lines2, maxLines, lineThickness);

    imshow("source", image);
    imshow("canny", canny);
    imshow("detected lines", dst1);
    imshow("detected lines_OpenCV", dst2);
    waitKey(0);

    return 0;
}