// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_RAILLESS_H
#define CONCEPTRODON_OMENNIVORE_ANY_RAILLESS_H

#include "conceptrodon/omennivore/concepts/descend/all_railless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyRailless = (... || Railless<Structures>);

template<typename...Args>
concept AnyRailless
=   JustAnyRailless<Args...>
||  AllRailless<Args...>;

}}

#endif