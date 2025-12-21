// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_UNIT_TESTS_TEST_IS_SPECIALIZATION_OF_H
#define CONCEPTRODON_PAGELIVORE_UNIT_TESTS_TEST_IS_SPECIALIZATION_OF_H

#include <utility>

#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/utilities/shuttle.hpp"
#include "conceptrodon/metafunctions/pagelivore/is_specialization_of.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestIsSpecializationOf {

VALID(IsSpecializationOf<std::index_sequence>::Mold_v<std::index_sequence<>>);
VALID(IsSpecializationOf<std::index_sequence>::Mold_v<std::index_sequence<1>>);
INVALID(IsSpecializationOf<std::index_sequence>::Mold_v<Capsule<>>);
INVALID(IsSpecializationOf<std::index_sequence>::Mold_v<Capsule<int>>);
INVALID(IsSpecializationOf<std::index_sequence>::Mold_v<Shuttle<>>);
INVALID(IsSpecializationOf<std::index_sequence>::Mold_v<Shuttle<1>>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif