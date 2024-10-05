// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_NOT_PEG_H
#define CONCEPTRODON_OMENNIVORE_NOT_PEG_H

#include "conceptrodon/pagelivore/is_specialization.hpp"
#include "conceptrodon/peg.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept NotPeg = not Pagelivore::IsSpecializationOf<Peg>::ProtoMold<Arg>::value;

}}

#endif