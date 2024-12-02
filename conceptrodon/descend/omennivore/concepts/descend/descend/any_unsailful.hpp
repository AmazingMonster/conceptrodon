// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNSAILFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNSAILFUL_H

#include "conceptrodon/omennivore/is_sailful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_unsailful.hpp"
#include "conceptrodon/mouldivore/concepts/any_deceive.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyUnsailful
=   Mouldivore::AnyDeceive<IsSailful, Args...>
||  AllUnsailful<Args...>
;

}}

#endif