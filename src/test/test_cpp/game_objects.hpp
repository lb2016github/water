#include "component_object.hpp"


struct AB : public ComponentObject<A, B>
{

};

struct DerivedAB : virtual public ComponentObject<A>, virtual public ComponentObject<B>
{

};