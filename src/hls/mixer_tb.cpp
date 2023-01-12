
#include <iostream>
#include "hls_stream.h"
#include "ap_axi_sdata.h"
#include "mixer.h"
#include "colors.h"
#include <stdlib.h>
#include <math.h>

int main(){

	rgb_pixel_t *one;
	rgba_pixel_t *two;
	rgb_video_t idata1;
	rgba_video_t idata2;
	hls::stream<uint32_t> tdata1;
	hls::stream<uint32_t> tdata2;
	rgb_pixel_t out;
	rgb_video_t odata;

	RGB* rgb;
	RGBA* rgba;
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			one = new rgb_pixel_t();
			rgb = new RGB(255,255,255);
			one->data =rgb->get_rgb();
			one->keep = 7;
			one->strb = 7;
			one->user = (i == 0 && j == 0) ? 1 : 0;
			one->last = j == 4 ? 1 : 0;

			idata1.write(*one);
			tdata1.write(one->data);

			two = new rgba_pixel_t();
			rgba = new RGBA(128,128,128, (i+j)%2 ? 255 : 0);
			two->data = rgba->get_rgba();
			two->keep = 15;
			two->strb = 15;
			two->user = (i == 0 && j == 0) ? 1 : 0;
			two->last = j == 4 ? 1 : 0;

			idata2.write(*two);
			tdata2.write(two->data);
		}
	}

//	if(idata1.empty()) std::cout << "Error in the empty function \n";

	Mixer(idata1, idata2, odata);

	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			out = odata.read();

//			RGB a = RGB(tdata1.read());
//			RGBA b = RGBA(tdata2.read());
//			RGB c = b.mix(a);
//			if(out.data != c.get_rgb()){
			int odd = (i+j)%2;
			rgb = new RGB(out.data);
			int err = odd ? rgb->get_red()-255 : rgb->get_red()-128;
			if(abs(err) > 1){
//				std::cout << "Test Failed !!!\n" << "Data1 = " << a.get_rgb() << "\nData2 = " << b.get_rgba();
//				std::cout << "\nResult = " << c.get_rgb() << "\nMixer Output = " << out.data << "\n";
				std::cout << "Test Failed !!!\n" << "i = " << i << "\nj = " << j;
				std::cout << "\nShould be = " << (odd ? 255 : 128) << "\nMixer Output = " << out.data << "\n";
				return 1;
			}
		}
	}

	std::cout << "Test Bench Completed Successfully\n";
	return 0;
}
