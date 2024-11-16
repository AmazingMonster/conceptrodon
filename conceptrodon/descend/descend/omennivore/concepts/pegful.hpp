// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_PEGFUL_H
#define CONCEPTRODON_OMENNIVORE_PEGFUL_H

#include "conceptrodon/pagelivore/is_specialization_of.hpp"
#include "conceptrodon/typelivore/concepts/clarify.hpp"
#include "conceptrodon/descend/omennivore/concepts/pageful.hpp"
#include "conceptrodon/peg.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Pegful
=   Typelivore::Clarify<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Arg>
&&  Pageful<Arg>;

}}

#endif