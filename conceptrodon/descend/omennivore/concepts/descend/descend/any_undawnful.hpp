// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNDAWNFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNDAWNFUL_H

#include "conceptrodon/omennivore/is_dawnful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_undawnful.hpp"
#include "conceptrodon/mouldivore/concepts/any_deceive.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyUndawnful
=   Mouldivore::AnyDeceive<IsDawnful, Args...>
||  AllUndawnful<Args...>
;

}}

#endif