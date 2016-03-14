#include "../../api.h"

class Quarterer : public Plugin
{
public:
    Quarterer() : Plugin("Quarter", "I divide my input by 4", DOUBLE_PRIMITIVE, DOUBLE_PRIMITIVE)
    {};
    void *method(void *data);
};

void *Quarterer::method(void *data)
{
    double initial = *(double*)data;
    return new double(initial / 4);
}

extern "C" {

    LIB_EXPORT Plugin * pipeline_init(void)
    {
        return new Quarterer();
    }

}
