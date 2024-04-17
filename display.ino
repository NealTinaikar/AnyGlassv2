void drawStaticScreen() {
    // Set font and other display settings
    u8g2.setFont(u8g2_font_profont10_mr);
    u8g2.drawStr(0, 10, staticText);
}

void drawScrollingScreen() {
//    u8g2.drawStr(0, 10, "Listening");
//    i2s_adc();
//    u8g2.clearBuffer();
//    u8g2.sendBuffer();
//    u8g2.drawStr(0, 10, "Uploading");
//    i2s_adc();
//    chatgpt();
//    const char *result = chatgpt_R.c_str();
//    u8g2.clearBuffer();
//    u8g2.sendBuffer();
    // Set font and other display settings
    u8g2.setFont(u8g2_font_profont10_mr);

    // Calculate the maximum number of characters that can be displayed horizontally
    int maxChars = u8g2.getDisplayWidth() / u8g2.getMaxCharWidth();

    // Calculate the vertical offset
    static int xOffset = 0;

    // Start drawing
    u8g2.firstPage();
    do {
        u8g2.drawStr(-xOffset, 10, result);
    } while (u8g2.nextPage());

    // Increment the horizontal offset for scrolling effect
    xOffset++;

    // Reset the offset if it exceeds the length of the string
    if (xOffset >= strlen(result) * u8g2.getMaxCharWidth()) {
        xOffset = 0;
    }
}
