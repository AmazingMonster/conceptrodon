#ifndef CONCEPTRODON_VARYBIVORE_TEST_POP_H
#define CONCEPTRODON_VARYBIVORE_TEST_POP_H

#include <utility>
#include "conceptrodon/descend/varybivore/pop.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestPop {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = Shuttle<SHEEP_SPROUT(239)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Pop<SHEEP_SPROUT(240)>::type);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif