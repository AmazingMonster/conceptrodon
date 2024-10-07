// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_VARYBIVORE_CONDITIONAL_H
#define CONCEPTRODON_TESTS_UNIT_VARYBIVORE_CONDITIONAL_H

#include <type_traits>
#include "conceptrodon/varybivore/conditional.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Varybivore {
namespace UnitTests {
namespace TestConditional {




/******************************************************************************************************/
template<typename...>
using MoldT = std::true_type;

template<typename...>
using MoldF = std::false_type;

template<auto...>
using PageT = std::true_type;

template<auto...>
using PageF = std::false_type;
/******************************************************************************************************/




/******************************************************************************************************/
VALID(Conditional<true, false>::Road<MoldT, MoldT, MoldT, MoldT>::Mold_v<int>);
VALID(Conditional<true, false>::Rail<PageT, PageT, PageT, PageT>::Page_v<1>);
/******************************************************************************************************/




/******************************************************************************************************/
INVALID(Conditional<true, false>::Road<MoldF, MoldT, MoldT, MoldT>::Mold_v<int>);
INVALID(Conditional<true, false>::Rail<PageF, PageT, PageT, PageT>::Page_v<1>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif