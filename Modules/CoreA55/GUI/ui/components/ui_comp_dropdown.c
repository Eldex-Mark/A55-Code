// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 9.1.0
// Project name: Eldex_Optos_Touch

#include "../ui.h"


// COMPONENT Dropdown

lv_obj_t * ui_Container____Dropdown_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_Container____Dropdown;
    cui_Container____Dropdown = lv_obj_create(comp_parent);
    lv_obj_remove_style_all(cui_Container____Dropdown);
    lv_obj_set_width(cui_Container____Dropdown, 400);
    lv_obj_set_height(cui_Container____Dropdown, LV_SIZE_CONTENT);    /// 86
    lv_obj_set_align(cui_Container____Dropdown, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(cui_Container____Dropdown, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_Container____Dropdown, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_remove_flag(cui_Container____Dropdown, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_row(cui_Container____Dropdown, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_Container____Dropdown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_Container____Label_Group;
    cui_Container____Label_Group = lv_obj_create(cui_Container____Dropdown);
    lv_obj_remove_style_all(cui_Container____Label_Group);
    lv_obj_set_width(cui_Container____Label_Group, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_height(cui_Container____Label_Group, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_Container____Label_Group, LV_ALIGN_CENTER);
    lv_obj_remove_flag(cui_Container____Label_Group, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t * cui_Label____Title;
    cui_Label____Title = lv_label_create(cui_Container____Label_Group);
    lv_obj_set_width(cui_Label____Title, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_Label____Title, LV_SIZE_CONTENT);    /// 0
    lv_obj_set_align(cui_Label____Title, LV_ALIGN_CENTER);
    lv_label_set_text(cui_Label____Title, "Serial Number");
    ui_object_set_themeable_style_property(cui_Label____Title, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Dark_blue);
    ui_object_set_themeable_style_property(cui_Label____Title, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Dark_blue);
    lv_obj_set_style_text_font(cui_Label____Title, &ui_font_P3_Bold, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_Label____Title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_Label____Title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_Label____Title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_Label____Title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_Dropdown____Drop;
    cui_Dropdown____Drop = lv_dropdown_create(cui_Container____Dropdown);
    lv_dropdown_set_options(cui_Dropdown____Drop, "Option1\nOption2\nOption3\nOption4");
    lv_obj_set_height(cui_Dropdown____Drop, 56);
    lv_obj_set_width(cui_Dropdown____Drop, lv_pct(100));
    lv_obj_set_x(cui_Dropdown____Drop, 50);
    lv_obj_set_y(cui_Dropdown____Drop, -32);
    lv_obj_set_align(cui_Dropdown____Drop, LV_ALIGN_CENTER);
    lv_obj_add_flag(cui_Dropdown____Drop, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    ui_object_set_themeable_style_property(cui_Dropdown____Drop, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Dark_blue);
    ui_object_set_themeable_style_property(cui_Dropdown____Drop, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Dark_blue);
    lv_obj_set_style_text_font(cui_Dropdown____Drop, &ui_font_P2_SBold, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cui_Dropdown____Drop, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_object_set_themeable_style_property(cui_Dropdown____Drop, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR,
                                           _ui_theme_color_Purple);
    ui_object_set_themeable_style_property(cui_Dropdown____Drop, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_OPA,
                                           _ui_theme_alpha_Purple);
    lv_obj_set_style_border_width(cui_Dropdown____Drop, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_Dropdown____Drop, 14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_Dropdown____Drop, 14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_Dropdown____Drop, 14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_Dropdown____Drop, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_object_set_themeable_style_property(cui_Dropdown____Drop, LV_PART_INDICATOR | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Dark_blue);
    ui_object_set_themeable_style_property(cui_Dropdown____Drop, LV_PART_INDICATOR | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Dark_blue);
    lv_obj_set_style_text_font(cui_Dropdown____Drop, &lv_font_montserrat_28, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_object_set_themeable_style_property(lv_dropdown_get_list(cui_Dropdown____Drop),  LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_COLOR, _ui_theme_color_Dark_blue);
    ui_object_set_themeable_style_property(lv_dropdown_get_list(cui_Dropdown____Drop),  LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_OPA, _ui_theme_alpha_Dark_blue);
    lv_obj_set_style_text_letter_space(lv_dropdown_get_list(cui_Dropdown____Drop), 0,  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(lv_dropdown_get_list(cui_Dropdown____Drop), 20,  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(lv_dropdown_get_list(cui_Dropdown____Drop), &ui_font_P2_SBold,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(lv_dropdown_get_list(cui_Dropdown____Drop), 8,  LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_object_set_themeable_style_property(lv_dropdown_get_list(cui_Dropdown____Drop),  LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_BG_COLOR, _ui_theme_color_Disabled);
    ui_object_set_themeable_style_property(lv_dropdown_get_list(cui_Dropdown____Drop),  LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_BG_OPA, _ui_theme_alpha_Disabled);
    lv_obj_set_style_pad_left(lv_dropdown_get_list(cui_Dropdown____Drop), 8,  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(lv_dropdown_get_list(cui_Dropdown____Drop), 8,  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(lv_dropdown_get_list(cui_Dropdown____Drop), 8,  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(lv_dropdown_get_list(cui_Dropdown____Drop), 8,  LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_object_set_themeable_style_property(lv_dropdown_get_list(cui_Dropdown____Drop),  LV_PART_SELECTED | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_COLOR, _ui_theme_color_White);
    ui_object_set_themeable_style_property(lv_dropdown_get_list(cui_Dropdown____Drop),  LV_PART_SELECTED | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_OPA, _ui_theme_alpha_White);
    ui_object_set_themeable_style_property(lv_dropdown_get_list(cui_Dropdown____Drop),  LV_PART_SELECTED | LV_STATE_DEFAULT,
                                           LV_STYLE_BG_COLOR, _ui_theme_color_Dark_blue);
    ui_object_set_themeable_style_property(lv_dropdown_get_list(cui_Dropdown____Drop),  LV_PART_SELECTED | LV_STATE_DEFAULT,
                                           LV_STYLE_BG_OPA, _ui_theme_alpha_Dark_blue);
    ui_object_set_themeable_style_property(lv_dropdown_get_list(cui_Dropdown____Drop),  LV_PART_SELECTED | LV_STATE_CHECKED,
                                           LV_STYLE_TEXT_COLOR, _ui_theme_color_White);
    ui_object_set_themeable_style_property(lv_dropdown_get_list(cui_Dropdown____Drop),  LV_PART_SELECTED | LV_STATE_CHECKED,
                                           LV_STYLE_TEXT_OPA, _ui_theme_alpha_White);
    ui_object_set_themeable_style_property(lv_dropdown_get_list(cui_Dropdown____Drop),  LV_PART_SELECTED | LV_STATE_CHECKED,
                                           LV_STYLE_BG_COLOR, _ui_theme_color_Dark_blue);
    ui_object_set_themeable_style_property(lv_dropdown_get_list(cui_Dropdown____Drop),  LV_PART_SELECTED | LV_STATE_CHECKED,
                                           LV_STYLE_BG_OPA, _ui_theme_alpha_Dark_blue);

    lv_obj_t ** children = lv_malloc(sizeof(lv_obj_t *) * _UI_COMP_CONTAINER____DROPDOWN_NUM);
    children[UI_COMP_CONTAINER____DROPDOWN_CONTAINER____DROPDOWN] = cui_Container____Dropdown;
    children[UI_COMP_CONTAINER____DROPDOWN_CONTAINER____LABEL_GROUP] = cui_Container____Label_Group;
    children[UI_COMP_CONTAINER____DROPDOWN_CONTAINER____LABEL_GROUP_LABEL____TITLE] = cui_Label____Title;
    children[UI_COMP_CONTAINER____DROPDOWN_DROPDOWN____DROP] = cui_Dropdown____Drop;
    lv_obj_add_event_cb(cui_Container____Dropdown, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_Container____Dropdown, del_component_child_event_cb, LV_EVENT_DELETE, children);
    ui_comp_Container____Dropdown_create_hook(cui_Container____Dropdown);
    return cui_Container____Dropdown;
}

