// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_FLOWLY_H
#define CONCEPTRODON_OMENNIVORE_ANY_FLOWLY_H

#include "conceptrodon/omennivore/concepts/descend/all_flowly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Structures>
concept JustAnyFlowly = (... || Flowly<Structures>);

template<typename...Args>
concept AnyFlowly
=   JustAnyFlowly<Args...>
||  AllFlowly<Args...>;

}}

#endif