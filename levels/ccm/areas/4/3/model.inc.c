static const Lights1 slider_JumpMaterial_v4_lights = gdSPDefLights1(
	0x3F, 0x3F, 0x0,
	0xFF, 0xFF, 0x0, 0x28, 0x28, 0x28);

static const Vtx slider_8_dl_mesh_vtx_0[4] = {
	{{ {1128, 641, -4401}, 0, {-4, 996}, {229, 124, 0, 255} }},
	{{ {1128, 641, -5220}, 0, {2023, 1008}, {229, 124, 0, 255} }},
	{{ {907, 593, -5220}, 0, {2023, -10}, {229, 124, 0, 255} }},
	{{ {907, 593, -4401}, 0, {-4, -10}, {229, 124, 0, 255} }},
};

static const Gfx slider_8_dl_mesh_tri_0[] = {
	gsSPVertex(slider_8_dl_mesh_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(2, 3, 0, 0),
	gsSPEndDisplayList(),
};

static const Gfx mat_slider_JumpMaterial_v4[] = {
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPSetLights1(slider_JumpMaterial_v4_lights),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 128),
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b_LOAD_BLOCK, 1, ccm_seg7_texture_jump),
	gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 2047, 128),
	gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 16, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 124),
	gsSPEndDisplayList(),
};

static const Gfx mat_revert_slider_JumpMaterial_v4[] = {
	gsSPSetGeometryMode(G_CULL_BACK),
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsSPEndDisplayList(),
};

const Gfx slider_8_dl_mesh[] = {
	gsSPDisplayList(mat_slider_JumpMaterial_v4),
	gsSPDisplayList(slider_8_dl_mesh_tri_0),
	gsSPDisplayList(mat_revert_slider_JumpMaterial_v4),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

