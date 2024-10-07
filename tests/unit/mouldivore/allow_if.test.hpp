// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_ALLOW_IF_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_ALLOW_IF_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/descend/mouldivore/allow_if.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestAllowIf {




/******************************************************************************************************/
template<typename...>
using Bool_t = bool;

template<typename...>
struct Predicate
{ static constexpr bool value {true}; };

template<>
struct Predicate<int>
{ static constexpr bool value {false}; };

template<typename...Elements>
consteval auto Tester(Elements...) -> Bool_t<AllowIf<Predicate>::Mold_t<Elements...>>
{ return true; }

template<typename...>
consteval auto Tester(float)
{ return false; }
/******************************************************************************************************/




/******************************************************************************************************/
VALID(Tester(1, 2));
INVALID(Tester(1));
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif