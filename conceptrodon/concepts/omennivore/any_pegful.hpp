// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_ANY_PEGFUL_H
#define CONCEPTRODON_OMENNIVORE_ANY_PEGFUL_H

#include "conceptrodon/concepts/mouldivore/any_passed.hpp"
#include "conceptrodon/metafunctions/pagelivore/is_specialization_of.hpp"
#include "conceptrodon/concepts/omennivore/all_pegful.hpp"
#include "conceptrodon/utilities/peg.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Args>
concept AnyPegful
=   Mouldivore::AnyPassed<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Args...>
||  AllPegful<Args...>;

}}

#endif