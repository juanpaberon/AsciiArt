#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> 

using namespace cv;
using namespace std;

int main() {
	Mat img(500, 500, CV_8UC3, Scalar(0, 0, 0));

	int jump = 10;

	for (int i = 0; i < 500; i+=jump) {
		for (int j = 0; j < 500; j+=jump) {
			Point org(i, j);
			putText(img, "G", org, FONT_HERSHEY_SIMPLEX, 0.3, Scalar(255, 255, 255), 1);
		}
	}

	imshow("black image", img);

	waitKey(0);

	return 0;
}