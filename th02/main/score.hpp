// ZUN quirk: Terminated with an "impossibly high" sentinel value of
// (99,999,999 × 10), and no usage code checks against the size of the array.
// Classifying as a quirk for the time being, until we can prove the maximum
// possible score within all the original stage and boss scripts. This score
// will reveal how many elements of this array we would need to preserve – or
// turn this into a landmine if that maximum score is indeed below ZUN's
// assumption of (99,999,999 × 10).
extern const int32_t EXTEND_SCORES[];

extern unsigned int extends_gained;
extern int32_t score_delta;
extern int32_t hiscore;

// Adds the entire [score_delta] at once to the current score, but does not
// re-render it.
void score_delta_commit(void);

// Resets all score variables, including [score_delta] to 0. Used after
// continuing, and when starting a new stage to avoid the quirk from
// score_grant_current_delta_as_bonus().
void near score_reset(void);

// Transfers a part of the [score_delta] to [score], grants extra lives or
// bombs upon reaching the thresholds in [EXTEND_SCORES], and updates the UI
// accordingly.
void near score_update_and_render(void);

// Adds the current [score_delta] to [score] as an immediate bonus, without
// resetting [score_delta] to 0 afterward. Also grants extra lives or bombs
// upon reaching the thresholds in [EXTEND_SCORES], and updates the UI
// accordingly.
//
// Since it makes little sense to derive a score bonus from what's essentially
// an implementation detail, calling this function by itself is always a quirk.
// To avoid the quirky effect and turn this function into the equivalent of
// score_delta_commit() with re-rendering, make sure to reset [score_delta]
// before the next call to score_update_and_render().
void score_grant_current_delta_as_bonus(void);
