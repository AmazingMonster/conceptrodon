// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_CONJUNCTION_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_CONJUNCTION_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/pagelivore/conjunction.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestConjunction {




/******************************************************************************************************/
template<auto...>
using PageT = std::true_type;

template<auto...>
using PageF = std::false_type;
/******************************************************************************************************/




/******************************************************************************************************/
VALID(Conjunction<PageT, PageT, PageT, PageT>::Page_v<1>);
INVALID(Conjunction<PageF, PageT, PageT, PageT>::Page_v<1>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif