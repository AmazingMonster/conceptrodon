// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNSAILFUL_H
#define CONCEPTRODON_OMENNIVORE_UNSAILFUL_H

#include "conceptrodon/descend/omennivore/concepts/moldful.hpp"
#include "conceptrodon/descend/omennivore/concepts/pageful.hpp"
#include "conceptrodon/descend/omennivore/concepts/roadful.hpp"
#include "conceptrodon/descend/omennivore/concepts/railful.hpp"
#include "conceptrodon/descend/omennivore/concepts/flowful.hpp"
#include "conceptrodon/omennivore/is_sailful.hpp"
#include "conceptrodon/descend/omennivore/concepts/snowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/hailful.hpp"
#include "conceptrodon/descend/omennivore/concepts/lullful.hpp"
#include "conceptrodon/descend/omennivore/concepts/calmful.hpp"
#include "conceptrodon/descend/omennivore/concepts/gritful.hpp"
#include "conceptrodon/descend/omennivore/concepts/willful.hpp"
#include "conceptrodon/descend/omennivore/concepts/glowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/dawnful.hpp"
#include "conceptrodon/typelivore/concepts/falsify.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Arg>
concept Unsailful
=   Typelivore::Falsify<IsSailful, Arg>
||  Moldful<Arg>
||  Pageful<Arg>
||  Roadful<Arg>
||  Railful<Arg>
||  Flowful<Arg>
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