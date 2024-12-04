// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_REVEAL_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_REVEAL_H

#include <concepts>

#include "conceptrodon/mouldivore/reveal.hpp"
#include "conceptrodon/capsule.hpp"

#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestReveal {




/******************************************************************************************************/
template<typename...Args>
struct Operation
{ using type = Capsule<Args...>; };
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule<int, int*, int**, int***>

SAME_TYPE(Reveal<Operation>::Mold<int, int*, int**, int***>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif