// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_PEGFUL_H
#define CONCEPTRODON_OMENNIVORE_PEGFUL_H

#include "conceptrodon/pagelivore/is_specialization_of.hpp"
#include "conceptrodon/typelivore/concepts/clarify.hpp"
#include "conceptrodon/omennivore/concepts/pageful.hpp"
#include "conceptrodon/peg.hpp"

namespace Conceptrodon {
namespace Omennivore {
    
template<typename Arg>
concept Pegful
=   Typelivore::Clarify<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Arg>
&&  Pageful<Arg>;


template<typename...>
struct Tester {};

template<typename Arg>
requires Typelivore::Clarify<Pagelivore::IsSpecializationOf<Peg>::ProtoMold, Arg>
struct Tester<Arg>
{
    static constexpr bool value
    {false};
};

template<typename Arg>
requires Pegful<Arg>
struct Tester<Arg>
{
    static constexpr bool value
    {true};
};

template<typename Arg>
requires Pageful<Arg>
struct Tester<Arg>
{
    static constexpr bool value
    {false};
};

template<auto...>
struct Holder {};

static_assert(Tester<Peg<10>>::value);
static_assert(! Tester<Holder<10>>::value);

}}

#endif