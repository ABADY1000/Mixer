#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "mixer.h"



void Mixer(
		rgb_video_t &main,
		rgba_video_t &overlay,
		rgb_video_t &output
		){


#pragma HLS INTERFACE axis off port=main name=MAIN
#pragma HLS INTERFACE axis off port=overlay name=OVERLAY
#pragma HLS INTERFACE axis off port=output name=OUTPUT


	rgb_pixel_t main_p;
	rgba_pixel_t overlay_p;
	rgb_pixel_t output_p;

	RGB* rgb;
	RGBA* rgba;

	static ap_uint<10> row = 0;
	static ap_uint<10> column = 0;

	MAIN_LOOP:
	while(1){
#pragma HLS PIPELINE II=1 enable_flush

		main.read(main_p);
		overlay.read(overlay_p);
		output_p.keep = 15;
		output_p.last = main_p.last;
		output_p.strb = main_p.strb;
		output_p.user = main_p.user;

		/*
		 * Alpha Mixing Logic
		 * */
		rgb = new RGB(main_p.data);
		rgba = new RGBA(overlay_p.data);
		output_p.data = rgb

		column += 1;
		if(main_p.last){
			row += 1;
			column = 0;
		}

		output.write(output_p);

		if(row == 5){
			row = 0;
			column = 0;
			break;
		}
	}

//	return 0;
}
