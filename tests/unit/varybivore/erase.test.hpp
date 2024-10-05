// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_TEST_ERASE_H
#define CONCEPTRODON_VARYBIVORE_TEST_ERASE_H

#include "conceptrodon/descend/varybivore/erase.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include <utility>

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestErase {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResultA = Shuttle<SHEEP_SPROUT(40), SHEEP_SPROUT(140, +100)>;
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
/******************************************************************************************************/



/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResultA

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Erase<SHEEP_SPROUT(240)>::Page<40, 100>::UniRail<>);
SAME_TYPE(Erase<SHEEP_SPROUT(240)>::Page<40, 100>::Rail<Shuttle>);
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"


#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
// SAME_TYPE(Erase<SHEEP_SPROUT(240)>::Page<400, 100>::UniRail);
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResultB = Shuttle<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
/******************************************************************************************************/



/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResultB

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Erase<SHEEP_SPROUT(240)>::Page<40, 40>::UniRail<>);
SAME_TYPE(Erase<SHEEP_SPROUT(240)>::Page<40, 40>::Rail<Shuttle>);
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"


#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Variables>
requires (sizeof...(Variables) == 180)
struct Tester {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResultC = Tester<SHEEP_SPROUT(40), SHEEP_SPROUT(140, +100)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResultC

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Erase<SHEEP_SPROUT(240)>::Page<40, 100>::UniRail<Tester>);
SAME_TYPE(Erase<SHEEP_SPROUT(240)>::Page<40, 100>::Rail<Tester>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

#endif