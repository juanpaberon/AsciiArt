#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> 

#include <cmath>
#include <iostream>

using namespace cv;
using namespace std;

int main() {

	string letters = " _.,-++:lcba!?0123456789$#@Ñ";

	string img_path = "input_images\\img.png";
	Mat input_img;
	cvtColor(imread(img_path, IMREAD_COLOR), input_img, COLOR_BGR2GRAY);

	Mat img(500, 500, CV_8UC3, Scalar(0, 0, 0));

	int jump = 8;

	cout << input_img.channels() << endl;

	for (int i = 0; i < 500-jump+1; i+=jump) {
		for (int j = 0; j < 500-jump+1; j+=jump) {
			Range rows(i, i + jump);
			Range cols(j, j + jump);
			int mean = floor((sum(input_img(rows, cols))[0]) / (jump * jump));

			double tmp = (mean / 255.0) * letters.size();
			int letter_selector = round(tmp);

			Point org(j+jump/2, i+jump/2);
			string selected_letter(1, letters[letter_selector]);
			putText(img, selected_letter, org, FONT_HERSHEY_PLAIN, 0.4, Scalar(255, 255, 255), 1);
		}
	}

	imwrite("output_images\\img.png", img);

	return 0;
}