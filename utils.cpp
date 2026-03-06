#include "utils.h"

const std::string vardai[] = {"Jonas", "Petras", "Antanas", "Kazys", "Linas",
                               "Marius", "Tomas", "Andrius", "Darius", "Gediminas"};
const std::string pavardes[] = {"Jonaitis", "Petraitis", "Antanaitis", "Kazlauskas", "Lingys",
                                "Mariūnas", "Tomauskas", "Andriulis", "Dargis", "Gedminas"};

int getVarduKiekis() {
    return sizeof(vardai) / sizeof(vardai[0]);
}

int getPavardziuKiekis() {
    return sizeof(pavardes) / sizeof(pavardes[0]);
}
