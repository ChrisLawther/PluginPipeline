#include "../../api.h"

class Doubler : public Plugin {
public:
    Doubler() : Plugin("Double", "I double my input", DOUBLE_PRIMITIVE, DOUBLE_PRIMITIVE) {};
    void *method(void *data);
};

void *Doubler::method(void *data)
{
    double initial = *(double*)data;
    return new double(initial * 2);
}

extern "C" {
    
LIB_EXPORT Plugin *pipeline_init(void)
{
    return new Doubler();
}

}
