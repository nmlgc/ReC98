// ID of the next dialog box to be shown.
extern uint8_t dialog_box_cur;

// Loads the dialog text file for the current stage into the internal,
// statically allocated buffer, and resets [dialog_box_cur].
void dialog_load_and_init(void);

// Stage-specific hardcoded "scripts"
// ----------------------------------
// All of these start at [dialog_box_cur] within the text previously loaded via
// dialog_load_and_init(), and increment that variable for every box displayed.

enum dialog_sequence_t {
	DS_PREBOSS = 0,
	DS_POSTBOSS = 1,
	DS_COUNT = 2,

	_dialog_sequence_t_FORCE_INT16 = 0x7FFF,
};

// Shows the generic part of the current stage's given dialog [sequence], using
// hardcoded face IDs and box counts.
void pascal near dialog_script_generic_part_animate(dialog_sequence_t sequence);

// Naming convention for these dedicated script functions:
//
// 	dialog_script_(<stage>)_(<sequence>)(_<part>)?_animate()
void near dialog_script_stage2_pre_intro_animate(void);
void near dialog_script_stage4_pre_intro_animate(void);
void near dialog_script_stage4_pre_marisa_animate(void);
void near dialog_script_stage4_post_animate(void);
// ----------------------------------
