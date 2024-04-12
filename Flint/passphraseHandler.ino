void passphraseSwitcherHandler() {
    const std::string& mnemonicsString = KeyManager::getInstance().getMnemonicsString();

    // true means the switch is on
    if (lv_obj_has_state(ui_Switch111, LV_STATE_CHECKED)) {
        Serial.println("on");
        lv_label_set_text(ui_Label1114, "ON");

        const char *passphrase = lv_textarea_get_text(ui_TextArea113);
        HDPrivateKey hd(mnemonicsString.c_str(), passphrase);
        KeyManager::getInstance().setHDPrivateKey(&hd);
        Serial.println(passphrase);
    } else {
        // false means the switch is off
        Serial.println("off");
        HDPrivateKey hd(mnemonicsString.c_str());
        KeyManager::getInstance().setHDPrivateKey(&hd);
        lv_label_set_text(ui_Label1114, "OFF");
    }
}
