/************************/
/**** Implementation ****/
/************************/

template<auto Target>
struct AreEqualTo
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < Target) && not (Target < Variables))) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
    
    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Variables < Target) && not (Target < Variables))) };
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
template<auto...Args>
using Metafunction
= AreEqualTo<1>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<1, 1.0>::value);
static_assert(! Metafunction<1, 2, 3>::value);