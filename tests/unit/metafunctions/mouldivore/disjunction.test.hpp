// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_DISJUNCTION_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_DISJUNCTION_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/mouldivore/disjunction.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestDisjunction {




/******************************************************************************************************/
template<typename...>
using MoldT = std::true_type;

template<typename...>
using MoldF = std::false_type;
/******************************************************************************************************/




/******************************************************************************************************/
VALID(Disjunction<MoldT, MoldT, MoldT, MoldT>::Mold_v<int>);
VALID(Disjunction<MoldF, MoldT, MoldT, MoldT>::Mold_v<int>);
INVALID(Disjunction<MoldF, MoldF, MoldF, MoldF>::Mold_v<int>);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif