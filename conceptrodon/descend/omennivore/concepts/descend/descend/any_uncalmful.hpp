// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNCALMFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNCALMFUL_H

#include "conceptrodon/omennivore/is_calmful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_uncalmful.hpp"
#include "conceptrodon/mouldivore/concepts/any_deceive.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyUncalmful
=   Mouldivore::AnyDeceive<IsCalmful, Args...>
||  AllUncalmful<Args...>
;

}}

#endif