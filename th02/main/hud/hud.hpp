// Coordinates
// -----------

static const tram_x_t HUD_LEFT = 56;

static const tram_y_t HUD_POWER_Y = 20;

static const tram_cell_amount_t HUD_LABEL_PADDING = 1;
static const tram_cell_amount_t HUD_LABEL_W = (2 * GAIJI_TRAM_W);
static const tram_cell_amount_t HUD_LABEL_PADDED_W = (
	HUD_LABEL_PADDING + HUD_LABEL_W + HUD_LABEL_PADDING
);

static const tram_x_t HUD_LABELED_LEFT = (HUD_LEFT + HUD_LABEL_PADDED_W);
// -----------

// Yup, this also commits changes to [power] to the [shot_level], which
// absolutely doesn't belong here.
void near player_shot_level_update_and_hud_power_put(void);
