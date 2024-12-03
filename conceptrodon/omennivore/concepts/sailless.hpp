// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_SAILLESS_H
#define CONCEPTRODON_OMENNIVORE_SAILLESS_H

#include "conceptrodon/say.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Sailless = not requires 
{typename Say<Structure::template Sail>;};

}}

#endif