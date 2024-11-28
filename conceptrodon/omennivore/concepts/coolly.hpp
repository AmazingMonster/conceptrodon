// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_COOLLY_H
#define CONCEPTRODON_OMENNIVORE_COOLLY_H

#include "conceptrodon/coalfish.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Coolly = requires 
{typename Coalfish<Structure::template Cool>;};

}}

#endif