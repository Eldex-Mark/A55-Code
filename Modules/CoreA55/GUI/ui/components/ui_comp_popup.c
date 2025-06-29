// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 9.1.0
// Project name: Eldex_Optos_Touch

#include "../ui.h"


// COMPONENT Popup

lv_obj_t * ui_Panel____Popup_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_Panel____Popup;
    cui_Panel____Popup = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_Panel____Popup, lv_pct(100));
    lv_obj_set_height(cui_Panel____Popup, lv_pct(100));
    lv_obj_set_align(cui_Panel____Popup, LV_ALIGN_CENTER);
    lv_obj_remove_flag(cui_Panel____Popup, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(cui_Panel____Popup, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cui_Panel____Popup, 150, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_Panel____Card;
    cui_Panel____Card = lv_obj_create(cui_Panel____Popup);
    lv_obj_set_width(cui_Panel____Card, 516);
    lv_obj_set_height(cui_Panel____Card, LV_SIZE_CONTENT);    /// 277
    lv_obj_set_align(cui_Panel____Card, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(cui_Panel____Card, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cui_Panel____Card, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_remove_flag(cui_Panel____Card, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(cui_Panel____Card, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_object_set_themeable_style_property(cui_Panel____Card, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                           _ui_theme_color_White);
    ui_object_set_themeable_style_property(cui_Panel____Card, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_White);
    lv_obj_set_style_pad_left(cui_Panel____Card, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_Panel____Card, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_Panel____Card, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_Panel____Card, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(cui_Panel____Card, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_Panel____Card, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_Label____Title;
    cui_Label____Title = lv_label_create(cui_Panel____Card);
    lv_obj_set_width(cui_Label____Title, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_Label____Title, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_Label____Title, LV_ALIGN_CENTER);
    lv_label_set_text(cui_Label____Title, "Title");
    ui_object_set_themeable_style_property(cui_Label____Title, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Dark_blue);
    ui_object_set_themeable_style_property(cui_Label____Title, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Dark_blue);
    lv_obj_set_style_text_font(cui_Label____Title, &ui_font_P1_Bold, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_Container____Container11;
    cui_Container____Container11 = lv_obj_create(cui_Panel____Card);
    lv_obj_remove_style_all(cui_Container____Container11);
    lv_obj_set_width(cui_Container____Container11, lv_pct(100));
    lv_obj_set_height(cui_Container____Container11, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_Container____Container11, LV_ALIGN_CENTER);
    lv_obj_remove_flag(cui_Container____Container11, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(cui_Container____Container11, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_Container____Container11, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_Container____Container11, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_Container____Container11, 24, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_Label____Text;
    cui_Label____Text = lv_label_create(cui_Container____Container11);
    lv_obj_set_width(cui_Label____Text, lv_pct(100));
    lv_obj_set_height(cui_Label____Text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_Label____Text, LV_ALIGN_CENTER);
    lv_label_set_text(cui_Label____Text, "Text");
    ui_object_set_themeable_style_property(cui_Label____Text, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Dark_blue);
    ui_object_set_themeable_style_property(cui_Label____Text, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Dark_blue);
    lv_obj_set_style_text_align(cui_Label____Text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(cui_Label____Text, &ui_font_P2_SBold, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_Container____Container18;
    cui_Container____Container18 = lv_obj_create(cui_Panel____Card);
    lv_obj_remove_style_all(cui_Container____Container18);
    lv_obj_set_width(cui_Container____Container18, lv_pct(100));
    lv_obj_set_height(cui_Container____Container18, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(cui_Container____Container18, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(cui_Container____Container18, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cui_Container____Container18, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_remove_flag(cui_Container____Container18, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_row(cui_Container____Container18, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(cui_Container____Container18, 12, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_Secondarybtn____Cancel;
    cui_Secondarybtn____Cancel = ui_Button____Secondarybtn_create(cui_Container____Container18);
    lv_obj_set_width(cui_Secondarybtn____Cancel, 134);
    lv_obj_set_height(cui_Secondarybtn____Cancel, 65);
    lv_obj_set_x(cui_Secondarybtn____Cancel, 271);
    lv_obj_set_y(cui_Secondarybtn____Cancel, -16);
    lv_obj_remove_flag(cui_Secondarybtn____Cancel, LV_OBJ_FLAG_HIDDEN);      /// Flags
    lv_obj_set_style_min_height(cui_Secondarybtn____Cancel, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_max_height(cui_Secondarybtn____Cancel, 128, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_label_set_text(ui_comp_get_child(cui_Secondarybtn____Cancel, UI_COMP_BUTTON____SECONDARYBTN_LABEL____LABEL),
                      "Cancel");

    lv_obj_t * cui_Primarybtn____Next;
    cui_Primarybtn____Next = ui_Button____Primarybtn_create(cui_Container____Container18);
    lv_obj_set_x(cui_Primarybtn____Next, 0);
    lv_obj_set_y(cui_Primarybtn____Next, 0);

    lv_obj_t ** children = lv_malloc(sizeof(lv_obj_t *) * _UI_COMP_PANEL____POPUP_NUM);
    children[UI_COMP_PANEL____POPUP_PANEL____POPUP] = cui_Panel____Popup;
    children[UI_COMP_PANEL____POPUP_PANEL____CARD] = cui_Panel____Card;
    children[UI_COMP_PANEL____POPUP_PANEL____CARD_LABEL____TITLE] = cui_Label____Title;
    children[UI_COMP_PANEL____POPUP_PANEL____CARD_CONTAINER____CONTAINER11] = cui_Container____Container11;
    children[UI_COMP_PANEL____POPUP_PANEL____CARD_CONTAINER____CONTAINER11_LABEL____TEXT] = cui_Label____Text;
    children[UI_COMP_PANEL____POPUP_PANEL____CARD_CONTAINER____CONTAINER18] = cui_Container____Container18;
    children[UI_COMP_PANEL____POPUP_SECONDARYBTN____CANCEL] = cui_Secondarybtn____Cancel;
    children[UI_COMP_PANEL____POPUP_SECONDARYBTN____CANCEL_LABEL____CANCEL_LABEL] = ui_comp_get_child(
                                                                                        cui_Secondarybtn____Cancel, UI_COMP_BUTTON____SECONDARYBTN_LABEL____LABEL);
    children[UI_COMP_PANEL____POPUP_PRIMARYBTN____NEXT] = cui_Primarybtn____Next;
    children[UI_COMP_PANEL____POPUP_PRIMARYBTN____NEXT_LABEL____NEXT_LABEL] = ui_comp_get_child(cui_Primarybtn____Next,
                                                                                                UI_COMP_BUTTON____PRIMARYBTN_LABEL____LABEL);
    lv_obj_add_event_cb(cui_Panel____Popup, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_Panel____Popup, del_component_child_event_cb, LV_EVENT_DELETE, children);
    ui_comp_Panel____Popup_create_hook(cui_Panel____Popup);
    return cui_Panel____Popup;
}

