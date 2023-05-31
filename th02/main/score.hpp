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
