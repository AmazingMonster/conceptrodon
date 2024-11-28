// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_FLOWFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_FLOWFUL_H

#include "conceptrodon/omennivore/is_flowful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_flowful.hpp"
#include "conceptrodon/mouldivore/concepts/any_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyFlowful
=   Mouldivore::AnyConfess<IsFlowful, Args...>
||  AllFlowful<Args...>;

}}

#endif