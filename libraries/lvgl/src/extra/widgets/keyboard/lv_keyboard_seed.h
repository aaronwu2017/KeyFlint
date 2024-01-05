#ifndef LV_EX_BTNMATRIX_H
#define LV_EX_BTNMATRIX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#if LV_USE_BTNMATRIX

/**
 * @brief Event handler for button matrix.
 * 
 * This function is called when an event occurs on the button matrix.
 * 
 * @param obj The object that triggered the event.
 * @param event The event that occurred.
 */
void btnm_event_handler1(lv_event_t * e);

/**
 * @brief Create and configure a button matrix.
 * 
 * This function creates a new button matrix on the current active screen,
 * sets up its buttons, and assigns the event handler.
 */
lv_obj_t * lv_ex_btnmatrix_1(lv_obj_t * obj);

#endif /* LV_USE_BTNMATRIX */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_EX_BTNMATRIX_H */
