// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNGRITFUL_H
#define CONCEPTRODON_OMENNIVORE_UNGRITFUL_H

#include "conceptrodon/descend/omennivore/concepts/moldful.hpp"
#include "conceptrodon/descend/omennivore/concepts/pageful.hpp"
#include "conceptrodon/descend/omennivore/concepts/roadful.hpp"
#include "conceptrodon/descend/omennivore/concepts/railful.hpp"
#include "conceptrodon/descend/omennivore/concepts/flowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/sailful.hpp"
#include "conceptrodon/descend/omennivore/concepts/snowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/hailful.hpp"
#include "conceptrodon/descend/omennivore/concepts/coolful.hpp"
#include "conceptrodon/descend/omennivore/concepts/calmful.hpp"
#include "conceptrodon/omennivore/is_gritful.hpp"
#include "conceptrodon/descend/omennivore/concepts/willful.hpp"
#include "conceptrodon/descend/omennivore/concepts/glowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/dawnful.hpp"
#include "conceptrodon/typelivore/concepts/falsify.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Arg>
concept Ungritful
=   Typelivore::Falsify<IsGritful, Arg>
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
||  Willful<Arg>
||  Glowful<Arg>
||  Dawnful<Arg>
;

}}

#endif