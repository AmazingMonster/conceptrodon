// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_SNOWFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_SNOWFUL_H

#include "conceptrodon/omennivore/is_snowful.hpp"
#include "conceptrodon/mouldivore/concepts/all_confess.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllSnowful = Mouldivore::AllConfess<IsSnowful, Args...>;


}}

#endif