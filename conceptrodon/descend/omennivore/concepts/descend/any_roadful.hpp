// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_ROADFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_ROADFUL_H

#include "conceptrodon/omennivore/is_roadful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_roadful.hpp"
#include "conceptrodon/mouldivore/concepts/any_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyRoadful
=   Mouldivore::AnyConfess<IsRoadful, Args...>
||  AllRoadful<Args...>;

}}

#endif