// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_COGNATE_FILTER_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_COGNATE_FILTER_H

#include <utility>

#include "conceptrodon/mouldivore/cognate_filter.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestCognateFilter {




/******************************************************************************************************/
template<typename Integer>
struct IsEven
{
    static constexpr bool value = Integer::value % 2 == 0;
};
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Elements>
requires (sizeof...(Elements) == 120)
struct Operation {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = Operation<SHEEP_SPROUT(120, * 2 + 1)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(CognateFilter<Operation>::Road<IsEven>::Mold<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/





/******************************************************************************************************/
template<typename Integer>
struct IsDivisibleByThirty
{
    static constexpr bool value = Integer::value % 30 == 0;
};
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...Elements>
requires (sizeof...(Elements) == 232)
struct Operation_1 {};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult_1 = Operation_1
<
    SHEEP_SPROUT(29, +1),
    SHEEP_SPROUT(29, +31),
    SHEEP_SPROUT(29, +61),
    SHEEP_SPROUT(29, +91),
    SHEEP_SPROUT(29, +121),
    SHEEP_SPROUT(29, +151),
    SHEEP_SPROUT(29, +181),
    SHEEP_SPROUT(29, +211)
>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult_1

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(CognateFilter<Operation_1>::Road<IsEven, IsDivisibleByThirty>::Mold<SHEEP_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif