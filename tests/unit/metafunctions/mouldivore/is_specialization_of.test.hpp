// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_IS_SPECIALIZATION_OF_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_IS_SPECIALIZATION_OF_H

#include <utility>

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/mouldivore/is_specialization_of.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestIsSpecializationOf {

VALID(IsSpecializationOf<std::tuple>::Mold_v<std::tuple<>>);
VALID(IsSpecializationOf<std::tuple>::Mold_v<std::tuple<int>>);
INVALID(IsSpecializationOf<std::tuple>::Mold_v<Capsule<>>);
INVALID(IsSpecializationOf<std::tuple>::Mold_v<Capsule<int>>);
INVALID(IsSpecializationOf<std::tuple>::Mold_v<Shuttle<>>);
INVALID(IsSpecializationOf<std::tuple>::Mold_v<Shuttle<1>>);

}}}}

#endif