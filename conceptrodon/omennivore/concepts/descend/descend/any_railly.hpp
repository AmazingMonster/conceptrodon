// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_RAILLY_H
#define CONCEPTRODON_OMENNIVORE_ANY_RAILLY_H

#include "conceptrodon/omennivore/concepts/descend/all_railly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyRailly = (... || Railly<Structures>);

template<typename...Args>
concept AnyRailly
=   JustAnyRailly<Args...>
||  AllRailly<Args...>;

}}

#endif