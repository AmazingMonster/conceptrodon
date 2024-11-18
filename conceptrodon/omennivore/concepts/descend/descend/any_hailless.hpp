// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_HAILLESS_H
#define CONCEPTRODON_OMENNIVORE_ANY_HAILLESS_H

#include "conceptrodon/omennivore/concepts/descend/all_hailless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyHailless = (... || Hailless<Structures>);

template<typename...Args>
concept AnyHailless
=   JustAnyHailless<Args...>
||  AllHailless<Args...>;

}}

#endif