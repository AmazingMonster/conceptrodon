// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_WILLLY_H
#define CONCEPTRODON_OMENNIVORE_WILLLY_H

#include "conceptrodon/wildfire.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Willly = requires 
{typename Wildfire<Structure::template Will>;};

}}

#endif