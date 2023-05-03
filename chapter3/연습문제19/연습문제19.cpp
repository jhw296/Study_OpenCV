#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat_ <int> m(10, 15, 100);
	Range r1(1, 5), r2(3, 8), r3(3, 7), r4(5, 10), r5(5, 9), r6(8, 14);
	Mat m1, m2, m3;
	m1 = m(r1, r2);
	m2 = m(r3, r4);
	m3 = m(r5, r6);
	m1.setTo(200);
	m2.setTo(555);
	m3.setTo(300);
	cout << m << endl;

	return 0;
}