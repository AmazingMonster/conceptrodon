// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_CAPSULE_H
#define CONCEPTRODON_UNIT_TESTS_TEST_CAPSULE_H

#include "conceptrodon/utilities/capsule.hpp"
#include <concepts>

namespace Conceptrodon {
namespace UnitTests {
namespace TestCapsule {




/******************************************************************************************************/
/**** Operation ****/
template<typename...>
struct NewPacker;

/**** PackedVessel ****/
using PackedCapsule = Capsule<int, int*, int**, int**>;

/**** SupposedResult ****/
using SupposedResult = NewPacker<int, int*, int**, int**>;

/**** Result ****/
using Result = PackedCapsule::Road<NewPacker>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
static_assert(PackedCapsule::size() == 4);
/******************************************************************************************************/




}}}

#endif