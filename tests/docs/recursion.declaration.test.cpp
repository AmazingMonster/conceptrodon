
template<auto>
struct Decl;

template<auto I>
struct Tester { using type = Tester<I>; };

template<auto I>
struct Tester1 { using type = Tester1<I + 1>; };

template<auto I>
struct Tester2 { using type = Decl<I + 1>; };

template<auto I>
struct Tester3 
{ 
    template<auto...> 
    struct ProtoPage
    { using type = Tester3<I + 1>::template ProtoPage<>::type; };

    template<typename...> 
    struct ProtoMold
    { using type = Tester3<I + 1>::template Mold<>::type; };
};

template<typename Element>
struct Tester4
{ 
    template<auto...> 
    struct ProtoPage
    { using type = typename Element::type; };
};

template<typename Element>
struct Tester5
{
    template<typename...>
    using Mold = Element::type;
};

template<size_t I>
constexpr size_t Tester6 = Tester6<I - 1> + 1;

template<>
constexpr size_t Tester6<0> = 0;

// template<typename>
// struct Tester7
// {
//     using type = Tester7::type;
// };

// template<typename...>
// struct Tester8
// {
//     template<typename...>
//     using Mold = Tester8<>::Mold<>;
// };

// template<typename...>
// struct Tester9: Decl<0>
// {};

template<template<auto...> class...>
struct HoldDecl {};

template<typename...>
struct Tester10: HoldDecl<Decl>
{};