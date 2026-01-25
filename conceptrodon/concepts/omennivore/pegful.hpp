// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_PEGFUL_H
#define CONCEPTRODON_OMENNIVORE_PEGFUL_H

#include "conceptrodon/concepts/mouldivore/passed.hpp"
#include "conceptrodon/metafunctions/pagelivore/is_specialization_of.hpp"
#include "conceptrodon/utilities/peg.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Arg>
concept Pegful
= Mouldivore::Passed<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Arg>;

}}

#endif