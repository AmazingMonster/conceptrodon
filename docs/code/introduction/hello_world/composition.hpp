/************************/
/**** Implementation ****/
/************************/

template<template<template<auto...> class...> class Radio>
struct Trip
{
    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
        struct Commit
        {
            template<template<auto...> class...Signals>
            using Rail = Car<Radio<Signals...>::template Page>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Trip<Commit::template Rail>::template ProtoRail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
    
    template<template<auto...> class Car>
    struct ProtoRail
    {
        struct Commit
        {
            template<template<auto...> class...Signals>
            using Rail = Car<Radio<Signals...>::value>;
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

/******************/
/**** Examples ****/
/******************/

#include <concepts>

/**** DummyArg ****/
template<auto...>
struct DummyArg {};

/**** Oper_0 ****/
template<template<auto...> class...>
struct Oper_0 {};

template<>
struct Oper_0<DummyArg>
{
    template<auto...Args>
    requires (...&&(Args == 0))
    using Page = void;
};

/**** Oper_1 ****/
template<template<auto...> class Arg>
requires std::same_as<Arg<0>, void>
struct Oper_1
{
    static constexpr int value {24};
};

/**** Oper_2 ****/
template<auto Arg>
requires (Arg == 24)
struct Oper_2
{
    static constexpr int value {42};
};

/**** Test ****/
static_assert(
    Trip<Oper_0>
    ::Sail<Oper_1>
    ::Rail<Oper_2>
    ::Commit
    ::Rail<DummyArg>::value == 42
);