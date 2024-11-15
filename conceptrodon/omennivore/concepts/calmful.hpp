// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_CALMFUL_H
#define CONCEPTRODON_OMENNIVORE_CALMFUL_H

#include "conceptrodon/omennivore/is_calmful.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Calmful = IsCalmful_v<Arg>;

}}

#endif