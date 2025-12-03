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
    using type_signature = Ret(Args...);
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...) const>
{
    using type_signature = Ret(Args...);
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
struct AreSameTypeSignatureAs
{
    template<typename...Unknowns>
    struct ProtoMold
    {
        static constexpr bool value
        {
            (...&&(
                std::is_same_v
                <
                    typename Analyzer<Unknowns>::type_signature,
                    typename Analyzer<Known>::type_signature
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
inline int different_fun(int, int*, int**){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
};

/**** Metafunction ****/
using Metafunction = AreSameTypeSignatureAs<int(int, int*)>;

/**** Tests ****/
static_assert(Metafunction::Mold_v<decltype(fun)>);
static_assert(Metafunction::Mold_v<decltype(FunAddr)>);
static_assert(Metafunction::Mold_v<AbominableFun>);
static_assert(Metafunction::Mold_v<decltype(&Tester::fun)>);
static_assert(Metafunction::Mold_v<FO>);
static_assert
(
    Metafunction::Mold_v
    <
        decltype(fun),
        decltype(FunAddr),
        FO
    >
);
static_assert
(
    ! Metafunction::Mold_v
    <
        decltype(different_fun),
        decltype(fun),
        decltype(FunAddr),
        FO
    >
);