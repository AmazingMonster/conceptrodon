// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_VARYBIVORE_TEST_SLICE_H
#define CONCEPTRODON_VARYBIVORE_TEST_SLICE_H

#include "conceptrodon/descend/varybivore/slice.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace TestSlice {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResultA = Shuttle<SHEEP_SPROUT(40, +60)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResultA

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Slice<SHEEP_SPROUT(240)>::Page<60, 100>::UniRail<>);
SAME_TYPE(Slice<SHEEP_SPROUT(240)>::Page<60, 100>::Rail<Shuttle>);
// SAME_TYPE(Slice<SHEEP_SPROUT(240)>::Page<600, 100>::UniRail<>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/



/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResultB = Shuttle<>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResultB

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Slice<SHEEP_SPROUT(240)>::Page<40, 40>::UniRail<>);
SAME_TYPE(Slice<SHEEP_SPROUT(240)>::Page<40, 40>::Rail<Shuttle>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Variables>
requires (sizeof...(Variables) == 60)
struct Tester {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResultC = Tester<SHEEP_SPROUT(60, +40)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResultC

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Slice<SHEEP_SPROUT(240)>::Page<40, 100>::UniRail<Tester>);
SAME_TYPE(Slice<SHEEP_SPROUT(240)>::Page<40, 100>::Rail<Tester>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#endif