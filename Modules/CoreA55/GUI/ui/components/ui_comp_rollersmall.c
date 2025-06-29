// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 9.1.0
// Project name: Eldex_Optos_Touch

#include "../ui.h"


// COMPONENT RollerSmall

lv_obj_t * ui_Container____RollerSmall_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_Container____RollerSmall;
    cui_Container____RollerSmall = lv_obj_create(comp_parent);
    lv_obj_remove_style_all(cui_Container____RollerSmall);
    lv_obj_set_height(cui_Container____RollerSmall, lv_pct(100));
    lv_obj_set_width(cui_Container____RollerSmall, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_align(cui_Container____RollerSmall, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(cui_Container____RollerSmall, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_Container____RollerSmall, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_remove_flag(cui_Container____RollerSmall, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(cui_Container____RollerSmall, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_Container____RollerSmall, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_Container____RollerSmall, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_Container____RollerSmall, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_Container____RollerSmall, 14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_Container____RollerSmall, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_Label____Title;
    cui_Label____Title = lv_label_create(cui_Container____RollerSmall);
    lv_obj_set_width(cui_Label____Title, 140);
    lv_obj_set_height(cui_Label____Title, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_Label____Title, LV_ALIGN_CENTER);
    lv_label_set_text(cui_Label____Title, "Title");
    ui_object_set_themeable_style_property(cui_Label____Title, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Dark_blue);
    ui_object_set_themeable_style_property(cui_Label____Title, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Dark_blue);
    lv_obj_set_style_text_align(cui_Label____Title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_Label____Title, &ui_font_P3_Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_Roller____Roller;
    cui_Roller____Roller = lv_roller_create(cui_Container____RollerSmall);
    lv_roller_set_options(cui_Roller____Roller, "Option 1\nOption 2\nOption 3", LV_ROLLER_MODE_NORMAL);
    lv_roller_set_selected(cui_Roller____Roller, 1, LV_ANIM_OFF);
    lv_obj_set_width(cui_Roller____Roller, 140);
    lv_obj_set_flex_grow(cui_Roller____Roller, 1);
    lv_obj_set_x(cui_Roller____Roller, -75);
    lv_obj_set_y(cui_Roller____Roller, 3);
    lv_obj_set_align(cui_Roller____Roller, LV_ALIGN_CENTER);
    ui_object_set_themeable_style_property(cui_Roller____Roller, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Dark_blue);
    ui_object_set_themeable_style_property(cui_Roller____Roller, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Dark_blue);
    lv_obj_set_style_text_letter_space(cui_Roller____Roller, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(cui_Roller____Roller, 14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(cui_Roller____Roller, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_Roller____Roller, &ui_font_P2_Med, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_Roller____Roller, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_object_set_themeable_style_property(cui_Roller____Roller, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                           _ui_theme_color_Interface);
    ui_object_set_themeable_style_property(cui_Roller____Roller, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_Interface);

    ui_object_set_themeable_style_property(cui_Roller____Roller, LV_PART_SELECTED | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_White);
    ui_object_set_themeable_style_property(cui_Roller____Roller, LV_PART_SELECTED | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_White);
    lv_obj_set_style_text_font(cui_Roller____Roller, &ui_font_P2_SBold, LV_PART_SELECTED | LV_STATE_DEFAULT);
    ui_object_set_themeable_style_property(cui_Roller____Roller, LV_PART_SELECTED | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                           _ui_theme_color_Dark_blue);
    ui_object_set_themeable_style_property(cui_Roller____Roller, LV_PART_SELECTED | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_Dark_blue);

    lv_obj_t ** children = lv_malloc(sizeof(lv_obj_t *) * _UI_COMP_CONTAINER____ROLLERSMALL_NUM);
    children[UI_COMP_CONTAINER____ROLLERSMALL_CONTAINER____ROLLERSMALL] = cui_Container____RollerSmall;
    children[UI_COMP_CONTAINER____ROLLERSMALL_LABEL____TITLE] = cui_Label____Title;
    children[UI_COMP_CONTAINER____ROLLERSMALL_ROLLER____ROLLER] = cui_Roller____Roller;
    lv_obj_add_event_cb(cui_Container____RollerSmall, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_Container____RollerSmall, del_component_child_event_cb, LV_EVENT_DELETE, children);
    ui_comp_Container____RollerSmall_create_hook(cui_Container____RollerSmall);
    return cui_Container____RollerSmall;
}

