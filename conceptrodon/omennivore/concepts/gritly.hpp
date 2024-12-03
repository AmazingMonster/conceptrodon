// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_GRITLY_H
#define CONCEPTRODON_OMENNIVORE_GRITLY_H

#include "conceptrodon/gry.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Gritly = requires 
{typename Gry<Structure::template Grit>;};

}}

#endif