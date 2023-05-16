#include <opencv2/opencv.hpp>
#include <cmath>
using namespace cv;
using namespace std;

Mat calc_cosine(int N, int M)
{
  Mat cos_mat(N * N, M * M, CV_32F);

  for (int k = 0; k < N; k++) {
     for (int l = 0; l < M; l++)
     {
        Point idx(l * M, k * N);
        for (int n = 0; n < N; n++) {
           for (int m = 0; m < M; m++)
           {
              float theta1 = (float)((2 * n + 1) * k * CV_PI / (2 * N));
              float theta2 = (float)((2 * m + 1) * l * CV_PI / (2 * M));

              cos_mat.at<float>(idx + Point(m, n)) = cos(theta1) * cos(theta2);
           }
        }
     }
  }
  return cos_mat;
}

Mat IDCT_block(Mat f)
{
  Mat dst(f.size(), f.type());
  int N = f.rows, M = f.cols;

  for (int n = 0; n < N; n++) {
     for (int m = 0; m < M; m++) {
        float sum = 0;
        for (int k = 0; k < N; k++) {
           for (int l = 0; l < M; l++)
           {
              float theta1 = (float)((2 * n + 1) * k * CV_PI / (2 * N));
              float theta2 = (float)((2 * m + 1) * l * CV_PI / (2 * M));

              float ck = (k) ? sqrt(2.0f / N) : sqrt(1.0f / N);
              float cl = (l) ? sqrt(2.0f / M) : sqrt(1.0f / M);
              sum += ck * cl * f.at<float>(k, l) * cos(theta1) * cos(theta2);
           }
        }
        dst.at<float>(n, m) = sum;
     }
  }
  return dst;
}

Mat DCT_block(Mat g)
{
  Mat dst(g.size(), g.type());
  int N = g.rows, M = g.cols;

  for (int k = 0; k < N; k++) {
     for (int l = 0; l < M; l++) {
        float sum = 0;
        for (int n = 0; n < N; n++) {
           for (int m = 0; m < M; m++)
           {
              float theta1 = (float)(2 * n + 1) * k * CV_PI / (2 * N);
              float theta2 = (float)(2 * m + 1) * l * CV_PI / (2 * M);
              sum += g.at<float>(n, m) * cos(theta1) * cos(theta2);
           }
        }
        float ck = (k) ? sqrt(2.0f / N) : sqrt(1.0f / N);
        float cl = (l) ? sqrt(2.0f / M) : sqrt(1.0f / M);
        dst.at<float>(k, l) = ck * cl * sum;
     }
  }
  return dst;
}

Mat DCT_block(Mat g, Mat cos_mat, int dir)
{
  Mat dst(g.size(), g.type(), Scalar(0));
  int N = g.rows, M = g.cols;
  Vec2f CK(sqrt(1.0f / N), sqrt(2.0f / N));
  Vec2f CL(sqrt(1.0f / M), sqrt(2.0f / M));

  for (int k = 0; k < N; k++) {
     for (int l = 0; l < M; l++)
     {
        float ck = (k) ? CK[1] : CK[0];
        float cl = (l) ? CL[1] : CL[0];
        Point idx(l * M, k * N);
        for (int n = 0; n < N; n++) {
           for (int m = 0; m < M; m++)
           {
              float cos_value = cos_mat.at<float>(idx + Point(m, n));
              float coef = (dir == 0) ? g.at<float>(n, m) : g.at<float>(k, l);

              if (dir == 0) dst.at<float>(k, l) += ck * cl * coef * cos_value;
              else      dst.at<float>(n, m) += ck * cl * coef * cos_value;
           }
        }
     }
  }
  return dst;
}

void DCT_2D_fast(Mat img, Mat& dst, int N, int M, int dir)
{
  dst = Mat(img.size(), CV_32F);
  img.convertTo(img, CV_32F);
  Mat cos_mat = calc_cosine(N, M);

  for (int bi = 0; bi < img.rows; bi += N) {
     for (int bj = 0; bj < img.cols; bj += M)
     {
        Rect rect(Point(bj, bi), Size(M, N));
        Mat block = img(rect);
        Mat new_block = DCT_block(block, cos_mat, dir);
        new_block.copyTo(dst(rect));
     }
  }
}

void DCT_filtering(Mat img, Mat& dst, int N, int M)
{
  dst = Mat(img.size(), CV_32F);
  img.convertTo(img, CV_32F);

  Mat filter(N, M, CV_32F, Scalar(0));
  for (int i = 0; i < N / 2; i++)
     for (int j = 0; j < M / 2; j++)
        filter.at<float>(j, i) = 1;

  for (int bi = 0; bi < img.rows; bi += N) {
     for (int bj = 0; bj < img.cols; bj += M)
     {
        Rect rect(Point(bj, bi), Size(M, N));
        Mat new_block = DCT_block(img(rect));
        multiply(new_block, filter, new_block);

        IDCT_block(new_block).copyTo(dst(rect));
     }
  }
  dst.convertTo(dst, CV_8U);
}


int main()
{
  Mat image = imread("../../image/mine3.jpg", 0);
  CV_Assert(image.data);
  Mat  dst;

  DCT_filtering(image, dst, 8, 8);

  imshow("image", image);
  imshow("dct_fast_low", dst);
  waitKey();
  return 0;
}