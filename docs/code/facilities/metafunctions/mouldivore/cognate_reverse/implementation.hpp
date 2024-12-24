/**********************/
/**** Dependencies ****/
/**********************/

/**** ExtendBack ****/
template<typename...>
struct ExtendBack {};

template<
    template<typename...> class Container,
    typename...Elements
>
struct ExtendBack<Container<Elements...>>
{
    template<typename...Agreements>
    using Mold = Container<Elements..., Agreements...>;
};

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Typelivore::TypicalTurnOver ****/
namespace Typelivore {

template<typename...>
struct TypicalTurnOver {};

template<typename First>
struct TypicalTurnOver<First>
{
    using type = Capsule<First>;
};

template<typename First, typename Second>
struct TypicalTurnOver<First, Second>
{
    using type = Capsule<Second, First>;
};

template<typename First, typename Second, typename...Others>
struct TypicalTurnOver<First, Second, Others...>
{
    using type 
    = ExtendBack<typename TypicalTurnOver<Others...>::type>
    ::template Mold<Second, First>;
};

}

/**** Send ****/
template<typename...>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct CognateReverse
{
    template<typename...Elements>
    using Mold = Send<typename Typelivore::TypicalTurnOver<Elements...>::type>
    ::template Road<Operation>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int**, int**, int*, int>;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateReverse<Operation>::Mold<Args...>;

/**** Result ****/
using Result = Metafunction<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);