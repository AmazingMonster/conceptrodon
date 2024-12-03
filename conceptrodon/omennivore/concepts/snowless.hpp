// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_SNOWLESS_H
#define CONCEPTRODON_OMENNIVORE_SNOWLESS_H

#include "conceptrodon/sny.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Snowless = not requires 
{typename Sny<Structure::template Snow>;};

}}

#endif