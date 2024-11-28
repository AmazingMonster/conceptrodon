// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_FLOWLESS_H
#define CONCEPTRODON_OMENNIVORE_FLOWLESS_H

#include "conceptrodon/florican.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Flowless = not requires 
{typename Florican<Structure::template Flow>;};

}}

#endif