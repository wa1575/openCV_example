#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int x, y;
string szTitle = "창 제어";
string szTitle2 = "Selection";
Mat m2;

void onChange(int value, void* userdata) {
	Mat* m = (Mat*)userdata;
	m2 = *m - 130 + value;
	imshow(szTitle, m2);
}
//클릭한 위치의 이미지 잘라서 저장하기 
void onMouse(int event, int x, int y, int flag, void* param) {
	Mat* m = (Mat*)param;
	if (event == EVENT_MOUSEWHEEL) {
		Rect rect = getWindowImageRect(szTitle);
		resizeWindow(szTitle, rect.width + 10, rect.height + 10);
	}
	else if (event == EVENT_MOUSEMOVE) {//LBUTTONDOWN으로 하면 클릭으로 변경
		int ymin = (y - 50) < 0 ? 0 : (y - 50);
		int ymax = (y + 50) > m->size().height ? m->size().height : (y + 50);
		int xmin = (x - 50) < 0 ? 0 : (x - 50);
		int xmax = (x + 50) > m->size().width ? m->size().width : (x + 50);
		Mat m2 = (*m)(Range(ymin, ymax), Range(xmin, xmax));
		imshow(szTitle2, m2);
	}
}

int main() {
	int value = 128;
	Mat image1 = imread("D:/Project/clockwerk.jpg", IMREAD_GRAYSCALE);

	namedWindow(szTitle, WINDOW_NORMAL);
	namedWindow(szTitle2, WINDOW_NORMAL); //새로 생성
	setMouseCallback(szTitle, onMouse, &image1);//&image1 추가하면 에러 없어짐
	createTrackbar("화면 크기", szTitle, &value, 255, onChange, &image1);
	imshow(szTitle, image1);

	waitKey();
	if (!m2.empty()) //m2가 있는 경우에만 저장할 것이다. 
		imwrite("test.jpg", m2); //현재 위치에 m2를 저장 
	return 0;
}
