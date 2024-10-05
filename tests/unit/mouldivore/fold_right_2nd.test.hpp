// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_TEST_FOLD_RIGHT_2ND_H
#define CONCEPTRODON_MOULDIVORE_TEST_FOLD_RIGHT_2ND_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/mouldivore/fold_right.hpp"
#include "conceptrodon/capsule.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep_reversed.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep_reversed.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace TestFoldRight2nd {




/******************************************************************************************************/
template<typename Left, typename Right>
struct BinaryOperation
{ using type = std::integral_constant<int, Left::value + Right::value>; };

template<typename Left, typename Right>
requires (Right::value < Left::value)
struct BinaryOperation<Left, Right>
{ using type = std::integral_constant<int, 1>; };

template<typename Left, typename Right>
using BinaryOperation_t = BinaryOperation<Left, Right>::type;
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    std::integral_constant<int, 1 + 239 * 240 / 2>

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep_reversed.hpp"
SAME_TYPE(FoldRight<BinaryOperation>::Mold<std::integral_constant<int, 1>>::Mold_t<SHEEP_REVERSED_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep_reversed.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    std::integral_constant<int, 1 + 7 * 8 / 2>

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep_reversed.hpp"
SAME_TYPE(FoldRight<BinaryOperation>::Mold<std::integral_constant<int, 1>>::Mold_t<SHEEP_REVERSED_SPROUT(8)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep_reversed.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    std::integral_constant<int, 1>

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep_reversed.hpp"
SAME_TYPE(FoldRight<BinaryOperation>::Mold<std::integral_constant<int, 1>>::Mold_t<SHEEP_REVERSED_SPROUT(1)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep_reversed.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep_reversed.hpp"

#endif