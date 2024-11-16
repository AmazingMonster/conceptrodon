// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNPEGFUL_H
#define CONCEPTRODON_OMENNIVORE_UNPEGFUL_H

#include "conceptrodon/pagelivore/is_specialization_of.hpp"
#include "conceptrodon/typelivore/concepts/falsify.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/unpageful.hpp"
#include "conceptrodon/peg.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Unpegful
=   Typelivore::Falsify<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Arg>
||  Unpageful<Arg>;

}}

#endif