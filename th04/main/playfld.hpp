#include "th02/main/playfld.hpp"

// Fills the playfield area on the text RAM with transparent spaces.
void near playfield_tram_wipe(void);
// Fills the playfield area on the text RAM with black, effectively hiding the
// playfield in the process.
void near playfield_tram_black(void);
