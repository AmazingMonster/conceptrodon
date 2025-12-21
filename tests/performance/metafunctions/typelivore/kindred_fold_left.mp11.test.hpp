// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_PERFORMANCE_TESTS_TEST_KINDRED_FOLD_LEFT_2ND_H
#define CONCEPTRODON_TYPELIVORE_PERFORMANCE_TESTS_TEST_KINDRED_FOLD_LEFT_2ND_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/metafunctions/typelivore/kindred_fold_left.hpp"
#include "conceptrodon/utilities/capsule.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

#if CONCEPTRODON_TEST_COMPARE_WITH_BOOST
#include "boost/mp11.hpp"
#endif

namespace Conceptrodon {
namespace Typelivore {
namespace PerformanceTests {
namespace TestKindredFoldLeft2nd {




/******************************************************************************************************/
template<typename Left, typename Right>
struct BinaryOperation
{ using type = std::integral_constant<int, Left::value + Right::value>; };

template<typename Left, typename Right>
requires (Left::value < Right::value)
struct BinaryOperation<Left, Right>
{ using type = std::integral_constant<int, 1>; };

template<typename Left, typename Right>
using BinaryOperation_t = BinaryOperation<Left, Right>::type;
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using CapsuleTester = Capsule<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




#if CONCEPTRODON_TEST_COMPARE_WITH_BOOST




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    std::integral_constant<int, 1 + 239 * 240 / 2>
    
SAME_TYPE(boost::mp11::mp_fold<CapsuleTester, std::integral_constant<int, 1>, BinaryOperation_t>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




#else





/******************************************************************************************************/
#define SUPPOSED_TYPE \
    std::integral_constant<int, 1 + 239 * 240 / 2>

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(KindredFoldLeft<SHEEP_SPROUT(240)>::Mold<std::integral_constant<int, 1>>::UniRoad<BinaryOperation_t>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




#endif




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif