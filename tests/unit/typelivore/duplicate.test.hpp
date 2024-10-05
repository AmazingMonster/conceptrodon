#ifndef CONCEPTRODON_TYPELIVORE_TEST_DUPLICATE_H
#define CONCEPTRODON_TYPELIVORE_TEST_DUPLICATE_H

#include <concepts>
#include "conceptrodon/descend/typelivore/duplicate.hpp"
#include "conceptrodon/capsule.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/alkane.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_alkane.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace TestDuplicate {




/******************************************************************************************************/
#define ALKANE_PREFIX
#define ALKANE_CARBON   \
    int
#define ALKANE_SUFFIX   
#define ALKANE_SEPARATOR    \
    ,

using SupposedResult = Capsule<ALKANE_SPROUT(240)>;

#undef ALKANE_PREFIX
#undef ALKANE_CARBON
#undef ALKANE_SUFFIX   
#undef ALKANE_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

SAME_TYPE(Duplicate<int>::Page<240>::UniRoad<>);
SAME_TYPE(Duplicate<int>::Page<240>::Road<>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_alkane.hpp"

#endif