// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNGRITFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNGRITFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/all_ungritful.hpp"

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
namespace TestAllUngritful {

static_assert(AllUngritful<Capsule<>, Capsule<int>>);

static_assert(AllUngritful<Shuttle<>, Shuttle<0>>);

static_assert(AllUngritful<Vehicle<>, Vehicle<Capsule>>);

static_assert(AllUngritful<Carrier<>, Carrier<Shuttle>>);

static_assert(AllUngritful<Reverie<>, Reverie<Vehicle>>);

static_assert(AllUngritful<Phantom<>, Phantom<Carrier>>);

static_assert(AllUngritful<Forlorn<>, Forlorn<Reverie>>);

static_assert(AllUngritful<Travail<>, Travail<Phantom>>);

static_assert(AllUngritful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(AllUngritful<Halcyon<>, Halcyon<Travail>>);

static_assert(! AllUngritful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(AllUngritful<Persist<>, Persist<Halcyon>>);

static_assert(AllUngritful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(AllUngritful<Morning<>, Morning<Persist>>);

}}}}

#endif