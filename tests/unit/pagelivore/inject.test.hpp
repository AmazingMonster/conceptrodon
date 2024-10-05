#ifndef CONCEPTRODON_PAGELIVORE_TEST_INJECT_H
#define CONCEPTRODON_PAGELIVORE_TEST_INJECT_H

#include "conceptrodon/descend/pagelivore/inject.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace TestInject {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedShuttleA = Shuttle<SHEEP_SPROUT(40), SHEEP_SPROUT(100), SHEEP_SPROUT(100, +40)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedShuttleA

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Inject<>::Page<40>::Page<SHEEP_SPROUT(100)>::Page<SHEEP_SPROUT(140)>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Variables>
requires (sizeof...(Variables) == 240)
struct Tester {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResultB = Tester<SHEEP_SPROUT(40), SHEEP_SPROUT(100), SHEEP_SPROUT(100, +40)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResultB

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Inject<Tester>::Page<40>::Page<SHEEP_SPROUT(100)>::Page<SHEEP_SPROUT(140)>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif