#ifndef AVCODEC_X86_HEVCDSP_H
#define AVCODEC_X86_HEVCDSP_H

struct SAOParams;
struct AVFrame;
struct UpsamplInf;
struct HEVCWindow;

// #define OPTI_ASM

void ff_hevc_put_hevc_epel_v2_14_sse( int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t _srcstride, int width, int height,  int mx, int my);
void ff_hevc_put_hevc_epel_v4_14_sse( int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t _srcstride, int width, int height,  int mx, int my);
void ff_hevc_put_hevc_epel_v8_14_sse( int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t _srcstride, int width, int height,  int mx, int my);

void ff_hevc_put_hevc_qpel_v4_14_sse(int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t _srcstride, int width, int height,  int mx, int my);
void ff_hevc_put_hevc_qpel_v8_14_sse(int16_t *dst, ptrdiff_t dststride, uint8_t *_src, ptrdiff_t _srcstride, int width, int height,  int mx, int my);

void ff_hevc_put_hevc_epel_hv_8_sse(int16_t *dst, ptrdiff_t dststride,
                                    uint8_t *_src, ptrdiff_t _srcstride, int width, int height, int mx, int my);


#define PEL_LINK_ASM(dst, idx1, idx2, idx3, name, D) \
dst[idx1][idx2][idx3] = ff_hevc_put_hevc_ ## name ## _ ## D ## _sse4
#define PEL_LINK_SSE(dst, idx1, idx2, idx3, name, D) \
dst[idx1][idx2][idx3] = ff_hevc_put_hevc_ ## name ## _ ## D ## _sse

#ifdef OPTI_ASM
#define PEL_LINK(dst, idx1, idx2, idx3, name, D) \
PEL_LINK_ASM(dst, idx1, idx2, idx3, name, D)
#else
#define PEL_LINK(dst, idx1, idx2, idx3, name, D) \
PEL_LINK_SSE(dst, idx1, idx2, idx3, name, D)
#endif


#define PEL_PROTOTYPE_ASM(name, D) \
void ff_hevc_put_hevc_ ## name ## _ ## D ## _sse4(int16_t *dst, ptrdiff_t dststride,uint8_t *_src, ptrdiff_t _srcstride,int width, int height, int mx, int my)

#define PEL_PROTOTYPE_SSE(name, D) \
void ff_hevc_put_hevc_ ## name ## _ ## D ## _sse(int16_t *dst, ptrdiff_t dststride,uint8_t *_src, ptrdiff_t _srcstride, int width, int height, int mx, int my)


#ifdef OPTI_ASM
#define PEL_PROTOTYPE(name, D) \
PEL_PROTOTYPE_ASM(name, D)
#else
#define PEL_PROTOTYPE(name, D) \
PEL_PROTOTYPE_SSE(name, D)
#endif

//IDCT functions

void ff_hevc_transform_skip_8_sse(uint8_t *_dst, int16_t *coeffs, ptrdiff_t _stride);


void ff_hevc_transform_4x4_luma_add_8_sse4(uint8_t *_dst, int16_t *coeffs, ptrdiff_t _stride);
void ff_hevc_transform_4x4_luma_add_10_sse4(uint8_t *_dst, int16_t *coeffs, ptrdiff_t _stride);

void ff_hevc_transform_4x4_add_8_sse4(uint8_t *_dst, int16_t *coeffs, ptrdiff_t _stride);
void ff_hevc_transform_4x4_add_10_sse4(uint8_t *_dst, int16_t *coeffs, ptrdiff_t _stride);
void ff_hevc_transform_8x8_add_8_sse4(uint8_t *_dst, int16_t *coeffs, ptrdiff_t _stride);
void ff_hevc_transform_8x8_add_10_sse4(uint8_t *_dst, int16_t *coeffs, ptrdiff_t _stride);
void ff_hevc_transform_16x16_add_8_sse4(uint8_t *_dst, int16_t *coeffs, ptrdiff_t _stride);
void ff_hevc_transform_16x16_add_10_sse4(uint8_t *_dst, int16_t *coeffs, ptrdiff_t _stride);
void ff_hevc_transform_32x32_add_8_sse4(uint8_t *_dst, int16_t *coeffs, ptrdiff_t _stride);
void ff_hevc_transform_32x32_add_10_sse4(uint8_t *_dst, int16_t *coeffs, ptrdiff_t _stride);

// MC functions
void ff_hevc_put_unweighted_pred_8_sse(uint8_t *_dst, ptrdiff_t _dststride,int16_t *src, ptrdiff_t srcstride,int width, int height);

void ff_hevc_weighted_pred_8_sse(uint8_t denom, int16_t wlxFlag, int16_t olxFlag,uint8_t *_dst, ptrdiff_t _dststride,int16_t *src, ptrdiff_t srcstride,int width, int height);
void ff_hevc_put_weighted_pred_avg_8_sse(uint8_t *_dst, ptrdiff_t _dststride,int16_t *src1, int16_t *src2, ptrdiff_t srcstride,int width, int height);

void ff_hevc_weighted_pred_avg_8_sse(uint8_t denom, int16_t wl0Flag, int16_t wl1Flag,int16_t ol0Flag, int16_t ol1Flag, uint8_t *_dst, ptrdiff_t _dststride,int16_t *src1, int16_t *src2, ptrdiff_t srcstride,int width, int height);

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
PEL_PROTOTYPE(pel_pixels2 ,  8);
PEL_PROTOTYPE(pel_pixels4 ,  8);
PEL_PROTOTYPE(pel_pixels8 ,  8);
PEL_PROTOTYPE(pel_pixels16,  8);

PEL_PROTOTYPE(pel_pixels2 , 10);
PEL_PROTOTYPE(pel_pixels4 , 10);
PEL_PROTOTYPE(pel_pixels8 , 10);

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
PEL_PROTOTYPE(epel_h2 ,  8);
PEL_PROTOTYPE(epel_h4 ,  8);
PEL_PROTOTYPE(epel_h8 ,  8);

PEL_PROTOTYPE(epel_h2 , 10);
PEL_PROTOTYPE(epel_h4 , 10);
PEL_PROTOTYPE(epel_h8 , 10);

PEL_PROTOTYPE(epel_v2 ,  8);
PEL_PROTOTYPE(epel_v4 ,  8);
PEL_PROTOTYPE(epel_v8 ,  8);

PEL_PROTOTYPE(epel_v2 , 10);
PEL_PROTOTYPE(epel_v4 , 10);
PEL_PROTOTYPE(epel_v8 , 10);

PEL_PROTOTYPE(epel_v2 , 14);
PEL_PROTOTYPE(epel_v4 , 14);
PEL_PROTOTYPE(epel_v8 , 14);

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
PEL_PROTOTYPE(qpel_h4 ,  8);
PEL_PROTOTYPE(qpel_h8 ,  8);

PEL_PROTOTYPE(qpel_h4 , 10);
PEL_PROTOTYPE(qpel_h8 , 10);

PEL_PROTOTYPE(qpel_v4 ,  8);
PEL_PROTOTYPE(qpel_v8 ,  8);

PEL_PROTOTYPE(qpel_v4 , 10);
PEL_PROTOTYPE(qpel_v8 , 10);

PEL_PROTOTYPE(qpel_v4 , 14);
PEL_PROTOTYPE(qpel_v8 , 14);

// SAO functions

void ff_hevc_sao_edge_filter_0_8_sse(uint8_t *_dst, uint8_t *_src, ptrdiff_t _stride, struct SAOParams *sao,int *borders, int _width, int _height, int c_idx, uint8_t vert_edge, uint8_t horiz_edge, uint8_t diag_edge);
void ff_hevc_sao_edge_filter_1_8_sse(uint8_t *_dst, uint8_t *_src, ptrdiff_t _stride, struct SAOParams *sao,int *borders, int _width, int _height, int c_idx, uint8_t vert_edge, uint8_t horiz_edge, uint8_t diag_edge);
void ff_hevc_sao_edge_filter_2_8_sse(uint8_t *_dst, uint8_t *_src, ptrdiff_t _stride, struct SAOParams *sao,int *borders, int _width, int _height, int c_idx, uint8_t vert_edge, uint8_t horiz_edge, uint8_t diag_edge);
void ff_hevc_sao_edge_filter_3_8_sse(uint8_t *_dst, uint8_t *_src, ptrdiff_t _stride, struct SAOParams *sao,int *borders, int _width, int _height, int c_idx, uint8_t vert_edge, uint8_t horiz_edge, uint8_t diag_edge);

void ff_hevc_sao_band_filter_0_8_sse(uint8_t *_dst, uint8_t *_src, ptrdiff_t _stride, struct SAOParams *sao, int *borders, int width, int height, int c_idx);
void ff_hevc_sao_band_filter_1_8_sse(uint8_t *_dst, uint8_t *_src, ptrdiff_t _stride, struct SAOParams *sao, int *borders, int width, int height, int c_idx);
void ff_hevc_sao_band_filter_2_8_sse(uint8_t *_dst, uint8_t *_src, ptrdiff_t _stride, struct SAOParams *sao, int *borders, int width, int height, int c_idx);
void ff_hevc_sao_band_filter_3_8_sse(uint8_t *_dst, uint8_t *_src, ptrdiff_t _stride, struct SAOParams *sao, int *borders, int width, int height, int c_idx);

//#ifdef SVC_EXTENSION
void ff_upsample_base_layer_frame_sse(struct AVFrame *FrameEL, struct AVFrame *FrameBL, short *Buffer[3], const int32_t enabled_up_sample_filter_luma[16][8], const int32_t enabled_up_sample_filter_chroma[16][4], struct HEVCWindow *Enhscal, struct UpsamplInf *up_info, int channel);
void ff_upsample_base_layer_frame_sse_v(struct AVFrame *FrameEL, struct AVFrame *FrameBL, short *Buffer[3], const int32_t enabled_up_sample_filter_luma[16][8], const int32_t enabled_up_sample_filter_chroma[16][4], struct HEVCWindow *Enhscal, struct UpsamplInf *up_info, int channel);
void ff_upsample_base_layer_frame_sse_h(struct AVFrame *FrameEL, struct AVFrame *FrameBL, short *Buffer[3], const int32_t enabled_up_sample_filter_luma[16][8], const int32_t enabled_up_sample_filter_chroma[16][4], struct HEVCWindow *Enhscal, struct UpsamplInf *up_info, int channel);
//#endif

#endif // AVCODEC_X86_HEVCDSP_H
