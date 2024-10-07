// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_DISMISS_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_DISMISS_H

#include "conceptrodon/descend/varybivore/dismiss.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestDismiss {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
template<size_t I>
using DismissIndex = Dismiss<SHEEP_SPROUT(240)>::Page<I>::template Rail<Shuttle>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResultA = Shuttle<SHEEP_SPROUT(239, +1)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResultA
    
SAME_TYPE(DismissIndex<0>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResultB = Shuttle<SHEEP_SPROUT(40), SHEEP_SPROUT(199, +41)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResultB
    
SAME_TYPE(DismissIndex<40>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResultC = Shuttle<SHEEP_SPROUT(239)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResultC
    
SAME_TYPE(DismissIndex<239>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
template<auto...Variables>
requires (sizeof...(Variables) == 239)
struct Tester {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResultD = Tester<SHEEP_SPROUT(40), SHEEP_SPROUT(199, +41)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResultD

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Dismiss<SHEEP_SPROUT(240)>::Page<40>::UniRail<Tester>);
SAME_TYPE(Dismiss<SHEEP_SPROUT(240)>::Page<40>::Rail<Tester>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif