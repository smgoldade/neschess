/**
 * Author: Steven Goldade
 */
#include "nes/nes.h"

extern void nmi() {

}

u8 palette[] = {
    BLACK, WHITE, DARK_GRAY, MEDIUM_GRAY
};
u8 message[] = "Hello World!";
int main(void) {
    ppu_off();
    ppu_set_addr(BACKGROUND_COLOR);
    ppu_write(palette, sizeof(palette));

    ppu_set_addr(NT0_ADDR(10, 14));
    ppu_write(message, sizeof(message));
    ppu_on();

    while (1) {

    }
    return 0;
}