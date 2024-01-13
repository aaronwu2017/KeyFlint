#include <stdio.h>
#include "lv_keyboard_binary.h"


#if LV_USE_BTNMATRIX

void btnm_event_handler2(lv_event_t * e) {
char strtest[12];

lv_event_code_t code = lv_event_get_code(e);
lv_obj_t * obj = lv_event_get_target(e);
uint16_t btn_id = lv_btnmatrix_get_selected_btn(obj);
const char * txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));
lv_obj_t * ta = lv_event_get_user_data(e);

const char * fullEnteredText = lv_textarea_get_text(ta) ;

  

    if(strcmp(txt, "go") == 0) {
       lv_event_send(obj, LV_EVENT_READY, NULL);
     //    lv_event_send(obj, LV_EVENT_READY, ta);
         generateSeed(fullEnteredText);

    }





    if (strcmp(txt, LV_SYMBOL_BACKSPACE) == 0) {
      
      
        return;
    }

   
    lv_textarea_add_text(ta, txt);
    
}

//     static const char * kb_map[] = {"0000", "0001", "0010", "0011", "\n", "0100", "0101", "0110", "0111", "\n", "1000", "1001",  "\n",
//     "1010", "1011", "\n", "1100", "1101", "1110", "1111", 
// LV_SYMBOL_BACKSPACE,  "go", NULL
//     };
     static const char * kb_map[] = {"0000", "0001", "0010", "0011","\n", "0100", "0101", "0110", "0111", "\n","1000", "1001",
                                    "1010", "1011", "\n","1100", "1101", "1110", "1111", 
                                    "\n",LV_SYMBOL_BACKSPACE, "go", ""
                                   };

lv_obj_t * lv_ex_btnmatrix_binary(lv_obj_t * obj)
{
    

    lv_obj_t * btnm2 = lv_btnmatrix_create(obj);
   lv_btnmatrix_set_map(btnm2, kb_map);

    lv_btnmatrix_set_btn_ctrl(btnm2, 18, LV_BTNMATRIX_CTRL_CHECKED);
    lv_obj_align(btnm2, LV_ALIGN_CENTER, 0, 0);

     return btnm2;
}

#endif