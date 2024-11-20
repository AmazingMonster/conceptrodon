// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_PEGFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_PEGFUL_H

#include "conceptrodon/mouldivore/concepts/all_confess.hpp"
#include "conceptrodon/pagelivore/is_specialization_of.hpp"
#include "conceptrodon/peg.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AllPegful
= Mouldivore::AllConfess<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Args...>;

}}

#endif