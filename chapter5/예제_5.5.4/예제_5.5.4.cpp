#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
    Matx<ushort, 5, 4> pts;
    Mat_<int> sizes, sort_idx;
    vector<Rect> rects;
    randn(pts, Scalar(200), Scalar(100));

    cout << "---------------------------" << endl;
    cout << "        랜덤 사각형 정보       " << endl;
    cout << "---------------------------" << endl;
    for (int i = 0; i < pts.rows; i++) {
        Point pt1(pts(i, 0), pts(i, 1));
        Point pt2(pts(i, 2), pts(i, 3));
        rects.push_back(Rect(pt1, pt2));
        sizes.push_back(rects[i].area());
        cout << format("rects[%d] = ", i) << rects[i] << endl;
    }

    sortIdx(sizes, sort_idx, SORT_EVERY_COLUMN);

    cout << endl << "크기순 정렬 사각형 정보 \t크기" << endl;
    cout << "---------------------------" << endl;
    for(int i = 0; i < rects.size(); i++) {
        int idx = sort_idx(i);
        cout << rects[idx] << "\t" << sizes(idx) << endl;
    }
    cout << "---------------------------" << endl;
    return 0;
}