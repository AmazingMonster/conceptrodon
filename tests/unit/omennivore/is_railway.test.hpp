#ifndef CONCEPTRODON_OMENNIVORE_TEST_IS_ALMANAC_H
#define CONCEPTRODON_OMENNIVORE_TEST_IS_ALMANAC_H

#include "conceptrodon/omennivore/is_almanac.hpp"
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
namespace TestIsAlmanac {

using CapsuleTester = Capsule<>;
using ShuttleTester = Shuttle<>;
using ReverieTester = Reverie<>;
using PhantomTester = Phantom<>;

INVALID(IsAlmanac<CapsuleTester>::value);
INVALID(IsAlmanac_v<CapsuleTester>);

VALID(IsAlmanac<ShuttleTester>::value);
VALID(IsAlmanac_v<ShuttleTester>);

INVALID(IsAlmanac<ReverieTester>::value);
INVALID(IsAlmanac_v<ReverieTester>);

INVALID(IsAlmanac<PhantomTester>::value);
INVALID(IsAlmanac_v<PhantomTester>);

}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif