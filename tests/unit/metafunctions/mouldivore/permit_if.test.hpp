// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_PERMIT_IF_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_PERMIT_IF_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/mouldivore/permit_if.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestPermitIf {




/******************************************************************************************************/
template<typename...>
using Bool_t = bool;

template<typename...>
struct Predicate
{ static constexpr bool value {true}; };

template<>
struct Predicate<int>
{ static constexpr bool value {false}; };

template<typename Element>
consteval auto Tester(Element) -> Bool_t<PermitIf<Predicate>::UniMold<Element>>
{ return true; }

template<typename...>
consteval auto Tester(float)
{ return false; }
/******************************************************************************************************/




/******************************************************************************************************/
VALID(Tester(1.0));
INVALID(Tester(1));
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif