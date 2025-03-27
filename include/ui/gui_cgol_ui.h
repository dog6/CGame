/*******************************************************************************************
*
*   CgolUi v1.0.1 - Config for Conway's Game of Life scene
*
*   MODULE USAGE:
*       #define GUI_CGOL_UI_IMPLEMENTATION
*       #include "gui_cgol_ui.h"
*
*       INIT: GuiCgolUiState state = InitGuiCgolUi();
*       DRAW: GuiCgolUi(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 Team Mediocrity. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "../../lib/raylib/raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "../../lib/raygui/raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_CGOL_UI_H
#define GUI_CGOL_UI_H

typedef struct {
    Vector2 anchor01;
    
    bool CGOLMenuActive;
    bool tileSize_txtboxEditMode;
    int tileSize_txtboxValue;
    bool mapSize_txtboxEditMode;
    int mapSize_txtboxValue;
    bool tileGap_txtboxEditMode;
    int tileGap_txtboxValue;
    Color tile_colorPickerValue;
    bool genDelay_txtboxEditMode;
    int genDelay_txtboxValue;

    Rectangle layoutRecs[10];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiCgolUiState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiCgolUiState InitGuiCgolUi(void);
void GuiCgolUi(GuiCgolUiState *state);
static void ClearGridButton();
static void ApplySettingsButton();

#ifdef __cplusplus
}
#endif

#endif // GUI_CGOL_UI_H

/***********************************************************************************
*
*   GUI_CGOL_UI IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_CGOL_UI_IMPLEMENTATION)

#include "../../lib/raygui/raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiCgolUiState InitGuiCgolUi(void)
{
    GuiCgolUiState state = { 0 };

    state.anchor01 = (Vector2){ 24, 24 };
    
    state.CGOLMenuActive = true;
    state.tileSize_txtboxEditMode = false;
    state.tileSize_txtboxValue = 0;
    state.mapSize_txtboxEditMode = false;
    state.mapSize_txtboxValue = 0;
    state.tileGap_txtboxEditMode = false;
    state.tileGap_txtboxValue = 0;
    state.tile_colorPickerValue = (Color){ 0, 0, 0, 0 };
    state.genDelay_txtboxEditMode = false;
    state.genDelay_txtboxValue = 0;

    state.layoutRecs[0] = (Rectangle){ state.anchor01.x + 0, state.anchor01.y + 0, 224, 328 };
    state.layoutRecs[1] = (Rectangle){ state.anchor01.x + 88, state.anchor01.y + 40, 120, 24 };
    state.layoutRecs[2] = (Rectangle){ state.anchor01.x + 88, state.anchor01.y + 72, 120, 24 };
    state.layoutRecs[3] = (Rectangle){ state.anchor01.x + 88, state.anchor01.y + 104, 120, 24 };
    state.layoutRecs[4] = (Rectangle){ state.anchor01.x + 88, state.anchor01.y + 176, 96, 96 };
    state.layoutRecs[5] = (Rectangle){ state.anchor01.x + 32, state.anchor01.y + 176, 56, 24 };
    state.layoutRecs[6] = (Rectangle){ state.anchor01.x + 0, state.anchor01.y + 272, 224, 16 };
    state.layoutRecs[7] = (Rectangle){ state.anchor01.x + 8, state.anchor01.y + 288, 80, 32 };
    state.layoutRecs[8] = (Rectangle){ state.anchor01.x + 96, state.anchor01.y + 288, 120, 32 };
    state.layoutRecs[9] = (Rectangle){ state.anchor01.x + 88, state.anchor01.y + 136, 120, 24 };

    // Custom variables initialization

    return state;
}
static void ClearGridButton()
{
    // TODO: Implement control logic
}
static void ApplySettingsButton()
{
    // TODO: Implement control logic
}


void GuiCgolUi(GuiCgolUiState *state)
{
    const char *CGOLMenuText = "CGame v0.0.3 CGOL Menu";
    const char *tile_color_lblText = "Tile Color";
    const char *clearGrid_buttonText = "Clear grid";
    const char *applySettings_buttonText = "Apply Settings";
    
    if (state->CGOLMenuActive)
    {
        state->CGOLMenuActive = !GuiWindowBox(state->layoutRecs[0], CGOLMenuText);
        if (GuiValueBox(state->layoutRecs[1], tileSize_txtboxValue, &state->tileSize_txtboxValue, 0, 100, state->tileSize_txtboxEditMode)) state->tileSize_txtboxEditMode = !state->tileSize_txtboxEditMode;
        if (GuiValueBox(state->layoutRecs[2], mapSize_txtboxText, &state->mapSize_txtboxValue, 0, 100, state->mapSize_txtboxEditMode)) state->mapSize_txtboxEditMode = !state->mapSize_txtboxEditMode;
        if (GuiValueBox(state->layoutRecs[3], tileGap_txtboxText, &state->tileGap_txtboxValue, 0, 100, state->tileGap_txtboxEditMode)) state->tileGap_txtboxEditMode = !state->tileGap_txtboxEditMode;
        GuiColorPicker(state->layoutRecs[4], tile_colorPickerText, &state->tile_colorPickerValue);
        GuiLabel(state->layoutRecs[5], tile_color_lblText);
        GuiLine(state->layoutRecs[6], horizontal-lineText);
        if (GuiButton(state->layoutRecs[7], clearGrid_buttonText)) ClearGridButton(); 
        if (GuiButton(state->layoutRecs[8], applySettings_buttonText)) ApplySettingsButton(); 
        if (GuiValueBox(state->layoutRecs[9], genDelay_txtboxText, &state->genDelay_txtboxValue, 0, 100, state->genDelay_txtboxEditMode)) state->genDelay_txtboxEditMode = !state->genDelay_txtboxEditMode;
    }
}

#endif // GUI_CGOL_UI_IMPLEMENTATION
