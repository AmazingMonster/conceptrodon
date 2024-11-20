// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_UNPEGFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_UNPEGFUL_H

#include "conceptrodon/descend/omennivore/concepts/descend/all_unpageful.hpp"
#include "conceptrodon/mouldivore/concepts/any_deceive.hpp"
#include "conceptrodon/pagelivore/is_specialization_of.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/descend/any_unpageful.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/descend/all_unpegful.hpp"
#include "conceptrodon/peg.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAnyUnpegful = Mouldivore::AnyDeceive<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Args...>;

template<typename...Args>
concept AnyUnpegful
= (
        Mouldivore::AnyDeceive<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Args...>
    &&  AnyUnpageful<Args...>
) || AllUnpageful<Args...>;

}}

#endif