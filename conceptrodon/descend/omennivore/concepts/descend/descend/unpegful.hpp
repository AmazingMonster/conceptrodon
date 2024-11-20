// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNPEGFUL_H
#define CONCEPTRODON_OMENNIVORE_UNPEGFUL_H

#include "conceptrodon/mouldivore/concepts/deceive.hpp"
#include "conceptrodon/pagelivore/is_specialization_of.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/unpageful.hpp"
#include "conceptrodon/peg.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Arg>
concept JustUnpegful = Mouldivore::Deceive<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Arg>;

template<typename Arg>
concept Unpegful
=   Mouldivore::Deceive<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Arg>
||  Unpageful<Arg>;

}}

#endif