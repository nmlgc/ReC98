GRX_COUNT = 16
PLANAR_STREAM_PER_GRX_COUNT = 16

public _rle_streams, _planar_streams, _planar_stream_count
_rle_streams	dd GRX_COUNT dup (?)
_planar_streams	dd GRX_COUNT dup (PLANAR_STREAM_PER_GRX_COUNT dup (?))
_planar_stream_count	db GRX_COUNT dup (?)
