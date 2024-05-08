#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> 

#include <cmath>
#include <iostream>

using namespace cv;
using namespace std;


int findBiggestSize(string letters, double font_size) {
	
	int baseline = 0;

	Size text_size;
	int biggest_height = 0;
	int biggest_width = 0;

	for (char& c : letters) {
		text_size = getTextSize(string(1, c), FONT_HERSHEY_PLAIN, font_size, 1, &baseline);
		if (text_size.height > biggest_height) {
			biggest_height = text_size.height;
		}
		if (text_size.width > biggest_width) {
			biggest_width = text_size.width;
		}
	}

	return max(biggest_height, biggest_width);
}


Mat createImageLetter(int width, int height, char letter, double font_size) {
	Mat img(height, width, CV_8UC3, Scalar(0, 0, 0));
	Point org(0,width-1);
	putText(img, string(1, letter), org, FONT_HERSHEY_PLAIN, font_size, Scalar(255, 255, 255), 1);
	cvtColor(img, img, COLOR_BGR2GRAY);
	int k = waitKey(0);
	return img;
}

struct ascii_letter {
	char letter;
	double val;
};


bool compare_ascii_letter(ascii_letter a1, ascii_letter a2) {
	return (a1.val < a2.val);
}


int main() {

	string letters = " _.,-+:lcba!?0123456789$#";
	double font_size = 0.4;

	int jump = findBiggestSize(letters, font_size);

	Range rows(0, jump);
	Range cols(0, jump);
	vector<ascii_letter> ascii_letters;
	for (char& c : letters) {
		ascii_letter tmp;
		tmp.letter = c;
		Mat letter_image = createImageLetter(jump, jump, c, font_size);
		tmp.val = sum(letter_image(rows, cols))[0] / (jump * jump);
		ascii_letters.push_back(tmp);
	}

	sort(ascii_letters.begin(), ascii_letters.end(), compare_ascii_letter);

	string img_path = "input_images\\img.png";
	Mat input_img;
	cvtColor(imread(img_path, IMREAD_COLOR), input_img, COLOR_BGR2GRAY);

	int width = input_img.size[1];
	int height = input_img.size[0];
	Mat img(height, width, CV_8UC3, Scalar(0, 0, 0));

	cout << input_img.channels() << endl;

	for (int i = 0; i < height-jump+1; i+=jump) {
		for (int j = 0; j < width-jump+1; j+=jump) {
			Range rows(i, i + jump);
			Range cols(j, j + jump);
			int mean = floor((sum(input_img(rows, cols))[0]) / (jump * jump));

			double tmp = (mean / 255.0) * ascii_letters.size();
			int letter_selector = round(tmp);

			Point org(j+jump/2, i+jump/2);
			string selected_letter(1, ascii_letters[letter_selector].letter);
			putText(img, selected_letter, org, FONT_HERSHEY_PLAIN, font_size, Scalar(255, 255, 255), 1);
		}
	}

	imwrite("output_images\\img.png", img);
	
	return 0;
}