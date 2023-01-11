
#ifndef COLORS_H_
#define COLORS_H_

#include "ap_int.h"

class RGB{

	RGB(ap_uint<24> rgb){
		_red   = (rgb>>0 ) & 0xff;
		_green = (rgb>>8 ) & 0xff;
		_green = (rgb>>16) & 0xff;
		_rgb   = rgb;
	}

	RGB(uint32_t rgb){
		_red   = (rgb>>0 ) & 0xff;
		_green = (rgb>>8 ) & 0xff;
		_green = (rgb>>16) & 0xff;
		_rgb   = rgb;
	}

	RGB(ap_uint<8> r, ap_uint<8> g, ap_uint<8> b){
		_red   = r;
		_green = g;
		_green = b;
		_rgb   = (ap_uint<24>)r + ((ap_uint<24>)g)<<8 + ((ap_uint<24>)b)<<16;
	}

private:
	ap_uint<8>  _red;
	ap_uint<8>  _green;
	ap_uint<8>  _blue;
	ap_uint<24> _rgb;

public:
	ap_uint<8>  get_red();
	ap_uint<8>  get_green();
	ap_uint<8>  get_blue();
	ap_uint<24> get_rgb();
};

class RGBA : public RGB{

	RGBA(ap_uint<32> rgba): RGB((ap_uint<24>)(rgba&0x00ffffff)){
		_alpha = (rgba>>24) & 0xff;
		_rgba  = rgba;
	}

	RGBA(uint32_t rgba): RGB((ap_uint<24>)(rgba&0x00ffffff)){
		_alpha = (rgba>>24) & 0xff;
		_rgba  = rgba;
	}

private:
	ap_uint<8> _alpha;
	ap_uint<32>_rgba;

public:
	ap_uint<8>  get_alpha();
	ap_uint<32> get_rgba();
	RGB mix(RGB rgb);
};


#endif
