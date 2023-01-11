
#include <iostream>
#include "hls_stream.h"
#include "ap_axi_sdata.h"
#include "mixer.h"
#include <stdlib.h>


//int main(int argc, char** argv){
//
//	cv::Mat array;
//	array = cv::imread("./bird.png", cv::IMREAD_COLOR);
//
//	cv::imshow("Window", array);
//	cv::waitKey(100);
//	cv::destroyAllWindows();
//
//
//	std::cout << "Test Bench Completed Successfully\n";
//	return 0;
//}

int main(){

	rgb_pixel_t *one;
	rgba_pixel_t *two;
	rgb_video_t idata1;
	rgba_video_t idata2;
	hls::stream<int> tdata1;
	hls::stream<int> tdata2;
	rgb_pixel_t out;
	rgb_video_t odata;

	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			one = new rgb_pixel_t();
			one->data = std::rand() % 256;
			one->keep = 15;
			one->strb = 15;
			one->user = (i == 0 && j == 0) ? 1 : 0;
			one->last = j == 4 ? 1 : 0;

			idata1.write(*one);
			tdata1.write(one->data);

			two = new rgba_pixel_t();
			two->data = std::rand() % 256;
			two->keep = 15;
			two->strb = 15;
			two->user = (i == 0 && j == 0) ? 1 : 0;
			two->last = j == 4 ? 1 : 0;

			idata2.write(*two);
			tdata2.write(two->data);
		}
	}

	if(idata1.empty()) std::cout << "Error in the empty function \n";

	Mixer(idata1, idata2, odata);

	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			out = odata.read();

			int a = tdata1.read();
			int b = tdata2.read();
			int c = a ^ b;
			if(out.data != c){
				std::cout << "Test Failed !!!\n" << "Data1 = " << a << "\nData2 = " << b;
				std::cout << "\nResult = " << c << "\nMixer Output = " << out.data << "\n";
				return 1;
			}
		}
	}

	std::cout << "Test Bench Completed Successfully\n";
	return 0;
}
