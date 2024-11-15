// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_LULLLESS_H
#define CONCEPTRODON_OMENNIVORE_LULLLESS_H

#include "conceptrodon/lungfish.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Lullless = not requires 
{typename Lungfish<Structure::template Lull>;};

}}

#endif