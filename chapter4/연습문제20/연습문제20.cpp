#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main() {
	
	Mat src = imread("../../image/mine1.jpg", IMREAD_COLOR);

	Size image_size = src.size();
	int depth = src.depth();
	Mat image_data = src;

	FileStorage fs("./image.xml", FileStorage::WRITE);
	
	fs << "image_size" << image_size;
	fs << "depth" << depth;
	fs << "image_data" << image_data;

	fs.release();
	return 0;
}