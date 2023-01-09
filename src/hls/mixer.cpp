

#include "ap_axi_sdata.h"
#include "hls_stream.h"

typedef ap_axis<32,1,0,0> video;
typedef ap_axis<24,1,0,0> result_video;
typedef hls::stream< video > istream;
typedef hls::stream< result_video > ostream;


int Mixer(istream &a, istream &b, ostream &c){

#pragma HLS INTERFACE s_axilite port=return bundle=cmd

#pragma HLS INTERFACE axis off port=a name=main
#pragma HLS INTERFACE axis off port=b name=overlay
#pragma HLS INTERFACE axis off port=c name=output


	video tmp1;
	video tmp2;
	result_video tmp3;
	static ap_uint<10> row = 0;
	static ap_uint<10> column = 0;

//	MAIN_LOOP:while(1){
		a.read(tmp1);
		b.read(tmp2);
		tmp3.data = tmp1.data.to_int() ^ tmp2.data.to_int();
		tmp3.keep = 7;
		tmp3.last = tmp1.last;
		tmp3.strb = tmp1.strb;
		tmp3.user = tmp1.user;
//		column += 1;
//		if(tmp1.last){
//			column += 1;
//		}
		c.write(tmp3);

//		if(row == 10 && column == 10){
//			break;
//		}
//	}

	return 0;
}
