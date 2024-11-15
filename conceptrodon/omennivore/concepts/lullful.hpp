// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_LULLFUL_H
#define CONCEPTRODON_OMENNIVORE_LULLFUL_H

#include "conceptrodon/omennivore/is_lullful.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Lullful = IsLullful_v<Arg>;

}}

#endif