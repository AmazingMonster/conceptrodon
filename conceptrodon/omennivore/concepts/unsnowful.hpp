// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNSNOWFUL_H
#define CONCEPTRODON_OMENNIVORE_UNSNOWFUL_H

#include "conceptrodon/omennivore/concepts/moldful.hpp"
#include "conceptrodon/omennivore/concepts/pageful.hpp"
#include "conceptrodon/omennivore/concepts/roadful.hpp"
#include "conceptrodon/omennivore/concepts/railful.hpp"
#include "conceptrodon/omennivore/concepts/flowful.hpp"
#include "conceptrodon/omennivore/concepts/sailful.hpp"
#include "conceptrodon/omennivore/is_snowful.hpp"
#include "conceptrodon/omennivore/concepts/hailful.hpp"
#include "conceptrodon/omennivore/concepts/coolful.hpp"
#include "conceptrodon/omennivore/concepts/calmful.hpp"
#include "conceptrodon/omennivore/concepts/gritful.hpp"
#include "conceptrodon/omennivore/concepts/willful.hpp"
#include "conceptrodon/omennivore/concepts/glowful.hpp"
#include "conceptrodon/omennivore/concepts/dawnful.hpp"
#include "conceptrodon/mouldivore/concepts/deceive.hpp"


namespace Conceptrodon {
namespace Omennivore {

template<typename Arg>
concept Unsnowful
=   Mouldivore::Deceive<IsSnowful, Arg>
||  Moldful<Arg>
||  Pageful<Arg>
||  Roadful<Arg>
||  Railful<Arg>
||  Flowful<Arg>
||  Sailful<Arg>
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