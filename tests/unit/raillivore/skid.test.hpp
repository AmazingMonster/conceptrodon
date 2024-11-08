// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_RAILLIVORE_SKID_H
#define CONCEPTRODON_TESTS_UNIT_RAILLIVORE_SKID_H

#include "conceptrodon/descend/raillivore/skid.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"
#include <utility>

namespace Conceptrodon {
namespace Raillivore {
namespace UnitTests {
namespace TestSkid {

template<template<auto...> class...>
struct Tester
{
    template<typename...>
    struct ProtoMold
    {
        template<auto...>
        struct ProtoPage
        {
            template<template<typename...> class...>
            struct ProtoRoad
            {
                template<template<auto...> class...>
                struct ProtoRail
                {
                    template<template<template<typename...> class...> class...>
                    struct ProtoFlow
                    {
                        template<template<template<auto...> class...> class...>
                        struct ProtoSail
                        {
                            template<template<template<template<typename...> class...> class...> class...>
                            struct ProtoSnow
                            {
                                template<template<template<template<auto...> class...> class...> class...>
                                struct ProtoHail
                                {
                                    template<template<template<template<template<typename...> class...> class...> class...> class...>
                                    struct ProtoLull
                                    {
                                        template<template<template<template<template<auto...> class...> class...> class...> class...>
                                        struct ProtoCalm
                                        {
                                            template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
                                            struct ProtoGrit
                                            {
                                                template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
                                                struct ProtoWill
                                                {
                                                    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
                                                    struct ProtoGlow
                                                    {
                                                        template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
                                                        struct ProtoDawn
                                                        {
                                                            static constexpr bool value {true};
                                                        };

                                                        template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Agreements>
                                                        using Dawn = ProtoDawn<Agreements...>;
                                                    };

                                                    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Agreements>
                                                    using Glow = ProtoGlow<Agreements...>;
                                                };

                                                template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Agreements>
                                                using Will = ProtoWill<Agreements...>;
                                            };

                                            template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Agreements>
                                            using Grit = ProtoGrit<Agreements...>;
                                        };

                                        template<template<template<template<template<auto...> class...> class...> class...> class...Agreements>
                                        using Calm = ProtoCalm<Agreements...>;
                                    };

                                    template<template<template<template<template<typename...> class...> class...> class...> class...Agreements>
                                    using Lull = ProtoLull<Agreements...>;
                                };

                                template<template<template<template<auto...> class...> class...> class...Agreements>
                                using Hail = ProtoHail<Agreements...>;
                            };

                            template<template<template<template<typename...> class...> class...> class...Agreements>
                            using Snow = ProtoSnow<Agreements...>;
                        };

                        template<template<template<auto...> class...> class...Agreements>
                        using Sail = ProtoSail<Agreements...>;
                    };

                    template<template<template<typename...> class...> class...Agreements>
                    using Flow = ProtoFlow<Agreements...>;
                };

                template<template<auto...> class...Agreements>
                using Rail = ProtoRail<Agreements...>;
            };

            template<template<typename...> class...Agreements>
            using Road = ProtoRoad<Agreements...>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;

        struct Slash
        {
            template<typename...>
            struct ProtoMold
            {
                static constexpr bool value {false};
            };
            
            template<>
            struct ProtoMold<std::true_type>
            {
                static constexpr bool value {true};
            };
        };

        template<typename...Agreements>
        using Mold = Slash::template ProtoMold<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};


template<>
struct Tester<std::index_sequence>
{
    template<auto...>
    struct ProtoPage
    {
        static constexpr bool value {false};
    };

    template<>
    struct ProtoPage<true>
    {
        static constexpr bool value {true};
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};


VALID(Skid<Tester>::Mold<>::Page<>::Road<>::R_il<>::Flow<>::Sail<>::Snow<>::Hail<>::Lull<>::Calm<>::Grit<>::Will<>::Glow<>::Dawn<>::Rail<>::value);
VALID(Skid<Tester>::Mold<>::Mold<std::true_type>::Rail<>::value);
VALID(Skid<Tester>::Page<true>::Rail<std::index_sequence>::value);


}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif