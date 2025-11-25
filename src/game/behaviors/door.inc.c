// door.inc.c

struct DoorAction {
    u32 flag;
    s32 action;
};

static struct DoorAction sDoorActions[] = {
    { 0x40000, 3 }, { 0x80000, 4 }, { 0x10000, 1 }, { 0x20000, 2 }, { 0xFFFFFFFF, 0 },
};

void door_animation_and_reset(s32 sp18) {
    cur_obj_init_animation_with_sound(sp18);
    if (cur_obj_check_if_near_animation_end()) {
        o->oAction = 0;
    }
}

void set_door_camera_event(void) {
    if (gMarioStates[0].interactObj == o) {
        if (segmented_to_virtual(bhvDoor) == o->behavior)
            gPlayerCameraState[0].cameraEvent = CAM_EVENT_DOOR;
        else if (gMarioStates[0].action != ACT_WARP_DOOR_SPAWN) {
            gPlayerCameraState[0].cameraEvent = CAM_EVENT_DOOR_WARP;
        }
        gPlayerCameraState[0].usedObj = o;
    }
}

void play_door_open_noise(void) {
    if (o->oTimer == 0) {
        cur_obj_play_sound_2(SOUND_GENERAL_OPEN_WOOD_DOOR);
        gTimeStopState |= TIME_STOP_MARIO_OPENED_DOOR;
    }
    if (o->oTimer == 70) {
        cur_obj_play_sound_2(SOUND_GENERAL_CLOSE_WOOD_DOOR);
    }
}

void play_warp_door_open_noise(void) {
    if (o->oTimer == 30) {
        cur_obj_play_sound_2(SOUND_GENERAL_CLOSE_WOOD_DOOR);
    }
}

void bhv_door_loop(void) {
    s32 sp1C = 0;

    while (sDoorActions[sp1C].flag != 0xFFFFFFFF) {
        if (cur_obj_clear_interact_status_flag(sDoorActions[sp1C].flag)) {
            set_door_camera_event();
            cur_obj_change_action(sDoorActions[sp1C].action);
        }
        sp1C++;
    }

    switch (o->oAction) {
        case 0:
            cur_obj_init_animation_with_sound(0);
            break;
        case 1:
            door_animation_and_reset(1);
            play_door_open_noise();
            break;
        case 2:
            door_animation_and_reset(2);
            play_door_open_noise();
            break;
        case 3:
            door_animation_and_reset(3);
            play_warp_door_open_noise();
            break;
        case 4:
            door_animation_and_reset(4);
            play_warp_door_open_noise();
            break;
    }

    if (o->oAction == 0) {
        load_object_collision_model();
    }

    o->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;
}

void bhv_door_init(void) {
    f32 x;
    f32 z;
    struct Surface *floor;

    x = o->oPosX;
    z = o->oPosZ;
    find_floor(x, o->oPosY, z, &floor);
    if (floor != NULL) {
        o->oDoorUnkF8 = floor->room;
    }

    x = o->oPosX + sins(o->oMoveAngleYaw) * 200.0f;
    z = o->oPosZ + coss(o->oMoveAngleYaw) * 200.0f;
    find_floor(x, o->oPosY, z, &floor);
    if (floor != NULL) {
        o->oDoorUnkFC = floor->room;
    }

    x = o->oPosX + sins(o->oMoveAngleYaw) * -200.0f;
    z = o->oPosZ + coss(o->oMoveAngleYaw) * -200.0f;
    find_floor(x, o->oPosY, z, &floor);
    if (floor != NULL) {
        o->oDoorUnk100 = floor->room;
    }

    if (o->oDoorUnkF8 > 0 && o->oDoorUnkF8 < 60) {
        gDoorAdjacentRooms[o->oDoorUnkF8][0] = o->oDoorUnkFC;
        gDoorAdjacentRooms[o->oDoorUnkF8][1] = o->oDoorUnk100;
    }
}
