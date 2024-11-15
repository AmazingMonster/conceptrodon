// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_SAILLESS_H
#define CONCEPTRODON_OMENNIVORE_SAILLESS_H

#include "conceptrodon/sailfish.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Sailless = not requires 
{typename Sailfish<Structure::template Sail>;};

}}

#endif