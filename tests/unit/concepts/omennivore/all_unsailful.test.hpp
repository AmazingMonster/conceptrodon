// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNSAILFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNSAILFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/all_unsailful.hpp"

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
namespace TestAllUnsailful {

static_assert(AllUnsailful<Capsule<>, Capsule<int>>);

static_assert(AllUnsailful<Shuttle<>, Shuttle<0>>);

static_assert(AllUnsailful<Vehicle<>, Vehicle<Capsule>>);

static_assert(AllUnsailful<Carrier<>, Carrier<Shuttle>>);

static_assert(AllUnsailful<Reverie<>, Reverie<Vehicle>>);

static_assert(! AllUnsailful<Phantom<>, Phantom<Carrier>>);

static_assert(AllUnsailful<Forlorn<>, Forlorn<Reverie>>);

static_assert(AllUnsailful<Travail<>, Travail<Phantom>>);

static_assert(AllUnsailful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(AllUnsailful<Halcyon<>, Halcyon<Travail>>);

static_assert(AllUnsailful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(AllUnsailful<Persist<>, Persist<Halcyon>>);

static_assert(AllUnsailful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(AllUnsailful<Morning<>, Morning<Persist>>);

}}}}

#endif