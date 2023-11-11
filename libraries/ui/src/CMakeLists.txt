SET(SOURCES screens/ui_Screen1.c
    screens/ui_Screen2.c
    screens/ui_Screen3.c
    screens/ui_Screen4.c
    screens/ui_Screen5.c
    screens/ui_Screen6.c
    screens/ui_Screen7.c
    screens/ui_Screen8.c
    screens/ui_Screen9.c
    screens/ui_Screen10.c
    screens/ui_Screen11.c
    screens/ui_Screen12.c
    screens/ui_Screen13.c
    screens/ui_Screen14.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_1882376574.c)

add_library(ui ${SOURCES})
