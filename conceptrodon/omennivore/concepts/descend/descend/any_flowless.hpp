// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_FLOWLESS_H
#define CONCEPTRODON_OMENNIVORE_ANY_FLOWLESS_H

#include "conceptrodon/omennivore/concepts/descend/all_flowless.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyFlowless = (... || Flowless<Structures>);

template<typename...Args>
concept AnyFlowless
=   JustAnyFlowless<Args...>
||  AllFlowless<Args...>;

}}

#endif