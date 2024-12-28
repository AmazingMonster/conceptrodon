// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_CLASSIC_FOLD_RIGHT_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_CLASSIC_FOLD_RIGHT_H

#include <concepts>

#include "conceptrodon/mouldivore/classic_fold_right.hpp"

#include "conceptrodon/vay.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestClassicFoldRight {




/******************************************************************************************************/
template<typename Left, typename Right>
struct BinaryOperation
{ using type = Vay<Left::value + Right::value>; };

template<typename Left, typename Right>
requires (Left::value < Right::value)
struct BinaryOperation<Left, Right>
{ using type = Vay<Left::value>; };

template<typename Left, typename Right>
using BinaryOperation_t = BinaryOperation<Left, Right>::type;
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    Vay<1>

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE
(
    ClassicFoldRight<BinaryOperation>
    ::Mold<Vay<239>>
    ::Mold<Vay<1>, SHEEP_SPROUT(239)>
);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    Vay<-1>

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE
(
    ClassicFoldRight<BinaryOperation>
    ::Mold<Vay<239>>
    ::Mold<Vay<-1>, SHEEP_SPROUT(239)>
);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    Vay<1>

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE
(
    ClassicFoldRight<BinaryOperation>
    ::Mold<Vay<7>>
    ::Mold<Vay<1>, SHEEP_SPROUT(7)>
);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif