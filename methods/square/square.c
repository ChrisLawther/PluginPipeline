#include "../../api.h"

double process(double input)
{
	return input * input;
}

LIB_EXPORT processingMethod pipeline_init(void)
{
	static processingMethod spec = {
		.name = "Square",
		.description = "I multiply my input by itself",
		.function = process
	};

	return spec;
}
