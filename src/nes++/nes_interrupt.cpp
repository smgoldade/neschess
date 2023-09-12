// Author: Steven Goldade
#include "nes_ppu.h"

extern "C" __attribute__((interrupt_norecurse)) void nmi() {
    if(nespp::ppu->is_rendering()) {
        nespp::ppu->nmi_update();
    }
}
