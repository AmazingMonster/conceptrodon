// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_MOLDFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_MOLDFUL_H

#include "conceptrodon/omennivore/is_moldful.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllMoldful = (... && IsMoldful<Args>::value);

}}

#endif