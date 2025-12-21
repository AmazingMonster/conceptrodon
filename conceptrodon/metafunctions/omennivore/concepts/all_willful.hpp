// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_WILLFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_WILLFUL_H

#include "conceptrodon/metafunctions/omennivore/is_willful.hpp"
#include "conceptrodon/metafunctions/mouldivore/concepts/all_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllWillful = Mouldivore::AllConfess<IsWillful, Args...>;


}}

#endif