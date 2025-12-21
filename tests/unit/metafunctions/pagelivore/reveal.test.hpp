// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_UNIT_TESTS_TEST_REVEAL_H
#define CONCEPTRODON_PAGELIVORE_UNIT_TESTS_TEST_REVEAL_H

#include <concepts>

#include "conceptrodon/metafunctions/pagelivore/reveal.hpp"
#include "conceptrodon/utilities/shuttle.hpp"

#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestReveal {




/******************************************************************************************************/
template<auto...Args>
struct Operation
{ using type = Shuttle<Args...>; };
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Shuttle<0, 1, 2, 3>

SAME_TYPE(Reveal<Operation>::Page<0, 1, 2, 3>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif