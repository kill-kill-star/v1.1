#include<opencv2/opencv.hpp>

using cv::Mat;

void PicturePrint(std::string PicturePath) {
	Mat src = cv::imread(PicturePath);
	Mat dst;
	if (src.empty()) {
		std::cout << PicturePath;
		exit(0);
	}
	int height = src.rows;
	int width = src.cols;
	int key;
	if (height >= 800) {
		cv::resize(src, dst, cv::Size(), 0.5, 0.5);
		src = dst;
	}
	cv::namedWindow("yeah~~");
	cv::imshow("yeah~~", src);
	key = cv::waitKey(0);
	if (key == 27) exit(0);//按下esc键直接退出
}