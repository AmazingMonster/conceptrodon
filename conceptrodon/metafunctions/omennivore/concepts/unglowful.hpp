// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNGLOWFUL_H
#define CONCEPTRODON_OMENNIVORE_UNGLOWFUL_H

#include "conceptrodon/metafunctions/omennivore/concepts/moldful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/pageful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/roadful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/railful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/flowful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/sailful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/snowful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/hailful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/coolful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/calmful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/gritful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/willful.hpp"
#include "conceptrodon/metafunctions/omennivore/is_glowful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/dawnful.hpp"
#include "conceptrodon/metafunctions/mouldivore/concepts/deceive.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Arg>
concept Unglowful
=   Mouldivore::Deceive<IsGlowful, Arg>
||  Moldful<Arg>
||  Pageful<Arg>
||  Roadful<Arg>
||  Railful<Arg>
||  Flowful<Arg>
||  Sailful<Arg>
||  Snowful<Arg>
||  Hailful<Arg>
||  Coolful<Arg>
||  Calmful<Arg>
||  Gritful<Arg>
||  Willful<Arg>
||  Dawnful<Arg>
;

}}

#endif