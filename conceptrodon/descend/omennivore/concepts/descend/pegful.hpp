// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_PEGFUL_H
#define CONCEPTRODON_OMENNIVORE_PEGFUL_H

#include "conceptrodon/mouldivore/concepts/confess.hpp"
#include "conceptrodon/pagelivore/is_specialization_of.hpp"
#include "conceptrodon/descend/omennivore/concepts/pageful.hpp"
#include "conceptrodon/peg.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Arg>
concept JustPegful = Mouldivore::Confess<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Arg>;

template<typename Arg>
concept Pegful
=   Mouldivore::Confess<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Arg>
&&  Pageful<Arg>;

}}

#endif