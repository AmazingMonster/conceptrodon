// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNROADFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNROADFUL_H

#include "conceptrodon/omennivore/is_roadful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_unroadful.hpp"
#include "conceptrodon/mouldivore/concepts/any_deceive.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyUnroadful
=   Mouldivore::AnyDeceive<IsRoadful, Args...>
||  AllUnroadful<Args...>
;

}}

#endif