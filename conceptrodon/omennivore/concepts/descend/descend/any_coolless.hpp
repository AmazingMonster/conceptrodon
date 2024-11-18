// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_COOLLESS_H
#define CONCEPTRODON_OMENNIVORE_ANY_COOLLESS_H

#include "conceptrodon/omennivore/concepts/descend/all_coolless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyCoolless = (... || Coolless<Structures>);

template<typename...Args>
concept AnyCoolless
=   JustAnyCoolless<Args...>
||  AllCoolless<Args...>;

}}

#endif