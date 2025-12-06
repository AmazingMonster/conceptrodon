/**********************/
/**** Dependencies ****/
/**********************/

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Omennivore::Press ****/
namespace Omennivore {

template<typename Operation>
struct Press
{
    template<typename...>
    struct Detail {};

// Base case:

    template
    <
        template<typename...> class Container,
        // There is only one parameter pack left.
        typename...Contents
    >
    struct Detail<Container<Contents...>>
    {
        // We invoke the corresponding template member of the operation
        // with the extracted pack.
        using type = Operation::template Mold<Contents...>; 
    };

    template
    <
        template<auto...> class Sequence,
        auto...Contents
    >
    struct Detail<Sequence<Contents...>>
    { using type = Operation::template Page<Contents...>; };

// Recursive case:

    template
    <
        template<typename...> class Container,
        // We separate the first parameter pack from the others.
        typename...Contents,
        typename...Others
    >
    struct Detail<Container<Contents...>, Others...>
    {
        using type = Press
        <
            // We invoke the corresponding template member of the operation
            // with the extracted pack.
            // Then, we pass the result back to Press for further invocations.
            typename Operation::template Mold<Contents...>
        >
        // Unused packs are recycled for further invocations.
        ::template Detail<Others...>::type;
    };

    template
    <
        template<auto...> class Sequence,
        auto...Contents,
        typename...Others
    >
    struct Detail<Sequence<Contents...>, Others...>
    {
        using type = Press<typename Operation::template Page<Contents...>>
        ::template Detail<Others...>::type;
    };
    
    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

}

/************************/
/**** Implementation ****/
/************************/

/**** LoadSkip ****/
// We will use `Items` to keep track of user inputs.
template<template<typename...> class Operation, typename...Items>
struct LoadSkip
{
    // If `Mold` is selected, user inputs will be kept
    // in a `Capsule` and placed at the end of `Items.`
    // Then, we pass the extended `Items` back to `LoadSkip`,
    // waiting for more inputs.
    template<typename...Elements>
    using Mold = LoadSkip<Operation, Items..., Capsule<Elements...>>;

    // If `Page` is selected, user inputs will be kept
    // in a `Shuttle` and placed at the end of `Items.`
    // Then, we pass the extended `Items` back to `LoadSkip`,
    // waiting for more inputs.
    template<auto...Variables>
    using Page = LoadSkip<Operation, Items..., Shuttle<Variables...>>;

    struct Commit
    {
        template<typename...Elements>
        // When finally initiating the operation, we invoke the skipped layer.
        // Then, we pass the instantiated operation and user inputs
        // to Omennivore::Press for further invocations.
        using Mold = Omennivore::Press<Operation<Elements...>>
        ::template Mold<Items...>;
    };
};

/**** Skip ****/
template<template<typename...> class Operation>
struct Skip: public LoadSkip<Operation> {};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<typename...>
struct Operation
{ 
    template<typename...>
    struct ProtoMold
    {
        template<auto...>
        struct ProtoPage {};

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/**** SupposedResult ****/
using SupposedResult = Operation<int>
::Mold<void>
::Page<0>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Skip<Operation>::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<void>::Page<0>::Commit::Mold<int>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);