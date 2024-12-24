/**********************/
/**** Dependencies ****/
/**********************/

template<typename PackedVessel>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    // Invoke `Operation` with the `Elements...`.
    { using type = Operation<Elements...>; };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

template<template<template<auto...> class...> class Stockroom, template<auto...> class...Sequences>
struct Send<Stockroom<Sequences...>>
{
    template<template<template<auto...> class...> class Operation>
    struct Detail
    // Invoke `Operation` with the `Sequences...`.
    { using type = Operation<Sequences...>; };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = Detail<Agreements...>::type;
};

/************************/
/**** Implementation ****/
/************************/

// `Radio` is a `Mold`.
template<template<typename...> class Radio>
struct Trek
{
    /**** Define Road ****/
    // `Car` is a `Mold`.
    template<template<typename...> class Car>
    struct ProtoRoad
    {
       /**** Commitment ****/
       struct Commit
        {
           /**** Conjuration ****/
           // `Radio` and `Car` are composed here.
           template<typename...Signals>
           using Mold = Send<Radio<Signals...>>::template Road<Car>;
           template<template<template<typename...> class...> class MoldVessel>

           // Helper function for the member template `Flow`.
           // This function transports the conjuration function `Mold` without invoking it, 
           // allowing further process by other higher-order functions.
           struct Detail
           {
               // We transfer the conjuration function `Mold` to `MoldVessel`.
               using type = MoldVessel<Mold>;
           };
           
           /**** Transition ****/
           template<template<template<typename...> class...> class...Agreements>
           using Flow = Detail<Agreements...>::type;
        };

       /**** Continuation ****/
       // This function composes the conjuration function `Mold` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `Trek<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Mold>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Mold` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trek<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Mold>::template ProtoSail<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;

    /**** Define Sail ****/
    // This function is the similar the `ProtoRoad` defined above.
    // It handles the case where `Car` is a `Rail`.
    template<template<template<auto...> class...> class Car>
    struct ProtoSail
    {
       /**** Commitment ****/
       struct Commit
       {
           /**** Conjuration ****/
           template<typename...Signals>
           using Mold = Send<Radio<Signals...>>::template Sail<Car>;

           template<template<template<typename...> class...> class MoldVessel>
           struct Detail
           {
              using type = MoldVessel<Mold>;
           };

           /**** Transition ****/
           template<template<template<typename...> class...> class...Agreements>
           using Flow = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       template<template<typename...> class...Agreements>
       using Road = Trek<Commit::template Mold>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trek<Commit::template Mold>::template ProtoSail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/**** Oper_0 ****/
template<template<auto...> class Sequence>
struct Oper_0
{ 
    template<typename...Vay>
    struct Detail
    {
        using type = Capsule<Sequence<Vay::value>...>;
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

/**** Oper_1 ****/
template<auto Multiplier>
struct Oper_1
{
    template<typename...>
    struct Detail {};

    template<template<auto...> class Sequence, auto...I>
    struct Detail<Sequence<I...>>
    {
       template<auto...J>
       using Page = Sequence<Multiplier*I..., J...>;
    };

    template<typename...Agreements>
    using Mold = Carrier<Detail<Agreements>::template Page...>;
};

/**** Oper_2 ****/
template<auto Variable>
struct Oper_2
{
    template<template<auto...> class...Sequences>
    struct Detail
    {
        using type = Capsule<Sequences<Variable>...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

/**** SupposedResult ****/
using SupposedResult = Capsule<Shuttle<10*2, '*'>, Shuttle<10*3, '*'>>;

/**** Metafunction ****/
using Metafunction = Trek<Oper_0<Shuttle>::Mold>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Mold
<
    std::integral_constant<int, 2>,
    std::integral_constant<int, 3>
>;

/**** Tests ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send
        <
            Oper_0<Shuttle>::Mold
            <
                std::integral_constant<int, 2>,
                std::integral_constant<int, 3>
            >
        >
        ::Road<Oper_1<10>::Mold>
    >
    ::Sail<Oper_2<'*'>::Rail>
    ,
    SupposedResult
>);

/************************/
/**** Second Example ****/
/************************/

/**** InvokeMold ****/
template<template<typename...> class MoldArg>
struct InvokeMoldDetail
{
    using type = MoldArg
    <
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >;
};

template<template<typename...> class...Args>
using InvokeMold = InvokeMoldDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Flow<InvokeMold>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);