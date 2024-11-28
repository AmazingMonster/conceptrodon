// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_ROADLESS_H
#define CONCEPTRODON_OMENNIVORE_ANY_ROADLESS_H

#include "conceptrodon/omennivore/concepts/descend/all_roadless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyRoadless = (... || Roadless<Structures>);

template<typename...Args>
concept AnyRoadless
=   JustAnyRoadless<Args...>
||  AllRoadless<Args...>;

}}

#endif