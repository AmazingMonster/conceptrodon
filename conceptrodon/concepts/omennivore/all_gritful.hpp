// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_GRITFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_GRITFUL_H

#include "conceptrodon/metafunctions/omennivore/is_gritful.hpp"
#include "conceptrodon/concepts/mouldivore/all_passed.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllGritful = Mouldivore::AllPassed<IsGritful, Args...>;


}}

#endif