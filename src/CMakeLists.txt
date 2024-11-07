SET(SOURCES components/ui_comp_settimg.c
    components/ui_comp.c
    screens/ui_deplay.c
    screens/ui_swifiseting.c
    screens/ui_stimeseting.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_botttt_png.c
    images/ui_img_602835949.c
    images/ui_img_do_png.c
    images/ui_img_up_png.c
    images/ui_img_filter_2_png.c
    images/ui_img_1711361369.c
    images/ui_img_11_png.c
    images/ui_img_1986391116.c
    images/ui_img_602825187.c
    images/ui_img_602820839.c
    images/ui_img_602819814.c
    fonts/ui_font_Font1.c
    fonts/ui_font_Font12.c
    fonts/ui_font_Font16.c
    fonts/ui_font_Font20.c
    fonts/ui_font_Font48.c
    fonts/ui_font_kanit28.c
    fonts/ui_font_kanit30.c)

add_library(ui ${SOURCES})
