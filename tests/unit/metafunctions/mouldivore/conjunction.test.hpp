// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDVORE_UNIT_TESTS_TEST_CONJUNCTION_H
#define CONCEPTRODON_MOULDVORE_UNIT_TESTS_TEST_CONJUNCTION_H

#include <utility>

#include "conceptrodon/metafunctions/mouldivore/conjunction.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestConjunction {




/******************************************************************************************************/
/**** Pred_0 ****/
// Returns true if the argument is less than 10.
template<typename...>
struct Pred_0
{ static constexpr bool value {false}; };

template<typename I>
requires (I::value < 10)
struct Pred_0<I>
{ static constexpr bool value {true}; };

/**** Pred_1 ****/
// Returns true if the argument is greater than 0.
template<typename...>
struct Pred_1
{ static constexpr bool value {false}; };

template<typename I>
requires (0 < I::value)
struct Pred_1<I>
{ static constexpr bool value {true}; };

/**** Pred_2 ****/
// Returns true if the argument is even.
template<typename...>
struct Pred_2
{ static constexpr bool value {false}; };

template<typename I>
requires (I::value % 2 == 0)
struct Pred_2<I>
{ static constexpr bool value {true}; };

/**** Example ****/
template<typename...Args>
using Metafunction = Conjunction<Pred_0, Pred_1, Pred_2>
::Mold<Args...>;
/******************************************************************************************************/




/******************************************************************************************************/
VALID(Metafunction<std::integral_constant<int, 2>>::value);
VALID(Metafunction<std::integral_constant<int, 4>>::value);
INVALID(Metafunction<std::integral_constant<int, 5>>::value);
INVALID(Metafunction<std::integral_constant<int, -2>>::value);

// If no predicate is provided,
// the value is always `true`.
VALID
(
    Conjunction<>
    ::Mold
    <
        std::integral_constant<int, 1>,
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >::value
);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif