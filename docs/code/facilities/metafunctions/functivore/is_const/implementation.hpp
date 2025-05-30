/**********************/
/**** Dependencies ****/
/**********************/

#include <cstdint>

/**** Analyzer ****/
template <typename>
struct AnalyzerPrototype {};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...)>
{
    static constexpr std::uint32_t value {1 << 3};
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...) const>
{
    static constexpr std::uint32_t value {1 << 6 | 1 << 3};
};

template<typename Fn>
struct Analyzer: public AnalyzerPrototype<Fn> {};

template<typename Fn>
struct Analyzer<Fn*>
: public AnalyzerPrototype<Fn>
{
    static constexpr std::uint32_t value
    {
        1 << 2 |
        (
            1 << 3 ^
            AnalyzerPrototype<Fn>::value
        )
    };
};

template<typename MemFn, typename Structure>
struct Analyzer<MemFn Structure::*>
: public AnalyzerPrototype<MemFn>
{
    static constexpr std::uint32_t value
    {
        1 << 1 |
        (
            1 << 3 ^
            AnalyzerPrototype<MemFn>::value
        )
    };

    using class_type = Structure;
};

template<typename FO>
requires requires {&FO::operator();}
struct Analyzer<FO>
: public Analyzer<decltype(&FO::operator())>
{
    static constexpr std::uint32_t value
    {
        1 |
        (
            1 << 1 ^
            Analyzer<decltype(&FO::operator())>::value
        )
    };

    using class_type = FO;
};

/************************/
/**** Implementation ****/
/************************/

template <typename F>
struct IsConst
{
    static constexpr bool value
    { static_cast<bool>((1 << 6) & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsConst_v
{ static_cast<bool>((1 << 6) & Analyzer<F>::value) };

/*****************/
/**** Example ****/
/*****************/

/**** functions ****/
inline int fun(int, int*){ return 0; }

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

/**** Tests ****/
static_assert(! IsConst<decltype(fun)>::value);
static_assert(IsConst<AbominableFun>::value);
static_assert(! IsConst<decltype(FunAddr)>::value);
static_assert(IsConst<decltype(&Tester::fun)>::value);
static_assert(IsConst<FO>::value);
