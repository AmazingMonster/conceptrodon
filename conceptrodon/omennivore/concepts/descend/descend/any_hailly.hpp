// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_HAILLY_H
#define CONCEPTRODON_OMENNIVORE_ANY_HAILLY_H

#include "conceptrodon/omennivore/concepts/descend/all_hailly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyHailly = (... || Hailly<Structures>);

template<typename...Args>
concept AnyHailly
=   JustAnyHailly<Args...>
||  AllHailly<Args...>;

}}

#endif