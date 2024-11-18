// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_SNOWFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_SNOWFUL_H

#include "conceptrodon/omennivore/is_snowful.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllSnowful = (... && IsSnowful<Args>::value);

}}

#endif