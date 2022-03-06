extern unsigned char stage_id;
extern nearfunc_t_near stage_invalidate;
extern nearfunc_t_near stage_render;

// Grants the stage clear bonus and renders its tally to text RAM.
void near stage_clear_bonus(void);

// Grants the clear bonus for the final stage, and renders its tally to text
// RAM.
void near stage_allclear_bonus(void);
