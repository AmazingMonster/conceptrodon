// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_PAGEFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_PAGEFUL_H

#include "conceptrodon/omennivore/is_pageful.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename...Args>
concept AllPageful = (... && IsPageful<Args>::value);

}}

#endif