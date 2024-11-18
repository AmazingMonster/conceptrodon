// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_ROADFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_ROADFUL_H

#include "conceptrodon/omennivore/is_roadful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_roadful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyRoadful = (... || IsRoadful<Args>::value);

template<typename...Args>
concept AnyRoadful
=   JustAnyRoadful<Args...>
||  AllRoadful<Args...>;

}}

#endif