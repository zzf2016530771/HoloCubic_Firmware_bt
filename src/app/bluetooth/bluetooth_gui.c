#include "bluetooth_gui.h"

#include "driver/lv_port_indev.h"
#include "lvgl.h"
#include "stdio.h"


lv_obj_t *blurtooth_gui=NULL;

lv_obj_t *bluetooth_text=NULL;

static lv_style_t default_style;
static lv_style_t b_lable_stytle;

LV_FONT_DECLARE(lv_font_montserrat_24);//字体大小24号

void bluetooth_gui_init(void)
{
    blurtooth_gui=NULL;

    lv_style_init(&default_style);
    lv_style_set_bg_color(&default_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_bg_color(&default_style, LV_STATE_PRESSED, LV_COLOR_GRAY);
    lv_style_set_bg_color(&default_style, LV_STATE_FOCUSED, LV_COLOR_BLACK);
    lv_style_set_bg_color(&default_style, LV_STATE_FOCUSED | LV_STATE_PRESSED, lv_color_hex(0xf88));

    blurtooth_gui=lv_obj_create(NULL,NULL);//创建屏幕对象
    lv_obj_add_style(blurtooth_gui,LV_BTN_PART_MAIN,&default_style);//将创建的新样式添加到对象的样式列表

    lv_style_init(&b_lable_stytle);
    lv_style_set_bg_opa(&b_lable_stytle,LV_STATE_DEFAULT,LV_OPA_COVER);
    lv_style_set_bg_color(&b_lable_stytle,LV_STATE_DEFAULT,LV_COLOR_WHITE);
    lv_style_set_bg_font(&b_lable_stytle,LV_STATE_DEFAULT,&lv_font_montserrat_24);

}

void display_bluetooth_init(void)
{
    lv_obj_t *act_obj = lv_scr_act(); // 获取当前活动页
    if (act_obj == blurtooth_gui)
        return;
    if(bluetooth_text!=NULL){
        lv_obj_clean(bluetooth_text);
    }
    lv_obj_clean(act_obj);// 清空此前页面
    bluetooth_text=lv_label_create(blurtooth_gui,NULL);
    
}


void display_bluetooth(const char *text,lv_scr_load_anim_t anim_type)
{
    display_bluetooth_init();

    lv_obj_add_style(bluetooth_text, LV_LABEL_PART_MAIN, &b_lable_stytle);
    lv_label_set_text(bluetooth_text, text);
    lv_obj_align(bluetooth_text, NULL, LV_ALIGN_OUT_BOTTOM_LEFT, 5, -120);

    lv_scr_load(blurtooth_gui);
}

void bluetooth_gui_del(void)
{
    if(NULL!=blurtooth_gui){
        lv_obj_clean(blurtooth_gui);
        blurtooth_gui=NULL;
    }

    if(bluetooth_text!=NULL){
        lv_obj_clean(bluetooth_text);
        bluetooth_text=NULL;
    }
}