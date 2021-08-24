#include "zelda_trainer.h"

ZeldaTrainer::ZeldaTrainer() {  }

ZeldaTrainer::ZeldaTrainer(const wchar_t* window_name) : TrainerBase(window_name) { }

int ZeldaTrainer::populate_consumables() {
    uintptr_t address = mod_addr[MODULE];

    uint16_t rupees = read_mem_double_byte(address + OFFSETS[0]);
    uint8_t bombs = read_mem_byte(address + OFFSETS[1]);
    uint8_t arrows = read_mem_byte(address + OFFSETS[2]);

    consumables = { rupees, bombs, arrows };

    return 1;
}
