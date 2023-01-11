
#ifndef MIXER_H_
#define MIXER_H_

#include "ap_axi_sdata.h"
#include "hls_stream.h"

typedef ap_axiu<24,1,1,1> rgb_pixel_t;
typedef ap_axiu<32,1,1,1> rgba_pixel_t;
typedef hls::stream<rgb_pixel_t> rgb_video_t;
typedef hls::stream<rgba_pixel_t> rgba_video_t;


#define MAX_WIDTH 640
#define MAX_HEIGT 480


void Mixer(rgb_video_t &main,rgba_video_t &overlay,rgb_video_t &output);


#endif // MIXER_H_
