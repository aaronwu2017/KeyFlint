#include <stdio.h>
#include "lv_keyboard_seed.h"
#include "../../../../../uBitcoin/src/utility/trezor/bip39_english.h"
#include "../../../../../../Flint/Trie.h"
#if LV_USE_BTNMATRIX
static TrieNode *myTrie = NULL;
static TrieNode *currentNode = NULL;
static int letterTobtnm_mapIndex[26] = {10, 24, 22, 12, 2, 13, 14, 15, 7, 16, 17, 18, 26, 25, 8, 9, 0, 3, 11, 4, 6, 23, 1, 21, 5, 20};
void btnm_event_handler1(lv_event_t * e) {
char strtest[12];
TrieNode *testNode = NULL;
lv_event_code_t code = lv_event_get_code(e);
lv_obj_t * obj = lv_event_get_target(e);
uint16_t btn_id = lv_btnmatrix_get_selected_btn(obj);
const char * txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));
lv_obj_t * ta = lv_event_get_user_data(e);
int index = txt[0] - 'a';
const char * fullEnteredText = lv_textarea_get_text(ta) ;

    if (myTrie == NULL) {
        myTrie = createNode(0);  
        for (int i = 0; i < 2048; i++) {
            insert(myTrie, wordlist[i],i);  // Insert words into the trie
           
        }
        currentNode = myTrie;
   
    }
    myTrie->parent = NULL;

    if(strcmp(txt, "go") == 0) {
        lv_event_send(obj, LV_EVENT_READY, NULL);
        //  lv_event_send(obj, LV_EVENT_READY, ta);
        initiateKeyPair(fullEnteredText);
        //  initiateKeyPair(fullEnteredText);
    }



if (strcmp(txt, "space") == 0) {
    if (currentNode->isEndOfWord == 0) {
        return;
    } 
    if (fullEnteredText != NULL && strlen(fullEnteredText) > 0) { // Ensure the string is not NULL and not empty
        char lastCharacter = fullEnteredText[strlen(fullEnteredText) - 1]; // Get the last character of the text
        if (lastCharacter != ' ') { // Check if the last character is not a space
            lv_textarea_add_text(ta, " "); // Add a space only if the last character is not a space
            currentNode = myTrie;
            for (int i = 0; i < 26; i++) {
                lv_btnmatrix_clear_btn_ctrl(obj, letterTobtnm_mapIndex[i], LV_BTNMATRIX_CTRL_HIDDEN);
             }
             lv_btnmatrix_set_btn_ctrl(obj, letterTobtnm_mapIndex[23], LV_BTNMATRIX_CTRL_HIDDEN);
        }
        // If the last character is a space, do nothing
    } 
    return; // Return after handling the "space" case
}


    if (strcmp(txt, LV_SYMBOL_BACKSPACE) == 0) {
        
        if(currentNode->parent == NULL){
            const char *lastSpace = strrchr(fullEnteredText, ' ');
            if (lastSpace != NULL) {
                const char *lastWord = fullEnteredText;
                for (const char *p = lastSpace - 1; p > fullEnteredText; --p) {
                    if ( *(p - 1) == ' '&&*p != ' ') {
                        lastWord = p;
                        break;
                    }
                }
               
            // const char *lastWord =  lastSpace-8;
                for (const char *p = lastWord; p <= lastSpace; p++) {
                  if (*p == ' ') {
                        lv_textarea_del_char(ta);
                    } else{
                        int lastWordLetterIndex = *p - 'a';
                        currentNode = currentNode->children[lastWordLetterIndex];
                    }                 
                }
            }else{
           //no text on the textarea
                return;    
            }

        }
        currentNode = currentNode->parent;
        lv_textarea_del_char(ta);
        for (int horizontalIndex = 0; horizontalIndex < 26; horizontalIndex++) {

            lv_btnmatrix_clear_btn_ctrl(obj, letterTobtnm_mapIndex[horizontalIndex], LV_BTNMATRIX_CTRL_HIDDEN);
            if (currentNode->children[horizontalIndex] == NULL) {

                lv_btnmatrix_set_btn_ctrl(obj, letterTobtnm_mapIndex[horizontalIndex], LV_BTNMATRIX_CTRL_HIDDEN);
            }
        }
        return;
    }

    if (currentNode && currentNode->children[index] != NULL) {
        currentNode = currentNode->children[index];
    }

    for (int i = 0; i < 26; i++) {
        lv_btnmatrix_clear_btn_ctrl(obj, letterTobtnm_mapIndex[i], LV_BTNMATRIX_CTRL_HIDDEN);
    }
    lv_textarea_add_text(ta, txt);



    int hasChild = 0;
    for (int i = 0; i < 26; i++) {
        if (currentNode->children[i] != NULL) {
            hasChild = 1;
            break;
        }
    }


    if (currentNode->isEndOfWord == 1 && hasChild ==0) {
 //lv_btnmatrix_set_map(btnm1, btnm_map_go);



              lv_textarea_add_text(ta, " ");
         //  sprintf(strtest, "%d", (currentNode->bip39Number));
               // lv_textarea_add_text(ta, strtest);
        // for(int j = 0;j<9-currentNode->level;j++){
        //     lv_textarea_add_text(ta, " ");
        // }
                currentNode = myTrie;
    } else{
        for (int horizontalIndex = 0; horizontalIndex < 26; horizontalIndex++) {
                if (currentNode->children[horizontalIndex] == NULL) {
                    lv_btnmatrix_set_btn_ctrl(obj, letterTobtnm_mapIndex[horizontalIndex], LV_BTNMATRIX_CTRL_HIDDEN);
                }
        } 
    }
    if(currentNode == myTrie){
         //disable x  as bip39 word list doesnot have word starting with x
       lv_btnmatrix_set_btn_ctrl(obj, letterTobtnm_mapIndex[23], LV_BTNMATRIX_CTRL_HIDDEN);
    }
}

static const char * btnm_map_go[] = {"q", "w", "e", "r", "t", "y","u","i", "o","p","\n",
                                  "a", "s", "d", "f", "g","h","j","k","l", "\n",
                                  LV_SYMBOL_BACKSPACE,"z", "x", "c", "v", "b","n","m","go222222",""
                                   };


static const char * btnm_map[] = {"q", "w", "e", "r", "t", "y","u","i", "o","p","\n",
                                  "a", "s", "d", "f", "g","h","j","k","l", "\n",
                                  LV_SYMBOL_BACKSPACE,"z", "x", "c", "v", "b","n","m","space","go",""
                                   };

                                //     static const char * kb_map[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", LV_SYMBOL_BACKSPACE, "\n",
                                //     "1010", "1011", "1100", "1101", "1110", "1111", "K", "L", "M",  LV_SYMBOL_NEW_LINE, "\n",
                                //     "W", "X", "C", "V", "B", "N", ",", ".", ":", "!", "?", "\n",
                                //     LV_SYMBOL_CLOSE, " ",  " ", " ", LV_SYMBOL_OK, NULL
                                //    };

lv_obj_t * lv_ex_btnmatrix_seed(lv_obj_t * obj)
{
    

    lv_obj_t * btnm1 = lv_btnmatrix_create(obj);
   lv_btnmatrix_set_map(btnm1, btnm_map);
 lv_btnmatrix_set_btn_width(btnm1, 27,  50);

  //  lv_btnmatrix_set_btn_ctrl(btnm1, 27, LV_BTNMATRIX_CTRL_CHECKED);
    lv_obj_align(btnm1, LV_ALIGN_CENTER, 0, 0);

     return btnm1;
}

#endif