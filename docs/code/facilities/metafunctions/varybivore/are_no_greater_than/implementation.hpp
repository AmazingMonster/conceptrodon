/************************/
/**** Implementation ****/
/************************/

template<auto Target>
struct AreNoGreaterThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Target < Variables))) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Target < Variables))) };
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
template<auto...Args>
using Metafunction
= AreNoGreaterThan<5>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<2, 3, 4, 5>::value);
static_assert(! Metafunction<6, 2, 3>::value);