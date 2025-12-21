// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNSAILFUL_H
#define CONCEPTRODON_OMENNIVORE_UNSAILFUL_H

#include "conceptrodon/metafunctions/omennivore/concepts/moldful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/pageful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/roadful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/railful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/flowful.hpp"
#include "conceptrodon/metafunctions/omennivore/is_sailful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/snowful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/hailful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/coolful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/calmful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/gritful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/willful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/glowful.hpp"
#include "conceptrodon/metafunctions/omennivore/concepts/dawnful.hpp"
#include "conceptrodon/metafunctions/mouldivore/concepts/deceive.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Arg>
concept Unsailful
=   Mouldivore::Deceive<IsSailful, Arg>
||  Moldful<Arg>
||  Pageful<Arg>
||  Roadful<Arg>
||  Railful<Arg>
||  Flowful<Arg>
||  Snowful<Arg>
||  Hailful<Arg>
||  Coolful<Arg>
||  Calmful<Arg>
||  Gritful<Arg>
||  Willful<Arg>
||  Glowful<Arg>
||  Dawnful<Arg>
;

}}

#endif