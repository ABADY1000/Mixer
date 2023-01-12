
#ifndef COLORS_H_
#define COLORS_H_

#include "ap_int.h"

class RGB{

public:
	RGB(ap_uint<24> rgb){
		_red   = (ap_uint<8>)(rgb>>0 ) & (ap_uint<8>)0xff;
		_green = (ap_uint<8>)(rgb>>8 ) & (ap_uint<8>)0xff;
		_blue = (ap_uint<8>)(rgb>>16) & (ap_uint<8>)0xff;
		_rgb   = rgb;
	}

#ifndef __SYNTHESIS__
//	RGB(uint32_t rgb){
//		_red   = (rgb>>0 ) & 0xff;
//		_green = (rgb>>8 ) & 0xff;
//		_green = (rgb>>16) & 0xff;
//		_rgb   = rgb&0x00ffffff;
//	}
#endif

	RGB(ap_uint<8> r, ap_uint<8> g, ap_uint<8> b){
		_red   = r;
		_green = g;
		_blue = b;
		std::cout << "R=" << (ap_uint<24>)r << "\nG=" << ((ap_uint<24>)g)<< 8 << "\n";
		_rgb   = (ap_uint<24>)r + (((ap_uint<24>)g)<<8) + (((ap_uint<24>)b)<<16);
		std::cout << "RGB=" << _rgb << "\n";

	}

	ap_uint<8>  get_red();
	ap_uint<8>  get_green();
	ap_uint<8>  get_blue();
	ap_uint<24> get_rgb();

private:
	ap_uint<8>  _red;
	ap_uint<8>  _green;
	ap_uint<8>  _blue;
	ap_uint<24> _rgb;

};



class RGBA : public RGB{

public:
	RGBA(ap_uint<32> rgba): RGB((ap_uint<24>)(rgba&0x00ffffff)){
		_alpha = (rgba>>24) & 0xff;
		_rgba  = rgba;
	}

	RGBA(ap_uint<8> r, ap_uint<8> g, ap_uint<8> b, ap_uint<8> a): RGB(r,g,b){
		_alpha = a;
		_rgba = (ap_uint<32>)r + (((ap_uint<32>)g)<<8) + (((ap_uint<32>)b)<<16) + (((ap_uint<32>)a)<<24);
	}

#ifndef __SYNTHESIS__
//	RGBA(uint32_t rgba): RGB((ap_uint<24>)(rgba&0x00ffffff)){
//		_alpha = (rgba>>24) & 0xff;
//		_rgba  = rgba;
//	}
#endif

	ap_uint<8>  get_alpha();
	ap_uint<32> get_rgba();
	RGB mix(RGB rgb);

private:
	ap_uint<8> _alpha;
	ap_uint<32>_rgba;

};


#endif
