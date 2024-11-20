// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_PEGFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_PEGFUL_H

#include "conceptrodon/mouldivore/concepts/any_confess.hpp"
#include "conceptrodon/pagelivore/is_specialization_of.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/any_pageful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_pegful.hpp"
#include "conceptrodon/peg.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyPegful = Mouldivore::AnyConfess<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Args...>;

template<typename...Args>
concept AnyPegful
= (
       Mouldivore::AnyConfess<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Args...>
    && AnyPageful<Args...>
) || AllPegful<Args...>;

}}

#endif