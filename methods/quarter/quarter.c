#include "../../api.h"

double process(double input)
{
	return input / 4;
}

LIB_EXPORT processingMethod pipeline_init(void)
{
	static processingMethod spec = {
		.name = "Quarter",
		.description = "I divide my input by four",
		.function = process,
        .options = "{factor: integer, range: {from: 1, to: 10}}"
	};

	return spec;
}
