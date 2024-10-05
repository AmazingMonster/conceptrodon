// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNTYPICAL_H
#define CONCEPTRODON_OMENNIVORE_UNTYPICAL_H

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Untypical = not requires 
{typename Structure::type;};

}}

#endif