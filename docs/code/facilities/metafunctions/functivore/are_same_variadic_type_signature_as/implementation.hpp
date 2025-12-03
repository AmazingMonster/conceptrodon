/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>

/**** Analyzer ****/
template <typename>
struct AnalyzerPrototype {};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...)>
{
    using variadic_type_signature = Ret(Args...);
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args..., ...)>
{
    using variadic_type_signature = Ret(Args..., ...);
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...) const>
{
    using variadic_type_signature = Ret(Args...);
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args..., ...) const>
{
    using variadic_type_signature = Ret(Args..., ...);
};

template<typename Fn>
struct Analyzer: public AnalyzerPrototype<Fn> {};

template<typename Fn>
struct Analyzer<Fn*>
: public AnalyzerPrototype<Fn> {};

template<typename MemFn, typename Structure>
struct Analyzer<MemFn Structure::*>
: public AnalyzerPrototype<MemFn> {};

template<typename FO>
requires requires {&FO::operator();}
struct Analyzer<FO>
: public Analyzer<decltype(&FO::operator())> {};

/************************/
/**** Implementation ****/
/************************/

template <typename Known>
struct AreSameVariadicTypeSignatureAs
{
    template<typename...Unknowns>
    struct ProtoMold
    {
        static constexpr bool value
        {
            (...&&(
                std::is_same_v
                <
                    typename Analyzer<Unknowns>::variadic_type_signature,
                    typename Analyzer<Known>::variadic_type_signature
                >
            ))
        };
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;

    template<typename...Unknowns>
    static constexpr bool Mold_v = Mold<Unknowns...>::value;
};

/*****************/
/**** Example ****/
/*****************/

/**** functions ****/
inline int fun(int, int*){ return 0; }
inline int variadic_fun(int, int*...){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;
using VariadicAbominableFun = int(int, int*...) const;

/**** function pointers ****/
inline auto FunAddr { &fun };
inline auto VariadicFunAddr { &variadic_fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
    inline int variadic_fun(int, int*...) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
};

struct VariadicFO
{
    int operator()(int, int*...) const { return 0; }
};

/**** Metafunction ****/
using Metafunction_0 = AreSameVariadicTypeSignatureAs<int(int, int*)>;
using Metafunction_1 = AreSameVariadicTypeSignatureAs<int(int, int*...)>;

/**** Tests ****/
static_assert(Metafunction_0::Mold_v<decltype(fun)>);
static_assert(Metafunction_0::Mold_v<decltype(FunAddr)>);
static_assert(Metafunction_0::Mold_v<AbominableFun>);
static_assert(Metafunction_0::Mold_v<decltype(&Tester::fun)>);
static_assert(Metafunction_0::Mold_v<FO>);
static_assert(! Metafunction_0::Mold_v<VariadicFO>);
static_assert
(
    Metafunction_0::Mold_v
    <
        decltype(fun),
        decltype(FunAddr),
        AbominableFun,
        decltype(&Tester::fun)
    >
);
static_assert
(
    ! Metafunction_0::Mold_v
    <
        decltype(variadic_fun),
        decltype(fun),
        decltype(FunAddr),
        AbominableFun,
        decltype(&Tester::fun)
    >
);

static_assert(Metafunction_1::Mold_v<decltype(variadic_fun)>);
static_assert(Metafunction_1::Mold_v<decltype(VariadicFunAddr)>);
static_assert(Metafunction_1::Mold_v<VariadicAbominableFun>);
static_assert(Metafunction_1::Mold_v<decltype(&Tester::variadic_fun)>);
static_assert(Metafunction_1::Mold_v<VariadicFO>);
static_assert(! Metafunction_1::Mold_v<FO>);