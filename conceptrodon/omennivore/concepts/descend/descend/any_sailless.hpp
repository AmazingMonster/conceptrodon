// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_SAILLESS_H
#define CONCEPTRODON_OMENNIVORE_ANY_SAILLESS_H

#include "conceptrodon/omennivore/concepts/descend/all_sailless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnySailless = (... || Sailless<Structures>);

template<typename...Args>
concept AnySailless
=   JustAnySailless<Args...>
||  AllSailless<Args...>;

}}

#endif