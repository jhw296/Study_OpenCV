#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Rect_<int> rect1(30, 40, 100, 200);
	Point2d pt1(10, 10);
	Size2d sz(20, 30);
	
	Rect rect_point = rect1 + (Point)pt1;
	Rect rect_size = rect1 + (Size)sz;

	cout << "rect_point = " << rect_point.tl() << " " << rect_point.br() << endl;
	cout << "rect_size = " << rect_size.size() << endl;

	return 0;
}