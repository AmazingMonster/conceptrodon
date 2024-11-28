// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_COOLLY_H
#define CONCEPTRODON_OMENNIVORE_ANY_COOLLY_H

#include "conceptrodon/omennivore/concepts/descend/all_coolly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyCoolly = (... || Coolly<Structures>);

template<typename...Args>
concept AnyCoolly
=   JustAnyCoolly<Args...>
||  AllCoolly<Args...>;

}}

#endif