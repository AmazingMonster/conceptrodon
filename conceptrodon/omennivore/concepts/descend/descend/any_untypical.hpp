// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNTYPICAL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNTYPICAL_H

#include "conceptrodon/omennivore/concepts/descend/all_untypical.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyUntypical = (... || Untypical<Structures>);

template<typename...Args>
concept AnyUntypical
=   JustAnyUntypical<Args...>
||  AllUntypical<Args...>;

}}

#endif