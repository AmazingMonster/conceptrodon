// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_TEST_NEGATION_H
#define CONCEPTRODON_MOULDIVORE_TEST_NEGATION_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/mouldivore/negation.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace TestNegation {




/******************************************************************************************************/
template<typename...>
using MoldT = std::true_type;

template<typename...>
using MoldF = std::false_type;
/******************************************************************************************************/




/******************************************************************************************************/
INVALID(Negation<MoldT>::Mold_v<int>);
VALID(Negation<MoldF>::Mold_v<int>);
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif