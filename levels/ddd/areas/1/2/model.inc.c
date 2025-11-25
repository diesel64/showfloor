static const Vtx water_land_2_dl_mesh_vtx_0[8] = {
	{{ {4992, -296, 469}, 0, {1821, 1025}, {166, 166, 0, 255} }},
	{{ {4536, 158, 469}, 0, {1821, 76}, {166, 166, 0, 255} }},
	{{ {4536, 158, -436}, 0, {237, 76}, {166, 166, 0, 255} }},
	{{ {4992, -296, -436}, 0, {239, 1025}, {166, 166, 0, 255} }},
	{{ {5864, -2706, -472}, 0, {199, 65}, {0, 127, 0, 255} }},
	{{ {5864, -2706, 481}, 0, {1849, 65}, {0, 127, 0, 255} }},
	{{ {6582, -2706, 481}, 0, {1849, 983}, {0, 127, 0, 255} }},
	{{ {6582, -2706, -472}, 0, {199, 983}, {0, 127, 0, 255} }},
};

static const Gfx water_land_2_dl_mesh_tri_0[] = {
	gsSPVertex(water_land_2_dl_mesh_vtx_0 + 0, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSPEndDisplayList(),
};

const Gfx water_land_2_dl_mesh[] = {
	gsSPDisplayList(mat_water_land_ArrowMaterial),
	gsSPDisplayList(water_land_2_dl_mesh_tri_0),
	gsSPDisplayList(mat_revert_water_land_ArrowMaterial),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

