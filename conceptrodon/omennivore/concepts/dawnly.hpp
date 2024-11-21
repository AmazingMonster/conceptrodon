// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_DAWNLY_H
#define CONCEPTRODON_OMENNIVORE_DAWNLY_H

#include "conceptrodon/daydream.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Dawnly = requires 
{typename Daydream<Structure::template Dawn>;};

}}

#endif