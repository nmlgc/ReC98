ifdef MASTERMOD
; Horizontal pixel mask pattern applied when drawing trapezoids, interpreted
; as a 16-pixel grid tiled across the screen. Pixels are only drawn if the
; corresponding bit in this mask is set. Only used in TH03 in the transition
; effect after the end-of-stage tally.
trapezoid_hmask dw 0ffffh
endif
