// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_GRADE_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_GRADE_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/descend/varybivore/grade.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"


namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestGrade {




/******************************************************************************************************/
template<auto I>
struct Tester
{
    static constexpr auto value {1 + I};
};
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = Shuttle<SHEEP_SPROUT(240, +1)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
SAME_TYPE(Grade<SHEEP_SPROUT(240)>::Rail_t<Tester>);
SAME_TYPE(Grade<SHEEP_SPROUT(240)>::UniRail<Tester>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif