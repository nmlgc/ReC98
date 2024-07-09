; Everything here needs to be kept in sync with the C++ versions in spark.hpp!

include libs/master.lib/macros.inc
include th02/main/entity.inc
include th04/math/motion.inc

spark_t struc
	flag       	db ?
	age        	db ?
	pos        	motion_t <?>
	SPARK_angle	dw ?
spark_t ends

if (GAME eq 5)
	SPARK_COUNT = 64
else
	SPARK_COUNT = 96
endif
SPARK_COUNT_BUG = 96
