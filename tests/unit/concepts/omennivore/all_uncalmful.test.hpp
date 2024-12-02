// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNCALMFUL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_ALL_UNCALMFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/all_uncalmful.hpp"

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
namespace TestAllUncalmful {

static_assert(AllUncalmful<Capsule<>, Capsule<int>>);

static_assert(AllUncalmful<Shuttle<>, Shuttle<0>>);

static_assert(AllUncalmful<Vehicle<>, Vehicle<Capsule>>);

static_assert(AllUncalmful<Carrier<>, Carrier<Shuttle>>);

static_assert(AllUncalmful<Reverie<>, Reverie<Vehicle>>);

static_assert(AllUncalmful<Phantom<>, Phantom<Carrier>>);

static_assert(AllUncalmful<Forlorn<>, Forlorn<Reverie>>);

static_assert(AllUncalmful<Travail<>, Travail<Phantom>>);

static_assert(AllUncalmful<Lullaby<>, Lullaby<Forlorn>>);

static_assert(! AllUncalmful<Halcyon<>, Halcyon<Travail>>);

static_assert(AllUncalmful<Pursuit<>, Pursuit<Lullaby>>);

static_assert(AllUncalmful<Persist<>, Persist<Halcyon>>);

static_assert(AllUncalmful<Sunrise<>, Sunrise<Pursuit>>);

static_assert(AllUncalmful<Morning<>, Morning<Persist>>);

}}}}

#endif