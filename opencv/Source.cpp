#include <opencv2/core/core.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <ctime>


# define M_PIl 3.141592653589793238462643383279502884L
//#pragma warning(default:4716)

using namespace cv;
using namespace std;
/*
int main()
{
	int height = 520;
	int width = 1500;
	Mat img(height, width, CV_8UC3);
	Point textOrg(10, img.rows / 10);
		int fontFace = FONT_HERSHEY_TRIPLEX;
		double fontScale = 2;
		Scalar color(0, 0, 0);
		putText(img, "smallwhitesaltfatflashlightpussy", textOrg, fontFace, fontScale, color);
		namedWindow("Hello world", 0);
		imshow("HelloWorld", img);
		waitKey(0);
		return 0;
}
*/
Mat img;


string input()
{
	setlocale(LC_ALL, "Russian");
	string filename;
	cout << "\nВведите название файла и нажмите enter" << endl;
	cout << "file.jpg" << endl;
	cout << "sf.jpg" << endl;
	cout << "sf2.jpg" << endl;
	cout << "road.png" << endl;
	cout << "lisii.png" << endl;
	cout << "jir.jpg" << endl;
	cout << "jir2.jpg" << endl;

	//cin.getline(filename, 80);
	cin >> filename;
	//string path = "/x64/Debug/";
	//string filename = path + filename1;
	cout << "\nОткрыть файл: ";
	cout << filename << endl;

	return filename;

}

string inputVid()
{
	setlocale(LC_ALL, "Russian");
	string filename;
	cout << "\nВведите название файла и нажмите enter" << endl;
	cout << "video.mp4" << endl;
	cout << "video1.mp4" << endl;

	//cin.getline(filename, 80);
	cin >> filename;
	cout << "\nОткрыть файл: ";
	cout << filename << endl;

	return filename;
}

string VideoCap() {
	//Open the default video camera
	VideoCapture cap(0);

	// if not success, exit program
	if (cap.isOpened() == false)
	{
		cout << "Cannot open the video camera" << endl;
		cin.get(); //wait for any key press
	}

	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video



	string window_name = "My Camera Feed";
	namedWindow(window_name); //create a window called "My Camera Feed"
	auto fps = cap.get(CAP_PROP_FPS); // frames per seconds
	auto delay = 1000 / fps;
	while (true)
	{
		Mat frame;
		auto time = clock();
		bool bSuccess = cap.read(frame); // read a new frame from video 

		//Breaking the while loop if the frames cannot be captured
		if (bSuccess == false)
		{
			cout << "Video camera is disconnected" << endl;
			cin.get(); //Wait for any key press
			break;
		}


		//show the frame in the created window
		imshow(window_name, frame);

		if (frame.channels() != 1) cvtColor(frame, frame, COLOR_RGB2GRAY);
		Mat x, y;
		Sobel(frame, x, CV_16S, 1, 0);
		Sobel(frame, y, CV_16S, 0, 1);
		// модуль собеля
		convertScaleAbs(x, x);
		convertScaleAbs(y, y);
		addWeighted(x, 0.5, y, 0.5, 0, frame); //совмещаем картинки

		imshow("sobel", frame);
		// скорость видео
		double time_work = (clock() - time) * 1000 / CLOCKS_PER_SEC;
		if (time_work > delay - 1) time_work = 1;
		else time_work = delay - time_work;


		////  если обработка собелем больше чем задержка тогда получится отрицательное значение(ошибка)
		//int vidos = waitKey(time_work);
		//if (vidos >= 0) break;

		//wait for for 10 ms until any key is pressed.  
		//If the 'Esc' key is pressed, break the while loop.
		//If the any other key is pressed, continue the loop 
		//If any key is not pressed withing 10 ms, continue the loop 
		if (waitKey(10) == 27)
		{
			cout << "Esc key is pressed by user. Stoppig the video" << endl;
			break;
		}
	}
	cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;
	cout << "Задержка в мс = " << delay << endl;
	waitKey(0);
	return 0;
}

string VideoCont()
{
	//char filename[100]; // Figyres.mp4 èëè Figyres_same_colour.mp4
	//cout << "Введите имя файла, который хотите проанализировать, и нажмите Enter" << endl;
	//cin.getline(filename, 100);
	//cout << "Открыт файл ";
	//cout << filename << endl;

	VideoCapture cap(0);
	if (!cap.isOpened()) { cout << "Ошибка открытия файла"; return 0; }
	Mat im;
	for (; ;)
	{
		Mat mat, frame;
		cap >> frame;
		mat = frame;
		if (mat.empty()) break;

		cvtColor(mat, mat, COLOR_RGB2GRAY);
		GaussianBlur(mat, mat, Size(3, 3), 0);
		Canny(mat, mat, 50, 100);

		vector<vector<Point>> points;
		auto kn = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(mat, mat, kn);
		findContours(mat, points, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);


		for (int i = 0; i < points.size(); i++)
		{
			vector<Point> _points;
			double len = arcLength(Mat(points[i]), true);
			if (len < 30) continue;
			approxPolyDP(points[i], _points, len * 0.02, true);
			Moments m = moments(_points);
			Point centm(m.m10 / m.m00, m.m01 / m.m00);
			printf("Контур № %d: центр масс - х = %.2f, y = %.2f \n", i, m.m10 / m.m00, m.m01 / m.m00);

			// 4 вершины - прямоугольник
			if (_points.size() == 4)
			{
				drawContours(frame, vector<vector<Point>>{_points}, 0, Scalar(255, 255, 0), 2);
				drawMarker(frame, centm, Scalar(255, 255, 255));
				continue;
			}
			// 3 вершины - треугольник
			if (_points.size() == 3)
			{
				drawContours(frame, vector<vector<Point>>{_points}, 0, Scalar(0, 255, 255), 2);
				drawMarker(frame, centm, Scalar(255, 255, 255));
				continue;
			}
			// если не прямоугольник и не треугольник
			if (_points.size() > 4 || _points.size() < 3)
			{
				Point2f cent;
				float rad;
				minEnclosingCircle(points[i], cent, rad);
				if ((2 * rad * M_PIl - len) * (2 * rad * M_PIl - len) < len * 0.2)
				{
					circle(frame, cent, rad, Scalar(0, 255, 0), 2);
				}
				continue;
			}
		}
		imshow("Распознавание", frame);
		if (waitKey(30) >= 0) break;
	}
	return 0;
}

string Image()
{

	string file = input();
	Mat img = imread(file, 1);
	string source_window = file;

	namedWindow(source_window, WINDOW_GUI_EXPANDED);
	imshow(source_window, img);

	Mat src_gray;
	Mat canny_output;

	cvtColor(img, src_gray, COLOR_RGB2GRAY); // перводит изображение в черно-белое
	imwrite("cvtColor.jpg", src_gray); //создает файл черно-белого изображения
	blur(src_gray, src_gray, Size(10, 10)); //размывает изображение
	imwrite("blur.jpg", src_gray); // создает файл размытого изображения

	double otsu_tresh_val = threshold(src_gray, img, 0, 255, THRESH_BINARY | THRESH_OTSU); //определяет яркость серого изображения
	//double high_tresh_val = otsu_tresh_val, lower_tresh_val = otsu_tresh_val * 0.5;
	double high_tresh_val = 40, lower_tresh_val = 40 * 0.5; //определяет максимумы и минимумы
	cout << "Фильтрация " << otsu_tresh_val << endl;

	Canny(src_gray, canny_output, lower_tresh_val, high_tresh_val, 3); // алгоритм для работы трехканальное изображение

	string source_grey_window = "Серое изображение";
	namedWindow(source_grey_window, WINDOW_GUI_EXPANDED);
	imshow(source_grey_window, canny_output);
	//dfd
	imwrite("canny_output.jpg", canny_output); //сохраняет и открывает обработанное изображение

	RNG rng(12345); //задает рандомные цвета из диапозона ниже
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0)); //

	vector<Moments>mu(contours.size()); //создается вектор моментов, куда передается количество контуров, которое зависит от изображения
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false); //часть вектора передается в столбцы массива mu
	}

	vector<Point2f>mc(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00); // показывается x y векторы
	}

	for (int i = 0; i < contours.size(); i++)
	{
		printf("Контур № %d: центр масс - x = %.2f y = %.2f; длина - %.2a \n", i, mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00, arcLength(contours[i], true)); //2f - количество знаков после запятой, типа float
	}

	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3); //CV_8UC3 - изображение без знака с 3 каналами

	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)); //указывает диапозон цвета, откуда будут браться случайные значения
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point()); //передается картинка, hierarchy - возвращает иерархию внешних контуров и отверстий. 
																				//элементы 2 и 3 иерархии [idx] имеют не более одного из них, не равного -1: то есть 
																				//у каждого элемента либо нет родителя или потомка, либо родителя, но нет потомка, либо потомка, но нет родителя
																				//Элемент с родителем, но без потомка, будет границей отверстия
		circle(drawing, mc[i], 4, color, -1, 5, 0); //выбирается изображение, центр масс, 4 - радиус, цвета, толщина
	}

	namedWindow("Contours", WINDOW_GUI_EXPANDED);
	imshow("Contours", drawing);

	waitKey(0);
	return 0;
}

string Video()
{
	string file = inputVid();
	VideoCapture cap(file);
	if (!cap.isOpened()) {
		cout << "Ошибка открытия файла";
	}

	Mat im;
	for (;;) {
		Mat mat, frame;
		cap >> frame;
		mat = frame;
		if (mat.empty()) break;

		imshow("Распознавание", frame);
		if (waitKey(30) >= 0) break;
	}
	waitKey(0);
	return 0;

}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "С чем работаем:\n" << endl;
	cout << "image" << endl;
	cout << "video" << endl;
	cout << "videoCap" << endl;
	cout << "videoCont" << endl;


	string choose;
	cin >> choose;
	bool check = true;
	while (check == true)
	{
		if (choose == "image") {
			check = false;
			Image();
		}
		if (choose == "video") {
			check = false;
			//Video();
			Video();
		}
		if (choose == "videoCap") {
			check = false;
			//Video();
			VideoCap();
		}
		if (choose == "videoCont") {
			check = false;
			//Video();
			VideoCont();
		}
		
		else {
			check = true;
			cout << "повторите попытку." << endl;
		}
	}
	return 0;
}
