SET(SOURCES components/ui_comp_settimg.c
    components/ui_comp.c
    screens/ui_deplay.c
    screens/ui_swifiseting.c
    screens/ui_stimeseting.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_botttt_png.c
    images/ui_img_427252146.c
    images/ui_img_1711361369.c
    images/ui_img_11_png.c
    images/ui_img_1986391116.c
    images/ui_img_602825187.c)

add_library(ui ${SOURCES})
