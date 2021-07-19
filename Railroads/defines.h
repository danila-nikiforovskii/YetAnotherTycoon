#ifndef DEFINES_H
#define DEFINES_H

// CORE

#define WIDTH 100
#define HEIGHT 100
#define HEIGHT2 50
#define GAME_ROOT_DIR "C:/YetAnotherTycoon/RailAssets/"

// ======================= GAMEPLAY ==============================
// TERRAIN TYPES

#define TERRAIN_TYPES_GRASS_YELLOW 0
#define TERRAIN_TYPES_GRASS 1
#define TERRAIN_TYPES_GRASS_GREEN 2
#define TERRAIN_TYPES_FOREST 3
#define TERRAIN_TYPES_SWAMP 4
#define TERRAIN_TYPES_SNOW 5
#define TERRAIN_TYPES_DESERT 6
#define TERRAIN_TYPES_FARM1 7
#define TERRAIN_TYPES_FARM2 8
#define TERRAIN_TYPES_FARM3 9
#define TERRAIN_TYPES_FARM4 10
#define TERRAIN_TYPES_FARM5 11
#define TERRAIN_TYPES_FARM6 12
#define TERRAIN_TYPES_FARM7 13
#define TERRAIN_TYPES_DIRT 14
#define TERRAIN_TYPES_ROCKS 15

#define TERRAIN_TYPES_WATER 16

#define HEIGHT_DIFF_THRESHOLD 5
// ======================= STATES AND SUBSTATES ================

#define STATE_MAINMENU 0
#define STATE_GAMEPLAY 100
#define STATE_MAPEDITOR 200


#define TOOL_NONE 0
#define TOOL_LANDSCAPE_UP 10
#define TOOL_LANDSCAPE_DOWN 20
#define TOOL_RAILROAD_PLACE_START 30
#define TOOL_RAILROAD_PLACE_END 31

#define TOOL_CHANGE_TERRAIN 40
#define TOOL_TOGGLE_WATER 50

#define TOOL_BULLDOSE 60


// ======================== TECHNICAL ==============================

// UI DRAWING MODES
#define UI_MOD_NONE 0


// TERRAIN DRAWING MODES

#define TERRAIN_MOD_NONE 0
#define TERRAIN_MOD_MOUSEMAP 9
#define TERRAIN_MOD_CORNERS_DL 1
#define TERRAIN_MOD_CORNERS_UL 2
#define TERRAIN_MOD_CORNERS_DR 3
#define TERRAIN_MOD_CORNERS_UR 4
#define TERRAIN_MOD_SIDES_L 5
#define TERRAIN_MOD_SIDES_R 6
#define TERRAIN_MOD_SIDES_U 7
#define TERRAIN_MOD_SIDES_D 8

// Hover GROUPS

#define HOVER_GROUP_OTHER 0
#define HOVER_GROUP_TERRAIN 1
#define HOVER_GROUP_CORNER 2
#define HOVER_GROUP_HOR_SIDE 3
#define HOVER_GROUP_VER_SIDE 4

// CORNER TYPES

#define CORNER_DL 0
#define CORNER_DR 1
#define CORNER_UL 2
#define CORNER_UR 3

#define SIDE_L 0
#define SIDE_R 1
#define SIDE_U 2
#define SIDE_D 3


// MOUSEMAP REGIONS

#define MOUSEMAP_MAX_DISPLAYED_WIDTH (200)
#define MOUSEMAP_MAX_DISPLAYED_HEIGHT (200)
#define MOUSEMAP_TERRAIN_BASE (0)
#define MOUSEMAP_TERRAIN_STEP (1)
#define MOUSEMAP_TERRAIN_END (MOUSEMAP_TERRAIN_BASE+MOUSEMAP_TERRAIN_STEP*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_MAX_DISPLAYED_HEIGHT)

#define MOUSEMAP_CORNERS_DL_BASE (MOUSEMAP_TERRAIN_END)
#define MOUSEMAP_CORNERS_DL_END (MOUSEMAP_CORNERS_DL_BASE+MOUSEMAP_TERRAIN_STEP*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_MAX_DISPLAYED_HEIGHT)

#define MOUSEMAP_CORNERS_DR_BASE (MOUSEMAP_CORNERS_DL_END)
#define MOUSEMAP_CORNERS_DR_END (MOUSEMAP_CORNERS_DR_BASE+MOUSEMAP_TERRAIN_STEP*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_MAX_DISPLAYED_HEIGHT)

#define MOUSEMAP_CORNERS_UL_BASE (MOUSEMAP_CORNERS_DR_END)
#define MOUSEMAP_CORNERS_UL_END (MOUSEMAP_CORNERS_UL_BASE+MOUSEMAP_TERRAIN_STEP*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_MAX_DISPLAYED_HEIGHT)

#define MOUSEMAP_CORNERS_UR_BASE (MOUSEMAP_CORNERS_UL_END)
#define MOUSEMAP_CORNERS_UR_END (MOUSEMAP_CORNERS_UR_BASE+MOUSEMAP_TERRAIN_STEP*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_MAX_DISPLAYED_HEIGHT)
#define MOUSEMAP_CORNERS_END MOUSEMAP_CORNERS_UR_END

#define MOUSEMAP_SIDES_L_BASE (MOUSEMAP_CORNERS_UR_END)
#define MOUSEMAP_SIDES_L_END (MOUSEMAP_SIDES_L_BASE+MOUSEMAP_TERRAIN_STEP*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_MAX_DISPLAYED_HEIGHT)

#define MOUSEMAP_SIDES_R_BASE (MOUSEMAP_SIDES_L_END)
#define MOUSEMAP_SIDES_R_END (MOUSEMAP_SIDES_R_BASE+MOUSEMAP_TERRAIN_STEP*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_MAX_DISPLAYED_HEIGHT)

#define MOUSEMAP_VER_SIDES_END MOUSEMAP_SIDES_R_END

#define MOUSEMAP_SIDES_U_BASE (MOUSEMAP_SIDES_R_END)
#define MOUSEMAP_SIDES_U_END (MOUSEMAP_SIDES_U_BASE+MOUSEMAP_TERRAIN_STEP*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_MAX_DISPLAYED_HEIGHT)

#define MOUSEMAP_SIDES_D_BASE (MOUSEMAP_SIDES_U_END)
#define MOUSEMAP_SIDES_D_END (MOUSEMAP_SIDES_D_BASE+MOUSEMAP_TERRAIN_STEP*MOUSEMAP_MAX_DISPLAYED_WIDTH*MOUSEMAP_MAX_DISPLAYED_HEIGHT)

#define MOUSEMAP_SIDES_END MOUSEMAP_SIDES_D_END


#endif // DEFINES_H
