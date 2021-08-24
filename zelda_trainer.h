#ifndef ZELDA_TRAINER_H
#define ZELDA_TRAINER_H

#include "trainer_base.h"

const std::wstring MODULE = L"bsnes_libretro.dll";

const uintptr_t OFFSETS[] = {
    0x576C7C, // Rupees
    0x576C5F, // Bombs
    0x576C93, // Arrows
};

struct Consumables {
    uint16_t rupees;
    uint8_t bombs;
    uint8_t arrows;
};

class ZeldaTrainer : public TrainerBase {

public:
    ZeldaTrainer();
    ZeldaTrainer(const wchar_t* window_name);

    struct Consumables consumables;

    int populate_consumables();
};

#endif // ZELDA_TRAINER_H
