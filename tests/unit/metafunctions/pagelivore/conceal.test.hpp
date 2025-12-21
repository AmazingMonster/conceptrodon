// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_UNIT_TESTS_TEST_CONCEAL_H
#define CONCEPTRODON_PAGELIVORE_UNIT_TESTS_TEST_CONCEAL_H

#include <concepts>

#include "conceptrodon/metafunctions/pagelivore/conceal.hpp"

#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestConceal {




/******************************************************************************************************/
template<auto...>
struct Operation;
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Operation<0, 1, 2, 3>

SAME_TYPE(Conceal<Operation>::Page<0, 1, 2, 3>::type);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif