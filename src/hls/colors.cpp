

#include "ap_int.h"
#include "mixer.h"

/*
 * -- RGB -- Functions Impl
 * */
ap_uint<8> RGB::get_red(){

	return _red;
}

ap_uint<8> RGB::get_green(){

	return _green;
}

ap_uint<8> RGB::get_blue(){

	return _blue;
}

ap_uint<24> RGB::get_rgb(){

	return _rgb;
}


/*
 *  -- RGBA  -- Functions Impl
 * */
ap_uint<8>  RGBA::get_alpha(){
	return _alpha;
}

ap_uint<32> RGBA::get_rgba(){
	return _rgba;
}

RGB RGBA::mix(RGB rgb){
	RGB rgb_new = new RGB(

			);
	rgb.get_red()
}


