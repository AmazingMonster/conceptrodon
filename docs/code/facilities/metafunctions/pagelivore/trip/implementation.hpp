/************************/
/**** Implementation ****/
/************************/

// `Radio` is a `Page`.
template<template<auto...> class Radio>
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
           template<auto...Signals>
           using Page = Car<Radio<Signals...>>;

           // Helper function for the member template `Sail`.
           // This function transports the conjuration function `Page` without invoking it, 
           // allowing further process by other higher-order functions.
           template<template<template<auto...> class...> class PageVessel>
           struct Detail
           {
               // We transfer the conjuration function `Page` to `PageVessel`.
               using type = PageVessel<Page>;
           };

           /**** Transition ****/
           template<template<template<auto...> class...> class...Agreements>
           using Sail = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       // This function composes the conjuration function `Page` and the `Agreements...`.
       // Note that even though `Agreements...` is variadic, it only allows a single argument.
       // This is because `Agreements...` will be used to invoke `Trip<*>::ProtoRoad`,
       // which has only one parameter `Car`.
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Page>::template ProtoRoad<Agreements...>;

       // This function composes the conjuration function `Page` and the `Agreements...`.
       // `Agreements` will be used to invoke `Trip<*>::ProtoSail.
       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Page>::template ProtoSail<Agreements...>;
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
           template<auto...Signals>
           using Page = Car<Radio<Signals...>::template Page>;

           template<template<template<auto...> class...> class PageVessel>
           struct Detail
           {
              using type = PageVessel<Page>;
           };

           /**** Transition ****/
           template<template<template<auto...> class...> class...Agreements>
           using Sail = Detail<Agreements...>::type;
       };

       /**** Continuation ****/
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Page>::template ProtoRoad<Agreements...>;

       template<template<template<auto...> class...> class...Agreements>
       using Sail = Trip<Commit::template Page>::template ProtoSail<Agreements...>;
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

/**** Oper_0 ****/
template<template<auto...> class Sequence>
struct Oper_0
{ 
    template<auto...Agreements>
    using Page = Sequence<Agreements...>;
};

/**** Oper_1 ****/
template<auto Multiplier>
struct Oper_1
{
    template<typename>
    struct ProtoMold {};

    template<template<auto...> class Sequence, auto...I>
    struct ProtoMold<Sequence<I...>>
    {
       template<auto...J>
       using Page = Sequence<Multiplier*I..., J...>;
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
using Metafunction = Trip<Oper_0<Shuttle>::Page>
::Road<Oper_1<10>::Mold>
::Sail<Oper_2<'*'>::Rail>
::Commit;

/**** Result ****/
using Result = Metafunction::Page<2, 3>;

/**** Tests ****/
static_assert(std::same_as<Result, SupposedResult>);

// The following `static_assert` shows how the operations are composed:
static_assert(std::same_as<
    Oper_2<'*'>::Rail<
    Oper_1<10>::Mold<
    Oper_0<Shuttle>::Page<
        2, 3
    >
    >::Page
    >,
    SupposedResult
>);

/************************/
/**** Second Example ****/
/************************/

/**** InvokePage ****/
template<template<auto...> class PageArg>
struct InvokePageDetail
{
    using type = PageArg<2, 3>;
};

template<template<auto...> class...Args>
using InvokePage = InvokePageDetail<Args...>::type;

/**** Result ****/
using Result_1 = Metafunction::Sail<InvokePage>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult>);