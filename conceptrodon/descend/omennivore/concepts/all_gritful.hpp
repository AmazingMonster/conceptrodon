// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_GRITFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_GRITFUL_H

#include "conceptrodon/omennivore/is_gritful.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllGritful = (... && IsGritful<Args>::value);

}}

#endif