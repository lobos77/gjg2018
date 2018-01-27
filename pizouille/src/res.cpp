#include "res.h"

namespace res
{
    Resources ui;

    void load()
    {
        //load our resources
        ui.loadXML("res/xmls/ui.xml");
    }

    void free()
    {
        //unload
        ui.free();
    }
}