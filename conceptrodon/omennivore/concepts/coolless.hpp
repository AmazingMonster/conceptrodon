// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_COOLLESS_H
#define CONCEPTRODON_OMENNIVORE_COOLLESS_H

#include "conceptrodon/coy.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Coolless = not requires 
{typename Coy<Structure::template Cool>;};

}}

#endif