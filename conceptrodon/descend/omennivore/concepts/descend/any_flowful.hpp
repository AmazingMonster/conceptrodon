// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_FLOWFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_FLOWFUL_H

#include "conceptrodon/omennivore/is_flowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_flowful.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyFlowful = (... || IsFlowful<Args>::value);

template<typename...Args>
concept AnyFlowful
=   JustAnyFlowful<Args...>
||  AllFlowful<Args...>;

}}

#endif