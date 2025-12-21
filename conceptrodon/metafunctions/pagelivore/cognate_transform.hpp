// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_TRANSFORM_H
#define CONCEPTRODON_PAGELIVORE_TRANSFORM_H

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class Operation>
struct CognateTransform
{
    template<template<auto...> class...Puberty>
    struct ProtoRail
    {
        struct Slash
        {
            template<template<auto...> class...Hormones>
            struct ProtoRail
            {
                template<template<auto...> class Hormone, auto Variable>
                struct Detail
                {
                    static constexpr auto value
                    {Variable};
                };

                template<template<auto...> class Hormone, auto Variable>
                requires (...&&Puberty<Variable>::value)
                struct Detail<Hormone, Variable>
                {
                    static constexpr auto value
                    {Hormone<Variable>::value};
                };

                template<auto...Variables>
                struct Hidden 
                { using type = Operation<Detail<Hormones, Variables>::value...>; };

                template<auto Variable>
                struct Hidden<Variable>
                { using type = Operation<Detail<Hormones, Variable>::value...>; };

                template<auto...Variables>
                using Page = Hidden<Variables...>::type;
            };

            template<template<auto...> class Hormone>
            struct ProtoRail<Hormone>
            {
                template<auto Variable>
                struct Hidden 
                {
                    static constexpr auto value
                    {Variable};
                };

                template<auto Variable>
                requires (...&&Puberty<Variable>::value)
                struct Hidden<Variable>
                {
                    static constexpr auto value
                    {Hormone<Variable>::value};
                };

                template<auto...Variables>
                using Page = Operation<Hidden<Variables>::value...>;
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = Slash::template ProtoRail<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

}}

#endif