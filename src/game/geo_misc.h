#ifndef GEO_MISC_H
#define GEO_MISC_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>

#ifndef GBI_FLOATS
extern void make_vertex(
    Vtx *vtx, s32 n, s16 x, s16 y, s16 z, s16 tx, s16 ty, u8 r, u8 g, u8 b, u8 a
);
#else
extern void make_vertex(
    Vtx *vtx, s32 n, f32 x, f32 y, f32 z, s16 tx, s16 ty, u8 r, u8 g, u8 b, u8 a
);
#endif
extern s16 round_float(f32);
extern Gfx *geo_exec_cake_end_screen(s32 callContext, struct GraphNode *node, UNUSED f32 mtx[4][4]);

#define gLoadBlockTexture(dl, width, height, format, image)                                                  \
{                                                                                                            \
    gDPSetTextureImage((dl), (format), G_IM_SIZ_16b, 1, (image));                                            \
    gDPTileSync((dl));                                                                                       \
    gDPSetTile((dl), (format), G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, \
               G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);                                                      \
    gDPLoadSync((dl));                                                                                       \
    gDPLoadBlock((dl), G_TX_LOADTILE, 0, 0, (width) * (height) - 1, CALC_DXT((width), G_IM_SIZ_16b_BYTES))   \
}

#endif // GEO_MISC_H
