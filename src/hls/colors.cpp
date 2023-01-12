

#include "colors.h"
#include "ap_int.h"
#include "mixer.h"

ap_uint<8> blind(ap_uint<8> a, ap_uint<8> b, ap_uint<8> alpha);

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
	RGB rgb_new (
					blind(get_red(), rgb.get_red(), get_alpha()),
					blind(get_green(), rgb.get_green(), get_alpha()),
					blind(get_blue(), rgb.get_blue(), get_alpha())
				);
	return rgb_new;
}

ap_uint<8> blind(ap_uint<8> overlay, ap_uint<8> background, ap_uint<8> alpha){
	return ((background*alpha)>>8) + ((overlay*(255-alpha))>>8);
}
