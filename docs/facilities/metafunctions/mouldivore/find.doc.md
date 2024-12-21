<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Find`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-find">To Index</a></p>

## Description

`Mouldivore::Find` accepts a list of predicates and returns a function.
When invoked, the function returns the index of the first argument that satisfies all predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
Find ::   template<typename...> class...
       -> typename...
       -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct Find
{
    template<typename...>
    alias Mold
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };

    template<typename...>
    static constexpr std::make_signed_t<size_t> Mold_v
    {RESULT};
};
```

## Examples

We will find the indices of `int**` in list `int, int*, int**, int***` and `int, int*, int***`.

```C++
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

template<typename...Args>
using Metafunction = Find<IsIntDoubleStar>
::Mold<Args...>;

static_assert(Metafunction<int, int*, int**, int***>::value == 2);
static_assert(Metafunction<int, int*, int***>::value == -1);
```

## Implementation

`Mouldivore::Find` is implemented based on `Typelivore::KindredFind`. It changes the invocation order of the latter.

```C++
template<template<typename...> class Predicate>
struct Find
{
    template<typename...Elements>
    using Mold = KindredFind<Elements...>
    ::template Road<Predicate>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAAHNIADqgKhE4MHt6%2BAaSp6Y4CoeFRLLHxSbaY9kUMQgRMxATZPn6BdpgOmQ1NBCWRMXGJ0gqNza25HeP9YYPlw0kAlLaoXsTI7Bzm/mHI3lgA1Cb%2Bbl6OtIQAnifYJhoAgjt7B5jHp8hj6FhUt/dPjwImBYyQMQJObgIV2SjFYmAAdIi/o8xsQvA5DgBpMLoYiYdAAMRx/xMAHYrI9DlTDkCQWDMBDaaCmODTlCYcw2Ij4bdDvsmAoFNzlHj8KIgQpkQ9qYdUeiCIcRagiAAlVBMdD/GVkiyyxqOZB8gRjTCqZLEQ5Mc6oQ4ANzEXjeOoAtFwyQARE66j1ekmU6lM%2BmM4HM1mQ6GwrlI/zYPkGQXch7APHAxgESUxrXUrzpIyHNUa97uxXEZWoAua05JlNsQRC6N3fwUp6kz1Nv0PQMshlsiOct5E4hjKVyjHYhi4/FEicQwfDzOPHVZqldsOrnvhjlw7m8/kJxEi/F4cWYDN3f1U0cKpWq9Wai/HcnU5cyvUs49Ghgms0Wq1EO0Ok6D7auSL6vs%2BACsVgQe6EBLIczq8l8IAgCwTAANaYAA%2BukwDhOgWEEBC6QAF7YURC7SuBr5LsB1EyngVCft%2B5qHFAO5mAAbOYnGHmK3YZm4c4UdgKH2t4mBLEsYH0c%2BT54gQ6wMIcGheo%2BnqLnRsmHDUSgydpOqHApSkIW6TbqfpNGtnBlk%2Bu2D52c2L7rsGdLdoyfbbg2cYCvW8LVpgqZ1lKMo5mEwD5neRYlmWFYQgFQXpjumb2S2bZOYCIZBr2W5sIcwmkDSnl5UIXQCOghXspGCKIgA8gQCBxGe/xXliOKitOlZCXgQ4EIVpVoBOhX1Y1Q7JeeLbNjKLlsll7k5dV40%2Bfu8J8ceAkhdSrU3uWd4voZVKWWM76GoNLG/taAESccWmPlN2nHFBJgwXBCFIQQ6AoWhmE4XgeH4oRxF4GRgOUQ9d2WfRjHMUCP6Q9R7FIlxPFrSegnCbcYmAVJ8PgYZxnEMpqnmT6mlUeDVK6W80NnbD5q46%2BiM8sjXGoxtpwDeVmMgOJjo47d9H45gimE4cZneq2HYU9SVOHDTxp08QDMyhAyvUeOk6EsSpwjU141q%2BBKHrjFt4ahCbMSvrAsPVj11gGAJzFq6BuHNJ1t40%2BLsygTylmMclhtROHXa24utjQ2XvUkbc1Aibu1m6cFunlb5PS1HPOAWpLukwCqfg1T2fycLJnOyTkvu%2BpNm3Y5%2B2S6lzkxxuM2bot3l7n5CW1umm1UmFeYVtFO1xVWyaBV3fl/PXdcZZ2jeuaGTfFTVPIxstCglkeJ4jgQaIYp1JKgQ%2BzdVf23LYPQ4894cfcRQAsp46DRRrwczqc5%2BJRPYPp8bw9uEnk9OWnh2AA9AAKnARAyBUDgH/DARAw4AAVU86ZDiQJgY8OBUCsHgPQbnZ4DB9heCOBCc4dBrhSn%2BMfJehx35d23rvBUABJBQjDBDujWNEegvQlaPBAIcZIXhOEfmQiAPACgcJwghLQtMhUwgEHAbyJcQCyZUNysvB4xBgDNUeDfQ4t9hZMCoF4AhdRor71OMw1hBB2GCK4eMKUKF760C6horR%2Bt64on1MeLCvk4gEAgPoxoRiTGZAhHI2RghQERPkVEuWkSFExlto6IsjtDhmGkqlY6BofGCj8QEgxwTugCDCYIaJsS5EQO5rzJ0/g2xOy4BkiwHAVi0E4BBXgfgOBaFIKgTgbhrDWFlGsDYTozD%2BB4KQAgmhmkrHQiACCpJ4T%2BASJxUk/hVkaGWWsgAnIEVpHBJC8BYBIDQGhSCdO6b0jgvAFAgDOVMrpzTSBwFgDARAIA1gEAEX1CgEA0AgjoHECIcJOCqBWc6TikhDjAGQIaKQ8IzC8CPEQYgeBPpcBkIIEQYh2BSExfIJQahpmkF0BigA7sQJgyROA8BaW0jpxKrm1XON8w4qAmJgs4hCqFMK4WSARWxDwAL6AWh2A03gDytArAgEgf5yRAVkF%2BXKhVIBgBSDMHwOgQIhyUGiMS6IYQmhXBpbwA1zBiBXFqtEbQXQHkTP%2BV3WqDBaDGseaQLA0QvDADcGIWgtzuC8CwGhIw4g3X4DxN0W0p5iWmi6OcLYEy5E1GJZcaIlKLUeCwMSneeBjkBtIFG4g0Q0iYHdMCQwwBLhGGmSsKgBgtEADU8CYDJbVDkJr8XYvEHi/gghFAqHUG60l%2BgK0oAGZYfQeBoi3MgCsVAyQ6j%2BudF8R2phLDWDMJcwtqKsAzrgtUWomQXATkmH4DFIQ5hlAqHoAoGQBCnpvWkO9DABhXuGBizoRT6gzAfR%2BmotqegzFfUMeIH6f2eDaHoY6zRgMLFAysBQwzNgSDpRwdp5zGWcEOJy7l0LYVi35X7CAuBCAkH9uMpYEqa0rEahqYY%2B65mSH8PCXZpJJAaEkGYSQnFTkQU4ts/QnBDmkGOeM%2BEnEuCcQSNshIkmIKSC4BBXZnEMNuquTcu5kya3PLeTKj5LLzjkEoMqkVwK2CcCaCwW0pJnRMB8nmLg2z4RcHhN05FJA0V6F7cIUQ3bpDef7USodIANUUqpSa1D6GLm8CZQZhU7LLTECszZuz/IHNOZcxoQVqBhVxHI%2BkqjjzpWypy/KkVRm/mlZVZZ6zzo0tqu2VwM5NBaDatuRAPVbqzVGo7d1i1VqbUOA7Q6tMTqXXEo9V6n1tA/UdqDRW0N3Tw0Aajf6tzqg41Ag7Um/Z3TU3pquJmrY3Sc15omYW4tSgy3BsreFbTdamCNuba29t%2BbvNdtxf52QgXB3dN0Bqgw1a11WAnamvdc6F2ZCXSu2pwON1briDu6Ns6D0AecBAVwv6ggTlg9ejFt66hY4J5kXH77Udfu4S0CDuQ/2HoEJT0noHbDgZyGe5nfRGcodWOsZDDTBNoYZWprDNWUv2Yio55zrm2IkZReR8VWmis0cwHR%2BI%2B79nCdE05jjpIlOkjWZx7jCnVOXM4Bp%2B52mXnvM%2Bd8irJmgUgo4JZyFhwWAKFtIaW0Ev6RjCRfgFFnmMXvd859/FP3iW6ECGF6lAbIuC5NxwZlXzzhsqYk7qFrv3d2i9wJBUEAhVlbyzsfwlGFdSueSV3LirjNVZFTzZAyRkhYU99srC3uCA%2BKS5CzVrWmq6v1Yai1vWB%2BWutba4bOXHXOtdUtzAnrvW%2Bv9RM%2BbIbjuBp6it6NbrY3IHjdtwQya3X7aNUd7NqKzu8AuyW67C27tFb4PWhQTaW1tsYB2oPOKJBfb7YS37Og8iA%2BMHHRsDB3gAh0XU4GAWQjh0sE3Ri23TRWR33U/TqGPXcGpzZwvVKBA0fUKEyCJyfTqE51pzR2/T6Cx2QMAw50vWwLAzIPQKgyA2oLgy50Qx51xVj2Nxi2F073Tzdw92zwlFzxlzIzFRL0lRmVIFoywFV1Qw1xCyc38H8Agggg4ya02X8FJCk04J6VN1sE03EKklIEYzMHEy4H8C4nMO2Qky4g0FJH538Djy4OuVLwkP2URW0PUxcMMMLXSGcEkCAA%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/find.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/find.test.hpp)
