#include <ultra64.h>

#include "sm64.h"
#include "game_init.h"
#include "memory.h"
#include "envfx_snow.h"
#include "envfx_bubbles.h"
#include "engine/surface_collision.h"
#include "engine/math_util.h"
#include "engine/behavior_script.h"
#include "audio/external.h"
#include "textures.h"

/**
 * This file implements environment effects that are not snow:
 * Flowers (unused), lava bubbles and jet stream/whirlpool bubbles.
 * Refer to 'envfx_snow.c' for more info about environment effects.
 * Note that the term 'bubbles' is used as a collective name for
 * effects in this file even though flowers aren't bubbles. For the
 * sake of concise naming, flowers fall under bubbles.
 */

s16 gEnvFxBubbleConfig[10];
static Gfx *sGfxCursor; // points to end of display list for bubble particles
static s32 sBubbleParticleCount;
static s32 sBubbleParticleMaxCount;

UNUSED s32 D_80330690 = 0;
UNUSED s32 D_80330694 = 0;

/// Template for a bubble particle triangle
Vtx_t gBubbleTempVtx[3] = {
    { { 0, 0, 0 }, 0, { 1544, 964 }, { 0xFF, 0xFF, 0xFF, 0xFF } },
    { { 0, 0, 0 }, 0, { 522, -568 }, { 0xFF, 0xFF, 0xFF, 0xFF } },
    { { 0, 0, 0 }, 0, { -498, 964 }, { 0xFF, 0xFF, 0xFF, 0xFF } },
};

/**
 * Check whether the particle with the given index is
 * laterally within distance of point (x, z). Used to
 * kill flower and bubble particles.
 */
s32 particle_is_laterally_close(s32 index, s32 x, s32 z, s32 distance) {
    s32 xPos = (gEnvFxBuffer + index)->xPos;
    s32 zPos = (gEnvFxBuffer + index)->zPos;

    if (sqr(xPos - x) + sqr(zPos - z) > sqr(distance)) {
        return FALSE;
    }

    return TRUE;
}

/**
 * Generate a uniform random number in range [-2000, -1000[ or [1000, 2000[
 * Used to position flower particles
 */
s32 random_flower_offset(void) {
    s32 result = random_float() * 2000.0f - 1000.0f;
    if (result < 0) {
        result -= 1000;
    } else {
        result += 1000;
    }

    return result;
}

/**
 * Update flower particles. Flowers are scattered randomly in front of the
 * camera, and can land on any ground
 */
void envfx_update_flower(Vec3s centerPos) {
    s32 i;
    struct FloorGeometry *floorGeo; // unused
    s32 globalTimer = gGlobalTimer;

    s16 centerX = centerPos[0];
    UNUSED s16 centerY = centerPos[1];
    s16 centerZ = centerPos[2];

    for (i = 0; i < sBubbleParticleMaxCount; i++) {
        (gEnvFxBuffer + i)->isAlive = particle_is_laterally_close(i, centerX, centerZ, 3000);
        if (!(gEnvFxBuffer + i)->isAlive) {
            (gEnvFxBuffer + i)->xPos = random_flower_offset() + centerX;
            (gEnvFxBuffer + i)->zPos = random_flower_offset() + centerZ;
            (gEnvFxBuffer + i)->yPos = find_floor_height_and_data((gEnvFxBuffer + i)->xPos, 10000.0f,
                                                                  (gEnvFxBuffer + i)->zPos, &floorGeo);
            (gEnvFxBuffer + i)->isAlive = TRUE;
            (gEnvFxBuffer + i)->animFrame = random_float() * 5.0f;
        } else if (!(globalTimer & 3)) {
            (gEnvFxBuffer + i)->animFrame += 1;
            if ((gEnvFxBuffer + i)->animFrame > 5) {
                (gEnvFxBuffer + i)->animFrame = 0;
            }
        }
    }
}

/**
 * Update the position of a lava bubble to be somewhere around centerPos
 * Uses find_floor to find the height of lava, if no floor or a non-lava
 * floor is found the bubble y is set to -10000, which is why you can see
 * occasional lava bubbles far below the course in Lethal Lava Land.
 * In the second Bowser fight arena, the visual lava is above the lava
 * floor so lava-bubbles are not normally visible, only if you bring the
 * camera below the lava plane.
 */
void envfx_set_lava_bubble_position(s32 index, Vec3s centerPos) {
    struct Surface *surface;
    s16 floorY;

    s16 centerX = centerPos[0];
    s16 centerY = centerPos[1];
    s16 centerZ = centerPos[2];

    (gEnvFxBuffer + index)->xPos = random_float() * 6000.0f - 3000.0f + centerX;
    (gEnvFxBuffer + index)->zPos = random_float() * 6000.0f - 3000.0f + centerZ;

    if ((gEnvFxBuffer + index)->xPos > 8000) {
        (gEnvFxBuffer + index)->xPos = 16000 - (gEnvFxBuffer + index)->xPos;
    }
    if ((gEnvFxBuffer + index)->xPos < -8000) {
        (gEnvFxBuffer + index)->xPos = -16000 - (gEnvFxBuffer + index)->xPos;
    }

    if ((gEnvFxBuffer + index)->zPos > 8000) {
        (gEnvFxBuffer + index)->zPos = 16000 - (gEnvFxBuffer + index)->zPos;
    }
    if ((gEnvFxBuffer + index)->zPos < -8000) {
        (gEnvFxBuffer + index)->zPos = -16000 - (gEnvFxBuffer + index)->zPos;
    }

    floorY =
        find_floor((gEnvFxBuffer + index)->xPos, centerY + 500, (gEnvFxBuffer + index)->zPos, &surface);
    if (surface == NULL) {
        (gEnvFxBuffer + index)->yPos = FLOOR_LOWER_LIMIT_MISC;
        return;
    }

    if (surface->type == SURFACE_BURNING) {
        (gEnvFxBuffer + index)->yPos = floorY;
    } else {
        (gEnvFxBuffer + index)->yPos = FLOOR_LOWER_LIMIT_MISC;
    }
}

/**
 * Update lava bubble animation and give the bubble a new position if the
 * animation is over.
 */
void envfx_update_lava(Vec3s centerPos) {
    s32 i;
    s32 globalTimer = gGlobalTimer;
    s8 chance;

    UNUSED s16 centerX = centerPos[0];
    UNUSED s16 centerY = centerPos[1];
    UNUSED s16 centerZ = centerPos[2];

    for (i = 0; i < sBubbleParticleMaxCount; i++) {
        if (!(gEnvFxBuffer + i)->isAlive) {
            envfx_set_lava_bubble_position(i, centerPos);
            (gEnvFxBuffer + i)->isAlive = TRUE;
        } else if (!(globalTimer & 1)) {
            (gEnvFxBuffer + i)->animFrame += 1;
            if ((gEnvFxBuffer + i)->animFrame > 8) {
                (gEnvFxBuffer + i)->isAlive = FALSE;
                (gEnvFxBuffer + i)->animFrame = 0;
            }
        }
    }

    if ((chance = (s32) (random_float() * 16.0f)) == 8) {
        play_sound(SOUND_GENERAL_QUIET_BUBBLE2, gGlobalSoundSource);
    }
}

/**
 * Check whether a jet stream bubble should respawn. Happens if it is laterally
 * 1000 units away from the source or 1500 units above it.
 */
s32 envfx_is_jestream_bubble_alive(s32 index) {
    UNUSED u8 filler[4];

    if (!particle_is_laterally_close(index, gEnvFxBubbleConfig[ENVFX_STATE_SRC_X],
                                     gEnvFxBubbleConfig[ENVFX_STATE_SRC_Z], 1000)
        || gEnvFxBubbleConfig[ENVFX_STATE_SRC_Y] + 1500 < (gEnvFxBuffer + index)->yPos) {
        return FALSE;
    }

    return TRUE;
}

/**
 * Update the positions of jet stream bubble particles.
 * They move up and outwards.
 */
void envfx_update_jetstream(void) {
    s32 i;

    for (i = 0; i < sBubbleParticleMaxCount; i++) {
        (gEnvFxBuffer + i)->isAlive = envfx_is_jestream_bubble_alive(i);
        if (!(gEnvFxBuffer + i)->isAlive) {
            (gEnvFxBuffer + i)->angleAndDist[1] = random_float() * 300.0f;
            (gEnvFxBuffer + i)->angleAndDist[0] = random_u16();
            (gEnvFxBuffer + i)->xPos =
                gEnvFxBubbleConfig[ENVFX_STATE_SRC_X]
                + sins((gEnvFxBuffer + i)->angleAndDist[0]) * (gEnvFxBuffer + i)->angleAndDist[1];
            (gEnvFxBuffer + i)->zPos =
                gEnvFxBubbleConfig[ENVFX_STATE_SRC_Z]
                + coss((gEnvFxBuffer + i)->angleAndDist[0]) * (gEnvFxBuffer + i)->angleAndDist[1];
            (gEnvFxBuffer + i)->yPos =
                gEnvFxBubbleConfig[ENVFX_STATE_SRC_Y] + (random_float() * 400.0f - 200.0f);
        } else {
            (gEnvFxBuffer + i)->angleAndDist[1] += 10;
            (gEnvFxBuffer + i)->xPos += sins((gEnvFxBuffer + i)->angleAndDist[0]) * 10.0f;
            (gEnvFxBuffer + i)->zPos += coss((gEnvFxBuffer + i)->angleAndDist[0]) * 10.0f;
            (gEnvFxBuffer + i)->yPos -= ((gEnvFxBuffer + i)->angleAndDist[1] / 30) - 50;
        }
    }
}

/**
 * Initialize bubble (or flower) effect by allocating a buffer to store
 * the state of each particle and setting the initial and max count.
 * Analogous to init_snow_particles, but for bubbles.
 */
s32 envfx_init_bubble(s32 mode) {
    s32 i;

    switch (mode) {
        case ENVFX_MODE_NONE:
            return FALSE;

        case ENVFX_FLOWERS:
            sBubbleParticleCount = 30;
            sBubbleParticleMaxCount = 30;
            break;

        case ENVFX_LAVA_BUBBLES:
            sBubbleParticleCount = 15;
            sBubbleParticleMaxCount = 15;
            break;

        case ENVFX_JETSTREAM_BUBBLES:
            sBubbleParticleCount = 60;
            break;
    }

    gEnvFxBuffer =
        mem_pool_alloc(gEffectsMemoryPool, sBubbleParticleCount * sizeof(struct EnvFxParticle));
    if (gEnvFxBuffer == NULL) {
        return FALSE;
    }

    bzero(gEnvFxBuffer, sBubbleParticleCount * sizeof(struct EnvFxParticle));
    bzero(gEnvFxBubbleConfig, sizeof(gEnvFxBubbleConfig));

    switch (mode) {
        case ENVFX_LAVA_BUBBLES:
            for (i = 0; i < sBubbleParticleCount; i++) {
                (gEnvFxBuffer + i)->animFrame = random_float() * 7.0f;
            }
            break;
    }

    gEnvFxMode = mode;
    return TRUE;
}

/**
 * Update particles depending on mode.
 * Also sets the given vertices to the correct shape for each mode,
 * though they are not being rotated yet.
 */
void envfx_bubbles_update_switch(s32 mode, Vec3s camTo, Vec3s vertex1, Vec3s vertex2, Vec3s vertex3) {
    switch (mode) {
        case ENVFX_FLOWERS:
            envfx_update_flower(camTo);
            vertex1[0] = 50;
            vertex1[1] = 0;
            vertex1[2] = 0;
            vertex2[0] = 0;
            vertex2[1] = 75;
            vertex2[2] = 0;
            vertex3[0] = -50;
            vertex3[1] = 0;
            vertex3[2] = 0;
            break;

        case ENVFX_LAVA_BUBBLES:
            envfx_update_lava(camTo);
            vertex1[0] = 100;
            vertex1[1] = 0;
            vertex1[2] = 0;
            vertex2[0] = 0;
            vertex2[1] = 150;
            vertex2[2] = 0;
            vertex3[0] = -100;
            vertex3[1] = 0;
            vertex3[2] = 0;
            break;

        case ENVFX_JETSTREAM_BUBBLES:
            envfx_update_jetstream();
            vertex1[0] = 40;
            vertex1[1] = 0;
            vertex1[2] = 0;
            vertex2[0] = 0;
            vertex2[1] = 60;
            vertex2[2] = 0;
            vertex3[0] = -40;
            vertex3[1] = 0;
            vertex3[2] = 0;
            break;
    }
}

/**
 * Append 15 vertices to 'gfx', which is enough for 5 bubbles starting at
 * 'index'. The 3 input vertices represent the rotated triangle around (0,0,0)
 * that will be translated to bubble positions to draw the bubble image
 */
void append_bubble_vertex_buffer(Gfx *gfx, s32 index, Vec3s vertex1, Vec3s vertex2, Vec3s vertex3,
                                 Vtx *template) {
    s32 i = 0;
    Vtx *vertBuf = alloc_display_list(15 * sizeof(Vtx));

    if (vertBuf == NULL) {
        return;
    }

    for (i = 0; i < 15; i += 3) {
        vertBuf[i] = template[0];
        (vertBuf + i)->v.ob[0] = (gEnvFxBuffer + (index + i / 3))->xPos + vertex1[0];
        (vertBuf + i)->v.ob[1] = (gEnvFxBuffer + (index + i / 3))->yPos + vertex1[1];
        (vertBuf + i)->v.ob[2] = (gEnvFxBuffer + (index + i / 3))->zPos + vertex1[2];

        vertBuf[i + 1] = template[1];
        (vertBuf + i + 1)->v.ob[0] = (gEnvFxBuffer + (index + i / 3))->xPos + vertex2[0];
        (vertBuf + i + 1)->v.ob[1] = (gEnvFxBuffer + (index + i / 3))->yPos + vertex2[1];
        (vertBuf + i + 1)->v.ob[2] = (gEnvFxBuffer + (index + i / 3))->zPos + vertex2[2];

        vertBuf[i + 2] = template[2];
        (vertBuf + i + 2)->v.ob[0] = (gEnvFxBuffer + (index + i / 3))->xPos + vertex3[0];
        (vertBuf + i + 2)->v.ob[1] = (gEnvFxBuffer + (index + i / 3))->yPos + vertex3[1];
        (vertBuf + i + 2)->v.ob[2] = (gEnvFxBuffer + (index + i / 3))->zPos + vertex3[2];
    }

    gSPVertex(gfx, VIRTUAL_TO_PHYSICAL(vertBuf), 15, 0);
}

/**
 * Appends to the enfvx display list a command setting the appropriate texture
 * for a specific particle. The display list is not passed as parameter but uses
 * the global sGfxCursor instead.
 */
void envfx_set_bubble_texture(s32 mode, s16 index) {
    void **imageArr;
    s16 frame = (gEnvFxBuffer + index)->animFrame;

    switch (mode) {
        case ENVFX_FLOWERS:
            imageArr = segmented_to_virtual(&flower_bubbles_textures_ptr_0B002008);
            frame = (gEnvFxBuffer + index)->animFrame;
            break;

        case ENVFX_LAVA_BUBBLES:
            imageArr = segmented_to_virtual(&lava_bubble_ptr_0B006020);
            frame = (gEnvFxBuffer + index)->animFrame;
            break;

        case ENVFX_JETSTREAM_BUBBLES:
            imageArr = segmented_to_virtual(&bubble_ptr_0B006848);
            frame = 0;
            break;
    }

    gDPSetTextureImage(sGfxCursor++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, *(imageArr + frame));
    gSPDisplayList(sGfxCursor++, &tiny_bubble_dl_0B006D68);
}

/**
 * Updates the bubble particle positions, then generates and returns a display
 * list drawing them.
 */
Gfx *envfx_update_bubble_particles(s32 mode, UNUSED Vec3s marioPos, Vec3s camFrom, Vec3s camTo) {
    s32 i;
    s16 radius, pitch, yaw;

    Vec3s vertex1;
    Vec3s vertex2;
    Vec3s vertex3;

    Gfx *gfxStart = alloc_display_list(
        ((sBubbleParticleMaxCount / 5) * 10 + sBubbleParticleMaxCount + 3) * sizeof(Gfx));
    if (gfxStart == NULL) {
        return NULL;
    }

    sGfxCursor = gfxStart;

    orbit_from_positions(camTo, camFrom, &radius, &pitch, &yaw);
    envfx_bubbles_update_switch(mode, camTo, vertex1, vertex2, vertex3);
    rotate_triangle_vertices(vertex1, vertex2, vertex3, pitch, yaw);

    gSPDisplayList(sGfxCursor++, &tiny_bubble_dl_0B006D38);

    for (i = 0; i < sBubbleParticleMaxCount; i += 5) {
        gDPPipeSync(sGfxCursor++);
        envfx_set_bubble_texture(mode, i);
        append_bubble_vertex_buffer(sGfxCursor++, i, vertex1, vertex2, vertex3, (Vtx *) gBubbleTempVtx);
        gSP1Triangle(sGfxCursor++, 0, 1, 2, 0);
        gSP1Triangle(sGfxCursor++, 3, 4, 5, 0);
        gSP1Triangle(sGfxCursor++, 6, 7, 8, 0);
        gSP1Triangle(sGfxCursor++, 9, 10, 11, 0);
        gSP1Triangle(sGfxCursor++, 12, 13, 14, 0);
    }

    gSPDisplayList(sGfxCursor++, &tiny_bubble_dl_0B006AB0);
    gSPEndDisplayList(sGfxCursor++);

    return gfxStart;
}

/**
 * Update bubble-like environment effects. Assumes the mode is larger than 10,
 * lower modes are snow effects which are updated in a different function.
 * Returns a display list drawing the particles.
 */
Gfx *envfx_update_bubbles(s32 mode, Vec3s marioPos, Vec3s camTo, Vec3s camFrom) {
    Gfx *gfx;

    if (gEnvFxMode == ENVFX_MODE_NONE && !envfx_init_bubble(mode)) {
        return NULL;
    }

    switch (mode) {
        case ENVFX_FLOWERS:
            gfx = envfx_update_bubble_particles(ENVFX_FLOWERS, marioPos, camFrom, camTo);
            break;

        case ENVFX_LAVA_BUBBLES:
            gfx = envfx_update_bubble_particles(ENVFX_LAVA_BUBBLES, marioPos, camFrom, camTo);
            break;

        case ENVFX_JETSTREAM_BUBBLES:
            gfx = envfx_update_bubble_particles(ENVFX_JETSTREAM_BUBBLES, marioPos, camFrom, camTo);
            break;

        default:
            return NULL;
    }

    return gfx;
}
