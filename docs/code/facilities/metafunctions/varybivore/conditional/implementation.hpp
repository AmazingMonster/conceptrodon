/************************/
/**** Implementation ****/
/************************/

template<auto IfTrue, auto IfFalse>
struct Conditional
{
    template<auto>
    struct Detail {};

    template<auto I>
    requires I
    struct Detail <I>
    { static constexpr auto value {IfTrue}; };

    template<auto I>
    requires (!I)
    struct Detail <I>
    { static constexpr auto value {IfFalse}; };

    /**** Page ****/
    template<auto...Agreements>
    using Page = Detail<(...&&static_cast<bool>(Agreements))>;

    template<auto...Args>
    static constexpr auto Page_v {Detail<(...&&static_cast<bool>(Args))>::value};

    /**** Mold ****/
    template<typename...Elements>
    using Mold = Detail<(...&&static_cast<bool>(Elements::value))>;

    template<typename...Elements>
    static constexpr auto Mold_v { Detail<(...&&static_cast<bool>(Elements::value))>::value };

    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        
        template<typename...Elements>
        using Mold = Detail<(...&&static_cast<bool>(Predicates<Elements...>::value))>;

        template<typename...Elements>
        static constexpr auto Mold_v 
        { Detail<(...&&static_cast<bool>(Predicates<Elements...>::value))>::value };
    };

    /**** Road ****/
    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;
    
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Detail<(...&&static_cast<bool>(Predicates<Variables...>::value))>;
            
        template<auto...Variables>
        static constexpr auto Page_v 
        { Detail<(...&&static_cast<bool>(Predicates<Variables...>::value))>::value };
    };
    
    /**** Rail ****/
    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};

/***********************/
/**** First Example ****/
/***********************/

/**** Select ****/
using Select = Conditional<1, 0>;

/**** Test ****/
static_assert(Select::Page<1, 2>::value == 1);
static_assert(Select::Page<0, 2>::value == 0);

/************************/
/**** Second Example ****/
/************************/

#include <type_traits>

static_assert(
    Select::Mold
    <
        std::integral_constant<int, 1>, 
        std::integral_constant<int, 2>
    >::value == 1
);

static_assert(
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 2>
    >::value == 0
);

/***********************/
/**** Third Example ****/
/***********************/

/**** VoidInt ****/
struct VoidInt;

/**** VoidTester ****/
template<typename...>
struct VoidTester: public std::false_type {};

template<>
struct VoidTester<void>: public std::true_type {};

template<>
struct VoidTester<VoidInt>: public std::true_type {};

/**** IntTester ****/
template<typename...>
struct IntTester: public std::false_type {};

template<>
struct IntTester<int>: public std::true_type {};

template<>
struct IntTester<VoidInt>: public std::true_type {};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Select
::Road<VoidTester, IntTester>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int>::value == 0);
static_assert(Metafunction<void>::value == 0);
static_assert(Metafunction<VoidInt>::value == 1);
static_assert(Select::Road<>::Mold<>::value == 1);

/************************/
/**** Fourth Example ****/
/************************/

/**** NonpositiveTester ****/
template<auto...>
struct NonpositiveTester: public std::false_type {};

template<auto I>
requires (I <= 0 )
struct NonpositiveTester<I>: public std::true_type {};

template<auto...>
struct NonnegativeTester: public std::false_type {};

template<auto I>
requires (0 <= I)
struct NonnegativeTester<I>: public std::true_type {};

/**** Metafunction ****/
template<auto...Args>
using Metafunction_1 = Select
::Rail<NonpositiveTester, NonnegativeTester>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction_1<-1>::value == 0);
static_assert(Metafunction_1<1>::value == 0);
static_assert(Metafunction_1<0>::value == 1);
static_assert(Select::Rail<>::Page<>::value == 1);