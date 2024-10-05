// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_TEST_IS_POTTERY_H
#define CONCEPTRODON_OMENNIVORE_TEST_IS_POTTERY_H

#include "conceptrodon/omennivore/is_pottery.hpp"
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
namespace TestIsPottery {

using CapsuleTester = Capsule<>;
using ShuttleTester = Shuttle<>;
using ReverieTester = Reverie<>;
using PhantomTester = Phantom<>;

VALID(IsPottery<CapsuleTester>::value);
VALID(IsPottery_v<CapsuleTester>);

INVALID(IsPottery<ShuttleTester>::value);
INVALID(IsPottery_v<ShuttleTester>);

INVALID(IsPottery<ReverieTester>::value);
INVALID(IsPottery_v<ReverieTester>);

INVALID(IsPottery<PhantomTester>::value);
INVALID(IsPottery_v<PhantomTester>);

}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif