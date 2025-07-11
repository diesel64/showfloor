#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/area.h"
#include "game/level_update.h"
#include "menu/title_screen.h"

#include "levels/scripts.h"

#include "actors/common1.h"

#include "make_const_nonconst.h"
#include "levels/intro/header.h"

const LevelScript level_intro_splash_screen[] = {
    INIT_LEVEL(),
    BLACKOUT(/*active*/ TRUE),
    FIXED_LOAD(/*loadAddr*/ _goddardSegmentStart, /*romStart*/ _goddardSegmentRomStart, /*romEnd*/ _goddardSegmentRomEnd),
    LOAD_MARIO_HEAD(/*loadHeadID*/ REGULAR_FACE),
    LOAD_RAW(/*seg*/ 0x13, _behaviorSegmentRomStart, _behaviorSegmentRomEnd),
    LOAD_MIO0(/*seg*/ 0x07, _intro_segment_7SegmentRomStart, _intro_segment_7SegmentRomEnd),
    LOAD_MIO0_TEXTURE(/*seg*/ 0x0A, _title_screen_bg_mio0SegmentRomStart, _title_screen_bg_mio0SegmentRomEnd),
    ALLOC_LEVEL_POOL(),

    AREA(/*index*/ 1, intro_geo_0002D0),
    END_AREA(),

    AREA(/*index*/ 2, intro_geo_mario_head_regular),
    END_AREA(),

    FREE_LEVEL_POOL(),
    SLEEP(/*frames*/ 1),
    BLACKOUT(/*active*/ FALSE),

    LOAD_AREA(/*area*/ 1),
    CALL(/*arg*/ 0, /*func*/ lvl_intro_update),
    SLEEP(/*frames*/ 37),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0x00, 0x00, 0x00),
    SLEEP(/*frames*/ 16),

    /* This unused command is present in the original source code for this section and is it's only usage. 
     * It clears the current area, allowing the next are to be loaded. 
     * Even though it doesn't have a use in the retail source code, it does now have an affect, 
     * allowing the next area with the Mario head to be loaded, which was most likekly its original intention here.
     */
    CMD2A(/*unk2*/ 1),
    SLEEP(/*frames*/ 2),

    LOAD_AREA(/*area*/ 2),
    SET_MENU_MUSIC(/*seq*/ 0x0002),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_FROM_STAR, /*time*/ 20, /*color*/ 0x00, 0x00, 0x00),
    SLEEP(/*frames*/ 20),
    CALL_LOOP(/*arg*/ 1, /*func*/ lvl_intro_update),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ 100, script_intro_L1),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ 101, script_intro_L2),
    JUMP(script_intro_L4),
};

const LevelScript level_intro_mario_head_regular[] = {
    INIT_LEVEL(),
    BLACKOUT(/*active*/ TRUE),
    FIXED_LOAD(/*loadAddr*/ _goddardSegmentStart, /*romStart*/ _goddardSegmentRomStart, /*romEnd*/ _goddardSegmentRomEnd),
    LOAD_MARIO_HEAD(/*loadHeadID*/ REGULAR_FACE),
    LOAD_RAW         (/*seg*/ 0x13, _behaviorSegmentRomStart, _behaviorSegmentRomEnd),
    LOAD_MIO0_TEXTURE(/*seg*/ 0x0A, _title_screen_bg_mio0SegmentRomStart, _title_screen_bg_mio0SegmentRomEnd),

    ALLOC_LEVEL_POOL(),
    AREA(/*index*/ 1, intro_geo_mario_head_regular),
    END_AREA(),
    FREE_LEVEL_POOL(),

    SLEEP(/*frames*/ 2),
    BLACKOUT(/*active*/ FALSE),
    LOAD_AREA(/*area*/ 1),
    SET_MENU_MUSIC(/*seq*/ SEQ_MENU_TITLE_SCREEN),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_FROM_STAR, /*time*/ 20, /*color*/ 0x00, 0x00, 0x00),
    SLEEP(/*frames*/ 20),
    CALL_LOOP(/*arg*/ LVL_INTRO_REGULAR, /*func*/ lvl_intro_update),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ 100, script_intro_L1),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ 101, script_intro_L2),
    JUMP(script_intro_L4),
};

const LevelScript level_intro_mario_head_dizzy[] = {
    INIT_LEVEL(),
    BLACKOUT(/*active*/ TRUE),
    FIXED_LOAD(/*loadAddr*/ _goddardSegmentStart, /*romStart*/ _goddardSegmentRomStart, /*romEnd*/ _goddardSegmentRomEnd),
    LOAD_MARIO_HEAD(/*loadHeadID*/ DIZZY_FACE),
    LOAD_RAW         (/*seg*/ 0x13, _behaviorSegmentRomStart, _behaviorSegmentRomEnd),
    LOAD_MIO0_TEXTURE(/*seg*/ 0x0A, _title_screen_bg_mio0SegmentRomStart, _title_screen_bg_mio0SegmentRomEnd),
    ALLOC_LEVEL_POOL(),

    AREA(/*index*/ 1, intro_geo_mario_head_dizzy),
    END_AREA(),

    FREE_LEVEL_POOL(),
    SLEEP(/*frames*/ 2),
    BLACKOUT(/*active*/ FALSE),
    LOAD_AREA(/*area*/ 1),
    SET_MENU_MUSIC(/*seq*/ SEQ_MENU_GAME_OVER),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_FROM_STAR, /*time*/ 20, /*color*/ 0x00, 0x00, 0x00),
    SLEEP(/*frames*/ 20),
    CALL_LOOP(/*arg*/ LVL_INTRO_GAME_OVER, /*func*/ lvl_intro_update),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ 100, script_intro_L1),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ 101, script_intro_L2),
    JUMP(script_intro_L4),
};

const LevelScript level_intro_entry_4[] = {
    INIT_LEVEL(),
    LOAD_RAW         (/*seg*/ 0x13, _behaviorSegmentRomStart, _behaviorSegmentRomEnd),
    LOAD_MIO0_TEXTURE(/*seg*/ 0x0A, _title_screen_bg_mio0SegmentRomStart, _title_screen_bg_mio0SegmentRomEnd),
    LOAD_MIO0        (/*seg*/ 0x07, _debug_level_select_mio0SegmentRomStart, _debug_level_select_mio0SegmentRomEnd),
    FIXED_LOAD(/*loadAddr*/ _goddardSegmentStart, /*romStart*/ _goddardSegmentRomStart, /*romEnd*/ _goddardSegmentRomEnd),
    ALLOC_LEVEL_POOL(),

    AREA(/*index*/ 1, intro_geo_000414),
    END_AREA(),

    FREE_LEVEL_POOL(),
    LOAD_AREA(/*area*/ 1),
    SET_MENU_MUSIC(/*seq*/ SEQ_MENU_TITLE_SCREEN),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_FROM_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 16),
    CALL_LOOP(/*arg*/ LVL_INTRO_LEVEL_SELECT, /*func*/ lvl_intro_update),
    JUMP_IF(/*op*/ OP_EQ, /*arg*/ -1, script_intro_L5),
    JUMP(script_intro_L3),
};

// These should be static, but C doesn't allow non-sized forward declarations of static arrays

const LevelScript script_intro_L1[] = {
    STOP_MUSIC(/*fadeOutTime*/ 0x00BE),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0x00, 0x00, 0x00),
    SLEEP(/*frames*/ 16),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    SET_REG(/*value*/ 16),
    INIT_LEVEL(),
    EXIT_AND_EXECUTE(/*seg*/ 0x15, _scriptsSegmentRomStart, _scriptsSegmentRomEnd, level_main_scripts_entry),
};

const LevelScript script_intro_L2[] = {
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 16),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    EXIT_AND_EXECUTE(/*seg*/ 0x14, _introSegmentRomStart, _introSegmentRomEnd, level_intro_entry_4),
};

const LevelScript script_intro_L3[] = {
    STOP_MUSIC(/*fadeOutTime*/ 0x00BE),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 16),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    EXIT_AND_EXECUTE(/*seg*/ 0x15, _scriptsSegmentRomStart, _scriptsSegmentRomEnd, level_main_scripts_entry),
};

const LevelScript script_intro_L4[] = {
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0xFF, 0xFF, 0xFF),
    SLEEP(/*frames*/ 16),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    EXIT_AND_EXECUTE(/*seg*/ 0x15, _scriptsSegmentRomStart, _scriptsSegmentRomEnd, level_main_scripts_entry),
};

const LevelScript script_intro_L5[] = {
    STOP_MUSIC(/*fadeOutTime*/ 0x00BE),
    TRANSITION(/*transType*/ WARP_TRANSITION_FADE_INTO_COLOR, /*time*/ 16, /*color*/ 0x00, 0x00, 0x00),
    SLEEP(/*frames*/ 16),
    CLEAR_LEVEL(),
    SLEEP(/*frames*/ 2),
    EXIT_AND_EXECUTE(/*seg*/ 0x14, _introSegmentRomStart, _introSegmentRomEnd, level_intro_splash_screen),
};
