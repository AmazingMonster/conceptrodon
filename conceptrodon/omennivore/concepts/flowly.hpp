// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_FLOWLY_H
#define CONCEPTRODON_OMENNIVORE_FLOWLY_H

#include "conceptrodon/fly.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Flowly = requires 
{typename Fly<Structure::template Flow>;};

}}

#endif