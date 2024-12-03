// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ROADLY_H
#define CONCEPTRODON_OMENNIVORE_ROADLY_H

#include "conceptrodon/roy.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Roadly = requires 
{typename Roy<Structure::template Road>;};

}}

#endif