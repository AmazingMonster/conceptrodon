// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_COOLFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_COOLFUL_H

#include "conceptrodon/omennivore/is_coolful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_coolful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyCoolful = (... || IsCoolful<Args>::value);

template<typename...Args>
concept AnyCoolful
=   JustAnyCoolful<Args...>
||  AllCoolful<Args...>;

}}

#endif