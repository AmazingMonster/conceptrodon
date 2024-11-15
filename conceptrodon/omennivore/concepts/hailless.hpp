// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_HAILLESS_H
#define CONCEPTRODON_OMENNIVORE_HAILLESS_H

#include "conceptrodon/halfmoon.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Hailless = not requires 
{typename Halfmoon<Structure::template Hail>;};

}}

#endif