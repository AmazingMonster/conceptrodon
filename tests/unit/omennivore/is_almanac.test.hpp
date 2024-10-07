// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_RAILWAY_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_IS_RAILWAY_H

#include "conceptrodon/omennivore/is_railway.hpp"
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestIsRailway {

using CapsuleTester = Capsule<>;
using ShuttleTester = Shuttle<>;
using ReverieTester = Reverie<>;
using PhantomTester = Phantom<>;

INVALID(IsRailway<CapsuleTester>::value);
INVALID(IsRailway_v<CapsuleTester>);

INVALID(IsRailway<ShuttleTester>::value);
INVALID(IsRailway_v<ShuttleTester>);

INVALID(IsRailway<ReverieTester>::value);
INVALID(IsRailway_v<ReverieTester>);

VALID(IsRailway<PhantomTester>::value);
VALID(IsRailway_v<PhantomTester>);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif