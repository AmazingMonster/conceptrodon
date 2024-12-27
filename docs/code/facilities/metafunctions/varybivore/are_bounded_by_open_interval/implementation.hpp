/************************/
/**** Implementation ****/
/************************/

template<auto Lower, auto Upper>
struct AreBoundedByOpenInterval
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(Lower < Variables && Variables < Upper)) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(Lower < Variables && Variables < Upper)) };
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
// Create a open interval (1, 4).
template<auto...Args>
using Metafunction
= AreBoundedByOpenInterval<1, 4>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<2, 3>::value);
static_assert(! Metafunction<1, 2, 3>::value);
static_assert(! Metafunction<2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3, 4>::value);
static_assert(! Metafunction<2, 3, -1>::value);