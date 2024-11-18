// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_ROADLY_H
#define CONCEPTRODON_OMENNIVORE_ANY_ROADLY_H

#include "conceptrodon/omennivore/concepts/descend/all_roadly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyRoadly = (... || Roadly<Structures>);

template<typename...Args>
concept AnyRoadly
=   JustAnyRoadly<Args...>
||  AllRoadly<Args...>;

}}

#endif