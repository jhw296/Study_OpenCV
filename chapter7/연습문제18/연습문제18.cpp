#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
using namespace cv;
using namespace std;

int main() {
    Mat image = imread("../../image/coin.jpg", 1);
    Mat gray, gauss_img, binary_image, morphology_image;

    CV_Assert(image.data);

    imshow("image", image);

    cvtColor(image, gray, CV_BGR2GRAY);
    // imshow("gray", gray);

    Size size(5, 25);
    double sigmaX = 0.3 * ((size.width - 1) * 0.5 - 1) + 0.8;
    double sigmaY = 0.3 * ((size.height - 1) * 0.5 - 1) + 0.8;

    GaussianBlur(gray, gauss_img, size, sigmaX, sigmaY);
    // imshow("gaussian_blur", gauss_img);

    threshold(gauss_img, binary_image, 170, 255, THRESH_BINARY_INV);
    // imshow("binary_image", binary_image);

    Matx <uchar, 3, 3> mask;
    mask << 0, 1, 0,
            1, 1, 1,
            0, 1, 0;

    morphologyEx(binary_image, morphology_image, MORPH_CLOSE, mask);

    imshow("morphology_image", morphology_image);

    waitKey();
    return 0;
}