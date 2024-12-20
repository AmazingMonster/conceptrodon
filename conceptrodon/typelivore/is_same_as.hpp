// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_IS_SAME_AS_H
#define CONCEPTRODON_TYPELIVORE_IS_SAME_AS_H

namespace Conceptrodon {
namespace Typelivore {

template<typename Target>
struct IsSameAs
{
    template<typename>
    struct ProtoMold 
    { static constexpr bool value {false}; };

    template<>
    struct ProtoMold<Target> 
    { static constexpr bool value {true}; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr bool Mold_v 
    {ProtoMold<Args...>::value};
};

}}

#endif