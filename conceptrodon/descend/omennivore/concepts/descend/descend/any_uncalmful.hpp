// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNCALMFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNCALMFUL_H

#include "conceptrodon/omennivore/is_calmful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_uncalmful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyUncalmful
= (...||(not IsCalmful<Args>::value));

template<typename...Args>
concept AnyUncalmful
=   JustAnyUncalmful<Args...>
||  AllUncalmful<Args...>
;

}}

#endif