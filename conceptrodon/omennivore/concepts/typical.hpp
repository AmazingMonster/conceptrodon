// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_TYPICAL_H
#define CONCEPTRODON_OMENNIVORE_TYPICAL_H

namespace Conceptrodon {
namespace Omennivore {

template<typename Structure>
concept Typical = requires 
{typename Structure::type;};

}}

#endif