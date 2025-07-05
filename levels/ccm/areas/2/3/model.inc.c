static const Lights1 slider_f3dlite_material_026_lights = gdSPDefLights1(
	0x3F, 0x3F, 0x0,
	0xFF, 0xFF, 0x0, 0x28, 0x28, 0x28);

static const Vtx slider_3_dl_mesh_vtx_0[4] = {
	{{ {5819, 5240, 5820}, 0, {-16, 751}, {90, 0, 90, 255} }},
	{{ {6109, 5342, 5531}, 0, {2044, 204}, {90, 0, 90, 255} }},
	{{ {5819, 5342, 5820}, 0, {-16, 204}, {90, 0, 90, 255} }},
	{{ {6109, 5240, 5531}, 0, {2044, 751}, {90, 0, 90, 255} }},
};

static const Gfx slider_3_dl_mesh_tri_0[] = {
	gsSPVertex(slider_3_dl_mesh_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSPEndDisplayList(),
};

static const Gfx mat_slider_f3dlite_material_026[] = {
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPSetLights1(slider_f3dlite_material_026_lights),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b_LOAD_BLOCK, 1, ccm_seg7_texture_start),
	gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 2047, 128),
	gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 16, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 124),
	gsSPEndDisplayList(),
};

static const Gfx mat_revert_slider_f3dlite_material_026[] = {
	gsSPSetGeometryMode(G_CULL_BACK),
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsSPEndDisplayList(),
};

const Gfx slider_3_dl_mesh[] = {
	gsSPDisplayList(mat_slider_f3dlite_material_026),
	gsSPDisplayList(slider_3_dl_mesh_tri_0),
	gsSPDisplayList(mat_revert_slider_f3dlite_material_026),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

