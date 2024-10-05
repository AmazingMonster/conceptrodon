#ifndef CONCEPTRODON_OMENNIVORE_TEST_INSERT_TYPES_H
#define CONCEPTRODON_OMENNIVORE_TEST_INSERT_TYPES_H

#include <concepts>
#include <utility>
#include "conceptrodon/descend/omennivore/insert_types.hpp"
#include "conceptrodon/capsule.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/alkane.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace TestInsertTypes {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = Capsule<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#define ALKANE_PREFIX
#define ALKANE_CARBON   \
    std::make_index_sequence<1>
#define ALKANE_SUFFIX   
#define ALKANE_SEPARATOR    \
    ,

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(InsertTypes<std::make_index_sequence<0>, ALKANE_SPROUT(119)>::Mold<SHEEP_SPROUT(120, *2)>::Mold_t<SHEEP_SPROUT(120, *2+1)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef ALKANE_PREFIX
#undef ALKANE_CARBON
#undef ALKANE_SUFFIX   
#undef ALKANE_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

#endif