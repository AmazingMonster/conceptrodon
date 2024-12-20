// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNRAILFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNRAILFUL_H

#include "conceptrodon/omennivore/is_railful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_unrailful.hpp"
#include "conceptrodon/mouldivore/concepts/any_deceive.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyUnrailful
=   Mouldivore::AnyDeceive<IsRailful, Args...>
||  AllUnrailful<Args...>
;

}}

#endif