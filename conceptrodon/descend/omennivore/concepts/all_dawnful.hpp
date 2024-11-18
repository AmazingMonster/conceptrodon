// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_DAWNFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_DAWNFUL_H

#include "conceptrodon/omennivore/is_dawnful.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllDawnful = (... && IsDawnful<Args>::value);

}}

#endif