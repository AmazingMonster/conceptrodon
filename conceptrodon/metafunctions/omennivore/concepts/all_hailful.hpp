// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_HAILFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_HAILFUL_H

#include "conceptrodon/metafunctions/omennivore/is_hailful.hpp"
#include "conceptrodon/metafunctions/mouldivore/concepts/all_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllHailful = Mouldivore::AllConfess<IsHailful, Args...>;


}}

#endif