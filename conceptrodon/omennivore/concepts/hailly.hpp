// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_HAILLY_H
#define CONCEPTRODON_OMENNIVORE_HAILLY_H

#include "conceptrodon/halfmoon.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Hailly = requires 
{typename Halfmoon<Structure::template Hail>;};

}}

#endif