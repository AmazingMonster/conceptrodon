// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNCOOLFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNCOOLFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/all_uncoolful.hpp"

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/vehicle.hpp"
#include "conceptrodon/carrier.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"
#include "conceptrodon/forlorn.hpp"
#include "conceptrodon/travail.hpp"
#include "conceptrodon/lullaby.hpp"
#include "conceptrodon/halcyon.hpp"
#include "conceptrodon/pursuit.hpp"
#include "conceptrodon/persist.hpp"
#include "conceptrodon/sunrise.hpp"
#include "conceptrodon/morning.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestAllUncoolful {

static_assert(AllUncoolful<Capsule<>, Capsule<int>>);

static_assert(AllUncoolful<Shuttle<>, Shuttle<0>>);

static_assert(AllUncoolful<Vehicle<>, Vehicle<Capsule>>);

static_assert(AllUncoolful<Carrier<>, Carrier<Shuttle>>);

static_assert(AllUncoolful<Reverie<>, Reverie<Vehicle>>);

static_assert(AllUncoolful<Phantom<>, Phantom<Carrier>>);

static_assert(AllUncoolful<Forlorn<>, Forlorn<Reverie>>);

static_assert(AllUncoolful<Travail<>, Travail<Phantom>>);

static_assert(! AllUncoolful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(AllUncoolful<Halcyon<>, Halcyon<Travail>>);

static_assert(AllUncoolful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(AllUncoolful<Persist<>, Persist<Halcyon>>);

static_assert(AllUncoolful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(AllUncoolful<Morning<>, Morning<Persist>>);

}}}}

#endif