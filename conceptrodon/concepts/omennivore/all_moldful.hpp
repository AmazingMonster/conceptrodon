// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_MOLDFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_MOLDFUL_H

#include "conceptrodon/metafunctions/omennivore/is_moldful.hpp"
#include "conceptrodon/concepts/mouldivore/all_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllMoldful = Mouldivore::AllConfess<IsMoldful, Args...>;


}}

#endif