/*******************************************************************************************
*
*   CGOLMenu v1.0.5 - Menu for adjusting Conway Game of Life settings
*
*   MODULE USAGE:
*       #define GUI_CGOLMENU_IMPLEMENTATION
*       #include "gui_CGOLMenu.h"
*
*       INIT: GuiCGOLMenuState state = InitGuiCGOLMenu();
*       DRAW: GuiCGOLMenu(&state);
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

#ifndef GUI_CGOLMENU_H
#define GUI_CGOLMENU_H

typedef struct {
    bool cgolWindowActive;
    bool tileSizeEditMode;
    int tileSizeValue;
    bool tileGapEditMode;
    int tileGapValue;
    bool mapSizeEditMode;
    int mapSizeValue;
    Color tileColorPickerValue;
    bool clearGridButtonPressed;
    bool applyButtonPressed;

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiCGOLMenuState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

// Module Functions Declaration
GuiCGOLMenuState InitGuiCGOLMenu(void);
void GuiCGOLMenu(GuiCGOLMenuState *state);

#ifdef __cplusplus
}
#endif
#endif // GUI_CGOLMENU_H

// GUI_CGOLMENU IMPLEMENTATION
#if defined(GUI_CGOLMENU_IMPLEMENTATION)

#include "../../lib/raygui/raygui.h"

// Module Functions Definition
GuiCGOLMenuState InitGuiCGOLMenu(void)
{
    GuiCGOLMenuState state = { 0 };

    state.cgolWindowActive = true;
    state.tileSizeEditMode = false;
    state.tileSizeValue = 0;
    state.tileGapEditMode = false;
    state.tileGapValue = 0;
    state.mapSizeEditMode = false;
    state.mapSizeValue = 0;
    state.tileColorPickerValue = (Color){ 0, 0, 0, 0 };
    state.clearGridButtonPressed = false;
    state.applyButtonPressed = false;
    // Custom variables initialization

    return state;
}

void GuiCGOLMenu(GuiCGOLMenuState *state)
{
    float yOffset = 100.0f;
    if (state->cgolWindowActive)
    {
        state->cgolWindowActive = !GuiWindowBox((Rectangle){ 40, 142-yOffset, 216, 288+60 }, "CGame v0.0.3 CGOL");
        if (GuiValueBox((Rectangle){ 120, 182-yOffset, 120, 24 }, "Tile size ", &state->tileSizeValue, 0, 100, state->tileSizeEditMode)) state->tileSizeEditMode = !state->tileSizeEditMode;
        if (GuiValueBox((Rectangle){ 120, 214-yOffset, 120, 24 }, "Tile gap ", &state->tileGapValue, 0, 100, state->tileGapEditMode)) state->tileGapEditMode = !state->tileGapEditMode;
        if (GuiValueBox((Rectangle){ 120, 246-yOffset, 120, 24 }, "Map size ", &state->mapSizeValue, 0, 100, state->mapSizeEditMode)) state->mapSizeEditMode = !state->mapSizeEditMode;
        GuiColorPicker((Rectangle){ 120, 286-yOffset, 96, 96 }, NULL, &state->tileColorPickerValue);
        GuiLabel((Rectangle){ 56, 286-yOffset, 56, 32 }, "Tile color");
        state->clearGridButtonPressed = GuiButton((Rectangle){ 120, 390-yOffset, 120, 24 }, "Clear grid"); 
        GuiLabel((Rectangle){ 80, 390-yOffset, 40, 24 }, "Reset");
        state->applyButtonPressed = GuiButton((Rectangle){ 120, 420-yOffset, 120, 24 }, "Apply"); 
        GuiLabel((Rectangle){ 80, 420-yOffset, 40, 24 }, "Apply settings");
    }
}

#endif // GUI_CGOLMENU_IMPLEMENTATION
