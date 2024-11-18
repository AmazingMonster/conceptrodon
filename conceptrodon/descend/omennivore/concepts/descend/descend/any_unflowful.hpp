// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNFLOWFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNFLOWFUL_H

#include "conceptrodon/omennivore/is_flowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_unflowful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyUnflowful
= (...||(not IsFlowful<Args>::value));

template<typename...Args>
concept AnyUnflowful
=   JustAnyUnflowful<Args...>
||  AllUnflowful<Args...>
;

}}

#endif