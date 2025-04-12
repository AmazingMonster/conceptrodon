// Copyright 2025 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_FUNCTIVORE_ARE_SAME_TYPE_SIGNATURE_AS_H
#define CONCEPTRODON_FUNCTIVORE_ARE_SAME_TYPE_SIGNATURE_AS_H

#include <type_traits>
#include "conceptrodon/functivore/analyzer.hpp"

/******************************************************************************************************/
namespace Conceptrodon {
namespace Functivore {

template <typename Known>
struct AreSameTypeSignatureAs
{
    template<typename...Unknowns>
    struct ProtoMold
    {
        static constexpr bool value
        {
            (...&&(
                std::is_same_v<typename Analyzer<Unknowns>::type_signature, typename Analyzer<Known>::type_signature>
            ))
        };
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;

    template<typename...Unknowns>
    static constexpr bool Mold_v
    {
        (...&&(
            std::is_same_v<typename Analyzer<Unknowns>::type_signature, typename Analyzer<Known>::type_signature>
        ))
    };
};

}}
/******************************************************************************************************/

#endif
