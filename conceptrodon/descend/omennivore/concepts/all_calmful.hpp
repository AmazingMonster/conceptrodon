// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_CALMFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_CALMFUL_H

#include "conceptrodon/omennivore/is_calmful.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllCalmful = (... && IsCalmful<Args>::value);

}}

#endif