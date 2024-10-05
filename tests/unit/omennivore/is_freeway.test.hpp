#ifndef CONCEPTRODON_OMENNIVORE_TEST_IS_FREEWAY_H
#define CONCEPTRODON_OMENNIVORE_TEST_IS_FREEWAY_H

#include "conceptrodon/omennivore/is_freeway.hpp"
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
namespace TestIsFreeway {

using CapsuleTester = Capsule<>;
using ShuttleTester = Shuttle<>;
using ReverieTester = Reverie<>;
using PhantomTester = Phantom<>;

INVALID(IsFreeway<CapsuleTester>::value);
INVALID(IsFreeway_v<CapsuleTester>);

INVALID(IsFreeway<ShuttleTester>::value);
INVALID(IsFreeway_v<ShuttleTester>);

VALID(IsFreeway<ReverieTester>::value);
VALID(IsFreeway_v<ReverieTester>);

INVALID(IsFreeway<PhantomTester>::value);
INVALID(IsFreeway_v<PhantomTester>);

}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif