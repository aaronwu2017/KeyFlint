#include <stdio.h>
#include "lv_keyboard_seed.h"
#include "../../../../../uBitcoin/src/utility/trezor/bip39_english.h"
#include "../../../../../../Flint/Trie.h"
#if LV_USE_BTNMATRIX
#include <stdbool.h>
static TrieNode *myTrie = NULL;
// static int hiddenletterTracker[26] = {0}; 
static TrieNode *currentNode = NULL;
static int verticalIndex;
static int letterTobtnm_mapIndex[26] = {10, 24, 22, 12, 2, 13, 14, 15, 7, 16, 17, 18, 26, 25, 8, 9, 0, 3, 11, 4, 6, 23, 1, 21, 5, 20};

//lv_btnmatrix_set_btn_ctrl(obj, letterTobtnm_mapIndex[23] 21 / , LV_BTNMATRIX_CTRL_HIDDEN);
void btnm_event_handler1(lv_event_t * e) {
    char strtest[12];
    TrieNode *testNode = NULL;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    uint16_t btn_id = lv_btnmatrix_get_selected_btn(obj);
    const char * txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));
    lv_obj_t * ta = lv_event_get_user_data(e);
    int index = txt[0] - 'a';

    if (myTrie == NULL) {
        myTrie = createNode();  
        for (int i = 0; i < 2048; i++) {
            insert(myTrie, wordlist[i]);  // Insert words into the trie
        }
        currentNode = myTrie;
    }
myTrie->parent = NULL;
    // testNode = myTrie->children[16];
     //lv_textarea_add_text(ta, "already rokljk;lot");

    if (strcmp(txt, LV_SYMBOL_BACKSPACE) == 0) {
        lv_textarea_del_char(ta);
        //return if current Node is root
         lv_textarea_add_text(ta, "chilren: ");
        
        if(currentNode->parent == NULL){
            lv_textarea_add_text(ta, "already root");
            return;    
        }
        currentNode = currentNode->parent;
       for (int i = 0; i < 26; i++) {
            if (currentNode->children[i] != NULL) {
                sprintf(strtest, "%d", i);
                lv_textarea_add_text(ta, strtest);
            }
        }
        lv_textarea_add_text(ta, "parent: ");
       // bool parentnull = currentNode->parent == NULL;
         lv_textarea_add_text(ta, "parent: ");
         if(currentNode->parent == NULL){
            lv_textarea_add_text(ta, "null");
         }else{
            lv_textarea_add_text(ta, "non null");
            // currentNode = currentNode->parent;
            //  for (int i = 0; i < 26; i++) {
            // if (currentNode->children[i] != NULL) {
            //     sprintf(strtest, "%d", i);
            //     lv_textarea_add_text(ta, strtest);
            // }
         }
        for (int horizontalIndex = 0; horizontalIndex < 26; horizontalIndex++) {
            //hiddenletterTracker[horizontalIndex] = 0;
            lv_btnmatrix_clear_btn_ctrl(obj, letterTobtnm_mapIndex[horizontalIndex], LV_BTNMATRIX_CTRL_HIDDEN);
            if (currentNode->children[horizontalIndex] == NULL) {
                //hiddenletterTracker[horizontalIndex] = 1;
                lv_btnmatrix_set_btn_ctrl(obj, letterTobtnm_mapIndex[horizontalIndex], LV_BTNMATRIX_CTRL_HIDDEN);
            }
        }
        return;
    }
        


    

    if (currentNode && currentNode->children[index] != NULL) {
        currentNode = currentNode->children[index];
    }

    if (currentNode->isEndOfWord == 1) {
        for (int i = 0; i < 26; i++) {
            // if (hiddenletterTracker[i] == 1) {
                lv_btnmatrix_clear_btn_ctrl(obj, i, LV_BTNMATRIX_CTRL_HIDDEN);
            // }
        }
        lv_textarea_add_text(ta, " ");
        // for (int i = 0; i < 26; i++) {
        //     hiddenletterTracker[i] = 0;
        // }
        return;
    }

    for (int i = 0; i < 26; i++) {
        //hiddenletterTracker[i] = 0;
        lv_btnmatrix_clear_btn_ctrl(obj, i, LV_BTNMATRIX_CTRL_HIDDEN);
    }

    for (int horizontalIndex = 0; horizontalIndex < 26; horizontalIndex++) {
        if (currentNode->children[horizontalIndex] == NULL) {
            //hiddenletterTracker[horizontalIndex] = 1;
            lv_btnmatrix_set_btn_ctrl(obj, letterTobtnm_mapIndex[horizontalIndex], LV_BTNMATRIX_CTRL_HIDDEN);
        }
    } 
    lv_textarea_add_text(ta, txt);
}


static const char * btnm_map[] = {"q", "w", "e", "r", "t", "y","u","i", "o","p","\n",
                                  "a", "s", "d", "f", "g","h","j","k","l", "\n",
                                  LV_SYMBOL_BACKSPACE,"z", "x", "c", "v", "b","n","m","go",""
                                   };

lv_obj_t * lv_ex_btnmatrix_1(lv_obj_t * obj)
{
    
    // for (int i = 0; wordlist[i] != nullptr; ++i) {
    //     trie.insert(wordlist[i]);
    // }
    lv_obj_t * btnm1 = lv_btnmatrix_create(obj);
   lv_btnmatrix_set_map(btnm1, btnm_map);
    // lv_btnmatrix_set_btn_width(btnm1, 10, 2);        /*Make "Action1" twice as wide as "Action2"*/
    // lv_btnmatrix_set_btn_ctrl(btnm1, 10, LV_BTNMATRIX_CTRL_CHECKABLE);
    lv_btnmatrix_set_btn_ctrl(btnm1, 27, LV_BTNMATRIX_CTRL_CHECKED);
    lv_obj_align(btnm1, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_add_event_cb(btnm1, btnm_event_handler1, LV_EVENT_ALL, NULL);
     return btnm1;
}

#endif