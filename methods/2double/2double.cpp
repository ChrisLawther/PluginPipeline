#include "../../api.h"

class ToDouble : public Plugin {
public:
    ToDouble() : Plugin("2Double", "I convert unsigneds to doubles", UNSIGNED_PRIMITIVE, DOUBLE_PRIMITIVE) {};
    void *method(void *data);
};

void *ToDouble::method(void *data)
{
    double initial = (double)*(unsigned*)data;
    return new double(initial);
}

extern "C" {
    
LIB_EXPORT Plugin * pipeline_init(void)
{
    return new ToDouble();
}

}
