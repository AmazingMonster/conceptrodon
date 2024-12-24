/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct CognateTransform
{
    template<template<typename...> class...Puberty>
    struct ProtoRoad
    {
        struct Slash
        {
            template<template<typename...> class Hormone>
            struct ProtoRoad
            {
                template<typename Element>
                struct Hidden 
                {
                    using type = Element;
                };

                template<typename Element>
                requires (...&&Puberty<Element>::value)
                struct Hidden<Element>
                {
                    // `Hormone` is the transformation.
                    using type = Hormone<Element>;
                };

                template<typename...Elements>
                using Mold = Operation<typename Hidden<Elements>::type...>;
            };
        };

        template<template<typename...> class...Agreements>
        using Road = Slash::template ProtoRoad<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** DivisibleByTwo ****/
template<typename Val>
struct DivisibleByTwo
{
    static constexpr bool value
    {Val::value % 2 == 0};
};

/**** DivisibleByThree ****/
template<typename Val>
struct DivisibleByThree
{
    static constexpr bool value
    {Val::value % 3 == 0};
};

/**** UnaryMinus ****/
template<typename Val>
struct UnaryMinusHelper
{
    using type = Vay<-Val::value>;
};

template<typename...Args>
using UnaryMinus = UnaryMinusHelper<Args...>::type;

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateTransform<Operation>
::Road<DivisibleByTwo, DivisibleByThree>
::Road<UnaryMinus>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation
<Vay<1>, Vay<-12>, Vay<2>, Vay<-6>, Vay<15>>;

/**** Result ****/
using Result = Metafunction
<Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);