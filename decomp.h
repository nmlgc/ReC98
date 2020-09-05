/* ReC98
 * -----
 * Macros to help decompiling the seemingly impossible
 */

// Flag comparisons
// ----------------
// When used inside a conditional expression like
//	if(FLAGS_*) { goto some_label; | return; }
// these assemble into the single given instruction. Apply the ! operator to
// get the N versions.
#define FLAGS_ZERO (_FLAGS & 0x40) /* JZ */
// ----------------
