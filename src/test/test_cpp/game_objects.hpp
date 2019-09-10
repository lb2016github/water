#include "component_object.hpp"


struct AB : public ComponentObject<A, B>
{

};

struct DerivedAB : public ComponentObject<A>, public ComponentObject<B>
{

};