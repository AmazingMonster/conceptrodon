// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ALL_UNPEGFUL_H
#define CONCEPTRODON_OMENNIVORE_ALL_UNPEGFUL_H

#include "conceptrodon/mouldivore/concepts/all_deceive.hpp"
#include "conceptrodon/pagelivore/is_specialization_of.hpp"
#include "conceptrodon/descend/omennivore/concepts/descend/all_unpageful.hpp"
#include "conceptrodon/peg.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept JustAllUnpegful = Mouldivore::AllDeceive<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Args...>;

template<typename...Args>
concept AllUnpegful
=   Mouldivore::AllDeceive<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Args...>
||  AllUnpageful<Args...>;

}}

#endif