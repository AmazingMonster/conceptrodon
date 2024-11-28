// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_WILLLY_H
#define CONCEPTRODON_OMENNIVORE_ANY_WILLLY_H

#include "conceptrodon/omennivore/concepts/descend/all_willly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyWillly = (... || Willly<Structures>);

template<typename...Args>
concept AnyWillly
=   JustAnyWillly<Args...>
||  AllWillly<Args...>;

}}

#endif