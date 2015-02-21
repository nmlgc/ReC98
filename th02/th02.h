/* ReC98
 * -----
 * Include file for TH02
 */

#define PI_SLOTS 6

// Formats
extern void far *pi_slot_buffers[PI_SLOTS];
extern PiHeader pi_slot_headers[PI_SLOTS];

void pi_slot_put(int x, int y, int slot);

// Hardware
void snd_se_reset(void);
void snd_se_play(unsigned char se);
void snd_se_update(void);

void pascal frame_delay(int frames);
