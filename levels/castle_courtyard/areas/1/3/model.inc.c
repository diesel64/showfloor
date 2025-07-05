static const Vtx courtyard_3_dl_mesh_vtx_0[24] = {
	{{ {-2047, 1126, 195}, 0, {974, -16}, {0, 0, 127, 255} }},
	{{ {-2047, 717, 195}, 0, {974, 974}, {0, 0, 127, 255} }},
	{{ {-1637, 717, 195}, 0, {-16, 974}, {0, 0, 127, 255} }},
	{{ {-1637, 1126, 195}, 0, {-16, -16}, {0, 0, 127, 255} }},
	{{ {-2047, 1741, 195}, 0, {974, -16}, {0, 0, 127, 255} }},
	{{ {-2047, 1331, 195}, 0, {974, 974}, {0, 0, 127, 255} }},
	{{ {-1637, 1331, 195}, 0, {-16, 974}, {0, 0, 127, 255} }},
	{{ {-1637, 1741, 195}, 0, {-16, -16}, {0, 0, 127, 255} }},
	{{ {-613, 1741, 502}, 0, {974, -16}, {0, 0, 127, 255} }},
	{{ {-613, 1331, 502}, 0, {974, 974}, {0, 0, 127, 255} }},
	{{ {-204, 1331, 502}, 0, {-16, 974}, {0, 0, 127, 255} }},
	{{ {-204, 1741, 502}, 0, {-16, -16}, {0, 0, 127, 255} }},
	{{ {1638, 1741, 195}, 0, {974, -16}, {0, 0, 127, 255} }},
	{{ {2048, 1331, 195}, 0, {-16, 974}, {0, 0, 127, 255} }},
	{{ {2048, 1741, 195}, 0, {-16, -16}, {0, 0, 127, 255} }},
	{{ {1638, 1331, 195}, 0, {974, 974}, {0, 0, 127, 255} }},
	{{ {1638, 1126, 195}, 0, {974, -16}, {0, 0, 127, 255} }},
	{{ {2048, 717, 195}, 0, {-16, 974}, {0, 0, 127, 255} }},
	{{ {2048, 1126, 195}, 0, {-16, -16}, {0, 0, 127, 255} }},
	{{ {1638, 717, 195}, 0, {974, 974}, {0, 0, 127, 255} }},
	{{ {205, 1741, 502}, 0, {974, -16}, {0, 0, 127, 255} }},
	{{ {614, 1331, 502}, 0, {-16, 974}, {0, 0, 127, 255} }},
	{{ {614, 1741, 502}, 0, {-16, -16}, {0, 0, 127, 255} }},
	{{ {205, 1331, 502}, 0, {974, 974}, {0, 0, 127, 255} }},
};

static const Gfx courtyard_3_dl_mesh_tri_0[] = {
	gsSPVertex(courtyard_3_dl_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 15, 13, 0),
	gsSPVertex(courtyard_3_dl_mesh_vtx_0 + 16, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 7, 5, 0),
	gsSPEndDisplayList(),
};

static const Gfx mat_courtyard_WindowMaterial[] = {
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPSetLights1(courtyard_lights),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, outside_0900A800),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 1023, 256),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

static const Gfx mat_revert_courtyard_WindowMaterial[] = {
	gsSPSetGeometryMode(G_CULL_BACK),
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsSPEndDisplayList(),
};

const Gfx courtyard_3_dl_mesh[] = {
	gsSPDisplayList(mat_courtyard_WindowMaterial),
	gsSPDisplayList(courtyard_3_dl_mesh_tri_0),
	gsSPDisplayList(mat_revert_courtyard_WindowMaterial),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

