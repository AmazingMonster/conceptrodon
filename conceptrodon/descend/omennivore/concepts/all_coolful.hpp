// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_COOLFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_COOLFUL_H

#include "conceptrodon/omennivore/is_coolful.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllCoolful = (... && IsCoolful<Args>::value);

}}

#endif