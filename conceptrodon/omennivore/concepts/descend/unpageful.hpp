// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNPAGEFUL_H
#define CONCEPTRODON_OMENNIVORE_UNPAGEFUL_H

#include "conceptrodon/omennivore/concepts/moldful.hpp"
#include "conceptrodon/omennivore/is_pageful.hpp"
#include "conceptrodon/omennivore/concepts/roadful.hpp"
#include "conceptrodon/omennivore/concepts/railful.hpp"
#include "conceptrodon/omennivore/concepts/flowful.hpp"
#include "conceptrodon/omennivore/concepts/sailful.hpp"
#include "conceptrodon/omennivore/concepts/snowful.hpp"
#include "conceptrodon/omennivore/concepts/hailful.hpp"
#include "conceptrodon/omennivore/concepts/lullful.hpp"
#include "conceptrodon/omennivore/concepts/calmful.hpp"
#include "conceptrodon/omennivore/concepts/gritful.hpp"
#include "conceptrodon/omennivore/concepts/willful.hpp"
#include "conceptrodon/omennivore/concepts/glowful.hpp"
#include "conceptrodon/omennivore/concepts/dawnful.hpp"

namespace Conceptrodon {
namespace Ominuci {

template<typename Arg>
concept JustUnpageful
= not Omennivore::IsPageful_v<Arg>;

}

namespace Omennivore {

template<typename Arg>
concept Unpageful
=   Ominuci::JustUnpageful<Arg>
||  Moldful<Arg>
||  Roadful<Arg>
||  Railful<Arg>
||  Flowful<Arg>
||  Sailful<Arg>
||  Snowful<Arg>
||  Hailful<Arg>
||  Lullful<Arg>
||  Calmful<Arg>
||  Gritful<Arg>
||  Willful<Arg>
||  Glowful<Arg>
||  Dawnful<Arg>
;

}}

#endif