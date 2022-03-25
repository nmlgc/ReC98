extern bool palette_changed;

// Updates the actual hardware palette at the end of the frame.
inline void palette_settone_deferred(unsigned int tone) {
	PaletteTone = tone;
	palette_changed = true;
}
