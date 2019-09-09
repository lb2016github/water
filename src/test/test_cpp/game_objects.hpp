#include "component_object.hpp"


struct AB : public ComponentObject<A, B>
{

};

struct DerivedAB : public AB
{

};