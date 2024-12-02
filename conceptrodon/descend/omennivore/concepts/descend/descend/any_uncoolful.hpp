// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNCOOLFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNCOOLFUL_H

#include "conceptrodon/omennivore/is_coolful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_uncoolful.hpp"
#include "conceptrodon/mouldivore/concepts/any_deceive.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyUncoolful
=   Mouldivore::AnyDeceive<IsCoolful, Args...>
||  AllUncoolful<Args...>
;

}}

#endif