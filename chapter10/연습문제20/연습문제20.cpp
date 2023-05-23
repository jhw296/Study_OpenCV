#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
    Size boardSize(8, 7), imageSize;
    float squareSize = 1.f;

    VideoCapture capture(0);
    if (!capture.isOpened()) {
        cout << "Failed to open the camera" << endl;
        return -1;
    }

    Mat image;
    capture.read(image);
    imageSize = image.size();

    vector<Point2f> imgPoints;
    vector<Point3f> objPoints;

    while (true) {
        capture.read(image);

        Mat gray;
        cvtColor(image, gray, COLOR_RGB2GRAY);
        bool found = findChessboardCorners(gray, boardSize, imgPoints);

        if (found) {
            cornerSubPix(gray, imgPoints, Size(11, 11), Size(-1, -1),
                TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 30, 0.1));

            drawChessboardCorners(image, boardSize, imgPoints, found);
        }

        imshow("Original", image);

        int key = waitKey(1);
        if (key == 27)
            break;
        else if (key == 'c' && found) {
            objPoints.clear();

            for (int i = 0; i < boardSize.height; i++)
                for (int j = 0; j < boardSize.width; j++)
                    objPoints.push_back(Point3f(j * squareSize, i * squareSize, 0));

            vector<vector<Point2f>> imagePoints(1, imgPoints);
            vector<vector<Point3f>> objectPoints(1, objPoints);

            vector<Mat> rvecs, tvecs;
            Mat cameraMatrix, distCoeffs;
            Mat undistorted;

            double rms = calibrateCamera(objectPoints, imagePoints, imageSize,
                cameraMatrix, distCoeffs, rvecs, tvecs);

            undistort(image, undistorted, cameraMatrix, distCoeffs);

            cout << "cameraMatrix " << endl << cameraMatrix << endl << endl;
            printf("RMS error reported by calibrateCamera: %g\n", rms);

            imshow("Undistorted", undistorted);
        }
    }

    return 0;
}