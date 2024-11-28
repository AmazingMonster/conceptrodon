// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_DAWNLESS_H
#define CONCEPTRODON_OMENNIVORE_DAWNLESS_H

#include "conceptrodon/daydream.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Dawnless = not requires 
{typename Daydream<Structure::template Dawn>;};

}}

#endif