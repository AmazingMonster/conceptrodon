// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_FLOWFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_FLOWFUL_H

#include "conceptrodon/omennivore/is_flowful.hpp"
#include "conceptrodon/mouldivore/concepts/all_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllFlowful = Mouldivore::AllConfess<IsFlowful, Args...>;


}}

#endif