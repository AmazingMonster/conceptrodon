<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Sequnivore::KindredRepack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#sequnivore-kindred-repack">To Index</a></p>

## Description

`Sequnivore::KindredRepack` accepts a list of packed sequences and returns a function.
When invoked by an operation, the function concatenates the packed sequences and instantiates the operation with the result.

<pre><code>   Seq<sub><i>0</i></sub>&lt;Vs<sub><i>0</i></sub>...&gt;, Seq<sub><i>1</i></sub>&lt;Vs<sub><i>1</i></sub>...&gt;, ..., Seq<sub><i>n</i></sub>&lt;Vs<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

`Sequnivore::KindredRepack` can also handle `std::integer_sequence`. The function first `static_cast` integers to `std::make_signed_t<size_t>`. Then, it uses the result to invoke an operation.

<pre><code>   Seq<sub><i>0</i></sub>&lt;Type<sub>0</sub>, Vs<sub><i>0</i></sub>...&gt;, Seq<sub><i>1</i></sub>&lt;Type<sub>1</sub>, Vs<sub><i>1</i></sub>...&gt;, ..., Seq<sub><i>n</i></sub>&lt;Type<sub>n</sub>, Vs<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredRepack
 :: typename...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<typename...>
struct KindredRepack
{
    template<template<auto...> class>
    alias Rail = RESULT;
};
```

## Examples

Here, we first concatenate `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>`. Then we pack the result into `Sequence`:

```C++
/**** New Vessel ****/
template<std::make_signed_t<std::size_t>...Args>
requires (sizeof...(Args) == 4)
struct Sequence;

/**** SupposedResult ****/
using SupposedResult = Sequence<0, 1, 2, 3>;

/**** Result ****/
using Result = KindredRepack
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::Road<Sequence>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Sequnivore::KindredRepack` is implemented similarly to [`Sequnivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Shuttle` or `std::integer_sequence<std::make_signed_t<size_t>, *>`.
After all variables are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<auto...>
struct Shuttle;

template<typename...>
struct KindredRepack {};

// Base Case:

template<template<auto...> class Sequence, auto...Variables>
struct KindredRepack<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
struct KindredRepack<Sequence<Type, Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation
        <static_cast<std::make_signed_t<size_t>>(Variables)...>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

// Recursive Case:

template
<
    template<auto...> class SequenceA,
    template<auto...> class SequenceB,
    auto...VariableAs, 
    auto...VariableBs,
    typename...Others
>
struct KindredRepack<SequenceA<VariableAs...>, SequenceB<VariableBs...>, Others...>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            Shuttle<VariableAs..., VariableBs...>,
            Others...
        >::template Road<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

template
<
    template<typename, auto...> class SequenceA,
    template<typename, auto...> class SequenceB,
    typename TA,
    typename TB,
    auto...VariableAs, 
    auto...VariableBs,
    typename...Others
>
struct KindredRepack<SequenceA<TA, VariableAs...>, SequenceB<TB, VariableBs...>, Others...>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = KindredRepack
        <
            std::integer_sequence
            <
                std::make_signed_t<std::size_t>,
                static_cast<std::make_signed_t<std::size_t>>(VariableAs)...,
                static_cast<std::make_signed_t<std::size_t>>(VariableBs)...
            >,
            Others...
        >::template Road<Operation>;
    };

    template<template<auto...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBJmAJykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdGxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpiJrozIeJgKF7tHp%2BcHX3vvJ8d/ZgAzMFkN4sBcTIC3MhhugsFRIdh/uZgQxQV5wZC3F5HLRCABPRHIj67C5CBA4gj0V47X4ETAsRIGelYpg41AAOi5RNOw2IXgcZIpBCpmEhVlO/0%2B3xl21%2B0ouAElGfQ2IImDUaXKpbLdYdiWdSQBpYLoYiYdAAJVuTGQAGstfrTvSVRqxVCCPi7sw2FyOTyTnyBQQLiaGGaLdbEraHSYAOxWONXcUG9brC4WJhKC5uLPsA0uplurGF5nu3Psv2Ii6grMvISYACOXgemFIFzZRD9ADUGngmBF6AoA0HBWGI1abfasQ3m62sb3iP3B88q4CkevkQn/hddxdS8WPQyiyyoZ3Odz1zWDAoXgB5O7EDXpAN7i6jkM3ep0Hd7%2BMSk43zfLxUiMfcvUwCFASuC4H2iZ8BAXPsByHNcNwAt942TQEAN/XcD1PNwCPLc80OvOs/ROYBzQZRgCGHTdTmA0DgAuS1UCYdAoJgr8mB/KEqJotV6LQkAQE9O4U0lJMpL%2BZ1jzLEsFMPIiIJ9NsO0rS9sHI28ySbFs0Q0iTGFYSCABUIPbUiuUXZchxHAh%2BTHU1zUnaNpyhWdDNWLFLLuds7JQ1dtIDf88P3ZTCOI1ktP9K9az0uCnxqV89w/a5MG/WgIvCpigN3EDglYkzuNgx8EIYCLMKhSZHGQAB9URhixWExJYJg7UwBrUmAEJ0AaghWrwAAvbqhs3dcICClcFDmNDZMwmScINN8YqPV1CJs%2BKdMShRKOozBaMEBikXywqWLYjiuMhHisr4nKBMO46RO0sSTNkrDPo%2BdNrWQZZUgAN0g3MlBAAsorFSUoQi9aKy7bTdPrAzWxOUhYch2KEZ2pH9LnIybAi7aZvoQN2yJuKScwCwFHR87wO9My/TvAgEGiYdobOwMnODUNXMjKc7RnFGjL%2BKEqcDND2281srHF5CVxpqXYNZ9mFukjC9zhuHturPbyvg1LGMA9KecFXif3pvKTYKoqwNK26%2BfDNyoxjaq/xh%2BmCt3clKXoJCl2CyWuUChX6CV7S6Zt73dxZtniH27kvY97B3shq7OKxZLKqJFareW3D6e1zGzzivWb0TjlBKO4TToiu3WPYziyotx63Grl7K8Rd6IM%2BguIc2qGxbcDHB5LNSzOssuEorvGfMwNHR5PcsTPUqfsfLus59lqO1ontgLnMxei/3izCfp4mw4X2mIQvymr5p3etdP5nVYT5FjYy8cXcF4X8dWYeR9Q6BxXMHHa0sRarDlm4cyNgLhUwjuAlW8cu7G2tmtEuRFMG6xnlvbORsuZvgyq3XK25k4XWKgzSCjtv4Cw8kLchUER6MKIQQdAYlgj0mANEHqkCh4xxqsw6OAjTbsJAB1LqPU8B9QtINVqbCxKpDGnI9cT8RGsOfI1ZqE03BtXEZ1bqvV%2BoqN0QokASjxq52wNNK%2BgZ5oh3diIuqeAtFZh0XoiRhjpHGPcWYixKiNzWIQXNKsLCU5qIEXHNWSdhEpzToPDO6As4VQIYtP8/dJRF0wTraeu0K4HSEnROu9MG6JJbvdfi7dnq11EuJXuec/gZLkoaPUtIdSXGwKoVgTJIJvHaa0p0zSFShEwAAd3gc8Owjo6SYI8QYqRMiBq%2BLEf4ia2BKLEGAMUk45pmx4HNC8CAFjUBUD9BAHZWy5jcUdpIOY/wMoyyMt9Fp2wyReESLkAWCgvC0BDH004pShDvM%2BZOb5vyyqPN8lCDQ7Y2gXDMO2QEudC4vM2GxZ4Py/ltIBZda0YKQw0P5u5N20MhGsLEZwzA3DiC8P/uWTh7YNCInJvTPRppMCqFpfPLEcKzDMoimy8MHKuXzihEitB64xJNySV5PhyLUyknMs8LF2peT1Hqg1Os0QCBHL8WZTVDE3B4sxdLYFKQvmYsRHchp/wOALFoJwAArLwPwHAtCkFQJwEelhrDviWCsahQIeCkAIJoO1Cw7QgEdZIDkGgAAcZh4hxC4I6%2BNcauBxjjNIB1HBJC8BYBIDQMLXXus9RwXgCgQAwtDW6u1pA4CwBgIgEASwCCJBxOQSgaBGR0GiKEMynBVBxoAGwAFph2SAuMAZAyALhSA5GYXgFpCAkDwOwto/BBAiDEOwKQMhBCKBUOoWtpBdBtFGU%2BRInAeD2qdS6sNHrOB3hxO2kMJyLhDrHROqdM650xrMBcCAHge30GIBCINcxeA1q0AsCASBu2JF7WQCgEAENIZAMAKQCKaC/PZpQCID6IjBAaPia9vAiPMGIPiO8ERtCYAcGR0g3bhJ3gYLQUjJ6sARC8MAXMtBaCVu4LwLAHUjDiE4/s%2BjjhgaCfdRy%2BjOI1jBspTm91eIIhPiox4LAD6nJ4ALUJ0gwNiARHNTcUTwA8RGDDQsKgBgtndieKMuCrrg2buEKIcQe73OHrUA%2Bs9%2BhDDGGsNYfQeAIiVsgAsVAiQaiCdHbCW6pgfWWDMKW4zS4sCRYgAsOwUn0guHDGMVopBAjBD6CUAYbRchpAEMVnIKRasMGmP0Mo7R8sCC6KMTwLQ9B5YcJ0EYPRyszCq7YIb9WJhDZa5VsouX/WrAkLejgzrSAlt4GWj9I7x2TunbO%2BdAGIC4BXWBlEXBIMhpswsNmnEBg5dIJGyQgIORxEBFmjQkgzCSGHUWx1w6Eg5rzaQAtgIuAcmHVwYdca4jpuHdGlNr3h1rYfWWitVbLu1tg02uDLaX0dpQ2h0D/a2CcAaCwQGcZR1MHImBLgcQORg7k/gIgmW9Due3V56QPmlB%2BZPboBFF6mBXqE8t1b63H0cGfW2nEFx32fp2zT1idOGexsA8BxDoHwOAjMBd6DdaceE%2BiJ21DqAQMDFrEYOnXAYU4fpAnfDhHiNUcYxRkjNG6MMcM8xuirH2MPq4zxvjAnGMiaC%2BJ91%2BBzQDZkw%2B%2BT/16SMZUw%2B9Tmn8TabWO6vTBng3GdM0oczYfio2b4PZhQjmxkucY%2Bzzzu6ueyF88e91/PAvWeS1YSwYWIvwGi7F9I8XEvQTb9YNLG2MtrueN39rA3nAQFcJN0r4YZuzGq41mo8%2Bas1CX2N/rNQutNB6%2BMKfu/psjda31ibB%2BSuTEaFvubixliLfO/oO9yOT2bfl9%2Bi3Sv6eM8A8dlnWu52UGV2pAN2WAMQ92gO%2BaIAgI9OH2cYjqcQmagIn232kgbQ4uqOtg6OeuWO8AOOrar6xuhuxAxOawZO36LACggMs6gMyuZYwwS6zOq666%2B6HmO6EgdeB6POjeOgMBpAguwuN6z%2BK296b%2BT6eOb6VAH6lB1BtB9BbowwaupuGu0QWugIuuxeBuKhSGxBOhoGIANBHyDUdBcQDUDBBADUqgE6fAdAdulaEABGJ6ruzuhmLh1GtGUmjG3uggvuHGEemA3GvGYgwehmoeYmGewmkm0eE%2BJ6ceimieggVQye4Wqe6eumS42evAueZmDIhe1mmOJeTADmTmlehm1eHB3m9ePB/m/BBgreIWHe6m2WPecWnA6wbUQ%2BqW6W0QmWE%2BUWR%2BBWs%2BRWl%2B/gi%2Bp%2Bs2DWeQ6Q6%2Bq%2B6Qt%2BfWVQHWtQF%2BWQV%2BSx0%2BKxUwExy%2B423Q8%2B1%2Bw2RQZ%2BT%2BCgC2u6ouYhpanAMhk6VBNBFwphHIFhf%2BzBp2EGwBmO12mAt2EBy2QOBa8QHIgIgIjqqa6BRaIJcYUOr%2B1x5a2B1aIBj2jqL2GacYRacakgyaXACaZgSOOagIVxG2nAnxMGy2i6sJxJ8JuBCwxmqQzgkgQAA%3D%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/descend/sequnivore/kindred_repack.hpp)
- [unit test](../../../../tests/unit/metafunctions/sequnivore/kindred_repack.test.hpp)
