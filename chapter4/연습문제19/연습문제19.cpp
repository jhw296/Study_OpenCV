#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main() {
	VideoCapture capture(0);
	CV_Assert(capture.isOpened());

	double fps = 15;
	int delay = cvRound(1000.0 / fps);
	Size size(640, 480);
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');

	capture.set(CAP_PROP_FRAME_WIDTH, size.width);
	capture.set(CAP_PROP_FRAME_HEIGHT, size.height);

	VideoWriter writer;
	writer.open("./flip_test.avi", fourcc, fps, size);
	CV_Assert(writer.isOpened());

	for (;;) {
		Mat frame, flip_frame;
		capture >> frame;

		flip(frame, flip_frame, 1);

		writer << flip_frame;
		writer.write(flip_frame);

		imshow("카메라 영상보기", frame);
		imshow("반전 카메라", flip_frame);
		if (waitKey(delay) >= 0)
			break;
	}
	return 0;
}