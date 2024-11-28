// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_SAILLY_H
#define CONCEPTRODON_OMENNIVORE_ANY_SAILLY_H

#include "conceptrodon/omennivore/concepts/descend/all_sailly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnySailly = (... || Sailly<Structures>);

template<typename...Args>
concept AnySailly
=   JustAnySailly<Args...>
||  AllSailly<Args...>;

}}

#endif