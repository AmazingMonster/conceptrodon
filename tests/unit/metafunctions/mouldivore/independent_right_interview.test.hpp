// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_INDEPENDENT_RIGHT_INTERVIEW_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_INDEPENDENT_RIGHT_INTERVIEW_H

#include <utility>

#include "conceptrodon/utilities/shuttle.hpp"
#include "conceptrodon/mouldivore/independent_right_interview.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/alkane.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_alkane.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestIndependentRightInterview {




/******************************************************************************************************/
template<typename L, typename R, typename>
struct NoGreaterThanZero
{ static constexpr bool value {false}; };

template<typename L, typename R, typename U>
requires (L::value <= 0)
struct NoGreaterThanZero<L, R, U>
{ static constexpr bool value {true}; };

template<typename L, typename R, typename>
struct EqualNegative
{ static constexpr bool value {false}; };

template<typename L, typename R, typename U>
requires (R::value == -L::value)
struct EqualNegative<L, R, U>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
template<int I>
constexpr auto Interviewed = IndependentRightInterview<NoGreaterThanZero, EqualNegative>
::Mold<std::integral_constant<int, I>, int>
::template Mold_v<SHEEP_SPROUT(40, *(-1))>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
#include "macaron/fragmental/amenity/instances/define_integer_negative_one_alkane.hpp"
using SupposedResult = SignedArk<SHEEP_SPROUT(40), ALKANE_SPROUT(40)>;
#include "macaron/fragmental/amenity/instances/undef_integer_negative_one_alkane.hpp"
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
SAME_TYPE(Shuttle<SHEEP_SPROUT(80)>);

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