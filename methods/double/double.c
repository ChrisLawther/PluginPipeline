#include "../../api.h"

double process(double input)
{
	return 2 * input;
}

LIB_EXPORT processingMethod pipeline_init(void)
{
	static processingMethod spec = {
		.name = "Double",
		.description = "I double my input",
		.function = process
	};

	return spec;
}
