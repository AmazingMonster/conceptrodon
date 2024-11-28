// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_CONCEAL_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_CONCEAL_H

#include <concepts>

#include "conceptrodon/mouldivore/conceal.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestConceal {




/******************************************************************************************************/
template<typename...>
struct Operation;
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Operation<int, int*, int**, int***>

SAME_TYPE(Conceal<Operation>::Mold<int, int*, int**, int***>::type);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif