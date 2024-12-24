/************************/
/**** Implementation ****/
/************************/

// `Radio` is a `Mold`.
template<template<typename...> class Radio>
struct Trip
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
           // First, we instantiate `Radio` and obtain a `typename`.
           // Then, we invoke `Car` with the resulting `typename`.
           template<typename...Signals>
           using Mold = Car<Radio<Signals...>>;
           
           // Helper function for the member template `Flow`.
           // This function transports the conjuration function `Mold` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<typename...> class...> class MoldVessel>
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
       // This is because `Agreements...` will be used to invoke `Trip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Mold>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Mold` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Mold>::template ProtoSail<Agreements...>;
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
           using Mold = Car<Radio<Signals...>::template Page>;

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
       using Road = Trip<Commit::template Mold>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Mold>::template ProtoSail<Agreements...>;
    };

    template<template<template<auto...> class...> class...Agreements>
    using Sail = ProtoSail<Agreements...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Oper_0 ****/
template<template<typename...> class Container>
struct Oper_0
{ 
    template<typename...Agreements>
    using Mold = Container<Agreements...>;
};

/**** Oper_1 ****/
template<auto Multiplier>
struct Oper_1
{
    template<typename>
    struct ProtoMold {};

    template<template<typename...> class Container, typename...Elements>
    struct ProtoMold<Container<Elements...>>
    {
       template<auto...J>
       using Page
       = Shuttle<Multiplier*Elements::value..., J...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/**** Oper_2 ****/
template<auto Variable>
struct Oper_2
{
    template<template<auto...> class Sequence>
    struct Detail
    {
        using type = Sequence<Variable>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};

/**** SupposedResult ****/
using SupposedResult = Shuttle<10*2, 10*3, '*'>;

/**** Metafunction ****/
using Metafunction = Trip<Oper_0<Capsule>::Mold>
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
    Oper_2<'*'>::Rail<
    Oper_1<10>::Mold<
    Oper_0<Capsule>::Mold<
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >
    >::Page
    >,
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