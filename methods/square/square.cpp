#include "../../api.h"

class Squarer : public Plugin
{
public:
    Squarer() : Plugin("Square", "I multiply my input by itself", DOUBLE_PRIMITIVE, DOUBLE_PRIMITIVE)
    {};
    void *method(void *data);
};

void *Squarer::method(void *data)
{
    double initial = *(double*)data;
    return new double(initial * initial);
}

extern "C" {

    LIB_EXPORT Plugin * pipeline_init(void)
    {
        return new Squarer();
    }

}
