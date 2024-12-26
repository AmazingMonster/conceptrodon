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

// `Radio` is a `Road`.
template<template<template<typename...> class...> class Radio>
struct ClassicTrek
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
           template<template<typename...> class...Signals>
           using Road = Send<typename Radio<Signals...>::type>::template Road<Car>;

           // Helper function for the member template `Snow`.
           // This function transports the conjuration function `Road` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<template<typename...> class...> class...> class RoadVessel>
           struct Detail
           {
               // We transfer the conjuration function `Road` to `RoadVessel`.
               using type = RoadVessel<Road>;
           };

           /**** Transition ****/
           template<template<template<template<typename...> class...> class...> class...Agreements>
           using Snow = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       // This function composes the conjuration function `Road` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `ClassicTrek<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = ClassicTrek<Commit::template Road>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Road` and the `Agreements...`.
       // `Agreements` will be used to invoke `ClassicTrek<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Road>::template ProtoSail<Agreements...>;
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
           template<template<typename...> class...Signals>
           using Road = Send<typename Radio<Signals...>::type>::template Sail<Car>;

           template<template<template<template<typename...> class...> class...> class RoadVessel>
           struct Detail
           {
              using type = RoadVessel<Road>;
           };

           /**** Transition ****/
           template<template<template<template<typename...> class...> class...> class...Agreements>
           using Snow = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       template<template<typename...> class...Agreements>
       using Road = ClassicTrek<Commit::template Road>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = ClassicTrek<Commit::template Road>::template ProtoSail<Agreements...>;
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

/**** Capsules ****/
template<typename...>
struct Capsule;

template<typename...>
struct Capsule_1;

template<typename...>
struct Capsule_2;

/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/**** Oper_0 ****/
template<auto Variable>
struct Oper_0
{ 
    template<template<typename...> class...Containers>
    struct ProtoRoad
    {
        using type = Capsule<Containers<Shuttle<Variable>>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/**** Oper_1 ****/
template<auto Multiplier>
struct Oper_1
{
    template<typename...>
    struct Detail {};

    template
    <
        template<typename...> class Container,
        template<auto...> class Sequence,
        auto...I
    >
    struct Detail<Container<Sequence<I...>>>
    {
       template<auto...J>
       using Page = Container<Sequence<Multiplier*I..., J...>>;
    };

    template<typename...Agreements>
    struct ProtoMold
    {
        using type = Carrier<Detail<Agreements>::template Page...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
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
using SupposedResult = Capsule<Capsule_1<Shuttle<10*2, '*'>>, Capsule_2<Shuttle<10*2, '*'>>>;

/**** Metafunction ****/
using Metafunction = ClassicTrek<Oper_0<2>::Road>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Road<Capsule_1, Capsule_2>;

/**** Tests ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Send
    <
        Send<Oper_0<2>::Road<Capsule_1, Capsule_2>::type>
        ::Road<Oper_1<10>::Mold>::type
    >
    ::Sail<Oper_2<'*'>::Rail>
    ,
    SupposedResult
>);

/************************/
/**** Second Example ****/
/************************/

/**** InvokeRoad ****/
template<template<template<typename...> class...> class RoadArg>
struct InvokeRoadDetail
{
    using type = RoadArg<Capsule_1, Capsule_2>;
};

template<template<template<typename...> class...> class...Args>
using InvokeRoad = InvokeRoadDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Snow<InvokeRoad>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);