// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

/**** Fun ****/
template<typename...>
struct Fun
{
    template<template<typename...> class...>
    struct ProtoRoad
    {
        template<auto...>
        struct ProtoPage
        {
            template<template<auto...> class...>
            struct ProtoRail
            {
                static constexpr bool value {true}; 
            };

            template<template<auto...> class...Sequences>
            using Rail = ProtoRail<Sequences...>;
        };

        template<auto...Variables>
        using Page = ProtoPage<Variables...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;
};

/**** Gun ****/
template<typename Element>
struct Gun
{
    using type = Element;
};

/**** Pun ****/
template<template<typename...> class Operation>
struct Pun
{
    template<typename...Elements>
    using Mold = Operation<Elements...>;
};

#if 0

/**** Mouldivore::ClassicTrip ****/
namespace Mouldivore {

template<template<typename...> class Radio>
struct ClassicTrip
{
    template<template<typename...> class Car>
    struct ProtoRoad
    {
        struct Commit
        {
           template<typename...Signals>
           using Mold = Car<typename Radio<Signals...>::type>;
        };
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}

/**** Roadrivore::Trip ****/
namespace Roadrivore {

template<template<template<typename...> class...> class Radio>
struct Trip
{
    template<template<template<typename...> class...> class Car>
    struct ProtoFlow
    {
        struct Commit
        {
           template<template<typename...> class...Signals>
           using Road = Car<Radio<Signals...>::template Mold>;
        };
    };

    template<template<template<typename...> class...> class...Agreements>
    using Flow = ProtoFlow<Agreements...>;
};

}

/**** FunGun ****/
template<typename...Args>
using FunGun = Mouldivore::ClassicTrip<Gun>
::Road<Fun>
::Commit
::Mold<Args...>;

/**** VoidifiedFunGun ****/
template<template<typename...> class...Args>
using VoidifiedFunGun = FunGun<void>
::Road<Args...>;

/**** FunGunPun ****/
template<template<typename...> class...Args>
using FunGunPun = Roadrivore::Trip<Pun>
::Flow<VoidifiedFunGun>
::Commit
::Road<Args...>;

#else

#include "conceptrodon/metafunctions/roadrivore/trip.hpp"
#include "conceptrodon/metafunctions/mouldivore/classic_trip.hpp"

/**** FunGun ****/
template<typename...Args>
using FunGun = Conceptrodon::Mouldivore::ClassicTrip<Gun>
::Road<Fun>
::Commit
::Mold<Args...>;

/**** VoidifiedFunGun ****/
template<template<typename...> class...Args>
using VoidifiedFunGun = FunGun<void>
::Road<Args...>;

/**** FunGunPun ****/
template<template<typename...> class...Args>
using FunGunPun = Conceptrodon::Roadrivore::Trip<Pun>
::Flow<VoidifiedFunGun>
::Commit
::Road<Args...>;

#endif

/***************/
/**** Tests ****/
/***************/

#include <concepts>

template<typename...>
struct Arg;

static_assert(std::same_as<FunGunPun<Arg>,

Fun<Gun<void>::type>
::Road<Pun<Arg>::Mold>

>);