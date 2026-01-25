// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNCALMFUL_H
#define CONCEPTRODON_OMENNIVORE_UNCALMFUL_H

#include "conceptrodon/concepts/omennivore/moldful.hpp"
#include "conceptrodon/concepts/omennivore/pageful.hpp"
#include "conceptrodon/concepts/omennivore/roadful.hpp"
#include "conceptrodon/concepts/omennivore/railful.hpp"
#include "conceptrodon/concepts/omennivore/flowful.hpp"
#include "conceptrodon/concepts/omennivore/sailful.hpp"
#include "conceptrodon/concepts/omennivore/snowful.hpp"
#include "conceptrodon/concepts/omennivore/hailful.hpp"
#include "conceptrodon/concepts/omennivore/coolful.hpp"
#include "conceptrodon/metafunctions/omennivore/is_calmful.hpp"
#include "conceptrodon/concepts/omennivore/gritful.hpp"
#include "conceptrodon/concepts/omennivore/willful.hpp"
#include "conceptrodon/concepts/omennivore/glowful.hpp"
#include "conceptrodon/concepts/omennivore/dawnful.hpp"
#include "conceptrodon/concepts/mouldivore/failed.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Arg>
concept Uncalmful
=   Mouldivore::Failed<IsCalmful, Arg>
||  Moldful<Arg>
||  Pageful<Arg>
||  Roadful<Arg>
||  Railful<Arg>
||  Flowful<Arg>
||  Sailful<Arg>
||  Snowful<Arg>
||  Hailful<Arg>
||  Coolful<Arg>
||  Gritful<Arg>
||  Willful<Arg>
||  Glowful<Arg>
||  Dawnful<Arg>
;

}}

#endif