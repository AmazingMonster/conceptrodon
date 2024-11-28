// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_TERSE_INDEPENDENT_RIGHT_INTERVIEW_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_TERSE_INDEPENDENT_RIGHT_INTERVIEW_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/pagelivore/terse_independent_right_interview.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/alkane.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_alkane.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestTerseIndependentRightInterview {




/******************************************************************************************************/
template<auto L, auto R, auto>
struct NoGreaterThanZero
{ static constexpr bool value {false}; };

template<auto L, auto R, auto U>
requires (L <= 0)
struct NoGreaterThanZero<L, R, U>
{ static constexpr bool value {true}; };

template<auto L, auto R, auto>
struct EqualNegative
{ static constexpr bool value {false}; };

template<auto L, auto R, auto U>
requires (R == -L)
struct EqualNegative<L, R, U>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
template<int I>
constexpr auto Interviewed = TerseIndependentRightInterview<NoGreaterThanZero, EqualNegative>
::Page<I, nullptr>::template Page_v<SHEEP_SPROUT(20, *(-1))>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = SignedArk<SHEEP_SPROUT(20)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#define SHEEP_PREFIX    \
    Interviewed <
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,
SAME_TYPE(Shuttle<SHEEP_SPROUT(20)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
template<int I>
constexpr auto FailInterviewed = TerseIndependentRightInterview<NoGreaterThanZero, EqualNegative>
::Page<1, nullptr>::template Page_v<SHEEP_SPROUT(40), I>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_negative_one_alkane.hpp"
using SupposedFailedResult = SignedArk<ALKANE_SPROUT(20)>;
#include "macaron/fragmental/amenity/instances/undef_integer_negative_one_alkane.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedFailedResult

#define SHEEP_PREFIX    \
    FailInterviewed <
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,
SAME_TYPE(Shuttle<SHEEP_SPROUT(20)>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/fragmental/amenity/undef_alkane.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif