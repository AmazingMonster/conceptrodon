// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_KINDRED_LEFT_INTERVIEW_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_KINDRED_LEFT_INTERVIEW_H

#include <utility>

#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/typelivore/kindred_left_interview.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/alkane.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_alkane.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestKindredLeftInterview {




/******************************************************************************************************/
template<typename, typename L, typename R>
struct NoGreaterThanZero
{ static constexpr bool value {false}; };

template<typename U, typename L, typename R>
requires (L::value <= 0)
struct NoGreaterThanZero<U, L, R>
{ static constexpr bool value {true}; };

template<typename, typename L, typename R>
struct EqualNegative
{ static constexpr bool value {false}; };

template<typename U, typename L, typename R>
requires (R::value == -L::value)
struct EqualNegative<U, L, R>
{ static constexpr bool value {true}; };
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
template<int I>
constexpr auto Interviewed = KindredLeftInterview<SHEEP_SPROUT(80)>
::template Mold<int, std::integral_constant<int, -I>>
::template Road_v<NoGreaterThanZero, EqualNegative>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
#include "macaron/fragmental/amenity/instances/define_integer_negative_one_alkane.hpp"
using SupposedResult = SignedArk<SHEEP_SPROUT(80), ALKANE_SPROUT(40)>;
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
SAME_TYPE(Shuttle<SHEEP_SPROUT(120)>);

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