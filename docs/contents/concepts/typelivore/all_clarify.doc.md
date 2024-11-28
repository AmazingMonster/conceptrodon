<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `AllClarify`

## Description

`Typelivore::AllClarify` accepts a callable type predicate and a list of variables.
It returns true if the predicate evaluates to `true` for every variable and returns false if otherwise.

<pre><code>   Predicate, Variables...
-> (...&&Predicate{}(Variables))</code></pre>

## Structure

```C++
template<typename, auto...>
concept AllClarify = REQUIREMENT;
```

## Examples

`AllClarify` turns a fold expression of a callable type predicate over `&&` into a concept so that it can be used for subsumption.

The following code will fail since `(...&&Pred_0{}(*))` and `(...&&Pred_0{}(*)) && (...&&Pred_1{}(*))` are both atomic:

```C++
using Pred_0 = decltype([](auto...){return true;});

using Pred_1 = decltype([](auto...){return true;});

template<auto...Args>
requires (...&&Pred_0{}(Args))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&Pred_0{}(Args)) && (...&&Pred_1{}(Args))
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSAMykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHF4ZRgDUysSY6AD6GgcmiQAiB1jItAQAnimYECYBVgE3EExeRAAdMCViYAOwWE4ETYMA4EYheTDXKxgm6gxJWDQAQRM2L24WARxO5y4V1u9zqT1e70%2B31%2B/yBIPBkMw0OIsPhiOR4LR3OxuKxBEwLBSBiF1zcDNQwMBWOIwAU12wApOAEcvHgTgoDhAZeYAGwG46nC7MnkQOUKlag7FoBizTCqFLEA4xVCeA5ULwMCCgiFQmGesRKbmogUCoUisVIxKSgHS4GWxWJZXYtUarU6vVmQ0543nDRm1EW%2BUKa1XHMGrPAg1G4lnLhF35J60Cu0Op0ut0er0%2Bv0stkchExlE3cPY2ZMRzIM5MBRKFrUb0Sxsp33oiwcNa0TgBXh%2BDhaUioThuazWA4KDZbTAVxI8UgETRbtYAaxAAX1gIAHPqpAEwX1SQAE5EkAsxkh3DhJF4FgJA0DRSAPI8Tw4XgFBARCn0PLdSDgWAYEQEANgIFIAXISg0BFOh4kiVgdlUX8AFogIOYBkGQA4pEBMxeFOQgSDwdA9H4QQRDEdgpBkQRFBUdQcNIXQuFIAB3YgmBSTgeG3Xd92fY9OAAeQBMiCAOVAqAORj9RYyQ2I4rjJB4nUPGo%2BgXXMe8Vl4bCtDWCAkColIaLICgICCkKQGAKQzD4OghWIDCIBifSYnCZpni03g0uYYhnkMmJtDqbCHyothBEMhhaEyhSsBiLxgElWhaAw7heCwFhDGAcRas1Yq8AAN0wVqj0dOoAR2B9wiFKCj1oPAYnUvKPCwfT4TwOC2tIIbiDdJQbmFLr5qMZ81ioAwFQANTwTAVMMt4DwfUThFEcQpOe2S1H0pT9C6lBz0sfQFowyA1lQFJelapjZnQa4blMSxrDMFCduIIThvgNZanqZwIFcKY/GU0IFnKSo9EKTIBAJ8n0kphghlJ5Yuh6Bo5mp5Tsd6foWgZkYqnGAZ2YFnmSb5iQsevbZxf0XSkP01CrOY1j2M47izB1XABI8iCuG8x9TrWBBMCYLAEl9Uh30kRJAVAsFJA0SQzEkfUEM/YCZeg2CQHvQE/31b9gO/Lh9QCSQuACUD9TlhTUPQzD9Zw/zCIC4iTPIsKIvcui2E4ZoWAGsEmKYA5Hi6rjgMBLhAVG/AiDR4TlOe8S3ukD6lC%2BhTdFitSNKynSOD3aOUKMtOzIsg484LouS4MQ4uArqvLggVzgvcu8zD13zcJTzP4go8LUDc0ZJ8L0ujHnrhEJoJ54iSlKFJyjKstIR%2B8oKoqHGfsrGAISrqv0uqDUmotWfh1I6Owjz4BOPUIaI0%2BKqHGkKZ%2B01uj6XmotDKK0IE%2BTRptB8O09qYAOp1Iwx1QCJz4BdBQ11br3UYM/Jur1JKt1kJ9eSR4u6/ROgjKwgN0Eg3NuDSGnBoYEFhrcHhSMUbxHrhjUGzN%2Bq43xp4doehiZlDFspCmvQhbaKyLzJY/NOas0FiovIHNuiKL6HMAxZMOZszMYTYW8wNGGOlleTYUtdYe0HshXgCsT7TzPoSeeldq4a1riQO8usfIG1IEbE2oxzZQRgqQOCiQK4OzBBHMEYJEiO2dmHIe/jOBxywqdPCyckAkVMvvXexBs47DzqxFgCgBqcQGqE6Msw%2BKRPriJWQzdmHSXkO3dhOhvaqXUppNq/dfHyxHqRAE5lLLNLsq09pBxOkV26WZZeh9V7xDvIkTeFSd4HJCnUi57kQDtJSCkM42yzi7NnMQFgQE4o30SpQe%2BR5X41QfP89%2BxUv6H3Kr/KqNVIGYHqo1MQICtpgNIdg0gUD%2BqwP0mNZAE1kGCFQQpdBS1nhYLWrg5%2BBD0hEMOqQgkFTzpMCujdO6D0GGDKYRIFhMkxnfUmbPYwAMbD8MxseCGWRWoAHoYb/URpYZG/jUbowEVjSxOM/B4wYO4RxaiNW2KZnoqmWqtG016LqoxKquYONyE44xAhuYuMWHY5xQtJwi1cXYiWnjJJzL0jHTgE83ktLaR0rpU5hp7M1nXaJpzE6G2NqbSg/dUlwTMBXRIiQAgBAdpfDQabALfmKQZNCth45b2tBbEAVtK6JG/KHCCmb9QQUAh7RIPrh5FtLf3XiBbY4Jz8msHaGRnCSCAA%3D%3D)

By turning `(...&&Pred_0{}(*))` and `(...&&Pred_1{}(*))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<auto...Args>
requires AllClarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AllClarify<Pred_0, Args...> && AllClarify<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

## Implementation

```C++
template<typename Predicate, auto...Variables>
concept AllClarify = (...&&Predicate{}(Variables));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMT%2BGqQADqgKhE4MHt6%2B/kGp6Y4CYRHRLHEJZkl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcBJgsyQa7JgDMbgQAnsmMrJgA1MrEmPiiu6S3TF5EAHQ/AGpNeCYMXoChO2BMGgAgmgGFtkgRbpDaLQ3AZiHgqOdbicACK3CA/L7mABsJIeTzwL0wJgA7FYaTiIP90UCQctlicrFCIZCAPQAKkFQuFIt5PIFQtuABVMDMFLdhWKoRKRarBUrITyvOkjPdHugAPoabHHPFYZC0C5XCAmAJWAKMj7fH4cumPAgbBi3AjELzU470nEcgM8rU64B6p4Grgms21S2XTA2u22x2fVCE10Wd2e72%2B/2B4NczVQ3b7Q7%2BtxOjM/SHEYCg47gqGPACOXjwj3lSJRaIx5xObnJhqSiPrCkJYJ5MJmmFUyWItxiqE8tyoXgYECzOeIXqoYiUnNpONDpb2ByYR1O1cJdYbU5bmHbndliORqIBmMHw6NbzvE5%2BMFsTMUkQLfXtPwHU4fy4P9x0nJtpwEWd50XZdV3XTdt0wD1dzzP0jwZU9IRmS9KQNJgFCUZpqA3QcuDBLciw4VZaE4AJeD8DgtFIVBODcaxrFuBR1k2O5zGOHhSAITQWNWABrEAAkkL4NEkLgaWODQAg0EDiTMAAOAz9E4SReBYCQNCSLieL4jheAUEAkhk7iWNIOBYBgRAQHWAhkk%2BchKDQfY6HiSIbk4VQDOJABaYlJFuYBkGQW4pC%2BMxeApIh0XQPR%2BEEEQxHYKQZEERQVHUVzSF0WCAHdiCYZJOB4Vj2M42TeM4AB5T5/IRVAqFuKLYvixLktSlSzHxDwQvoRcJK4ZZeBcrRVggJBguSUKyAoCBNu2kBgCkMw%2BDoXZiEciAYg6mJwiac5mt4W7mGIc4upibRahcqTgrYQQuoYWgHqqrAYi8YAq2RRzuF4LAWEMYBxBBl86gAN1lDq51qT5tik8JdjYqraDwGIGtejwsA6n08AsmHSHR4hlyUHE9gR4mjFk1YqAMBtfjwTBaq6q4uKk/LhFEcQSrF8q1A6mr9ARlBBMsfQSccyBVlQeFMmhmKZnQXFTEsawql4VAGZyjGNc6bpMhcBh3E8No9FCeYygqPQCgyARJj8WCvZ6QZ3ZGWCajqAQ%2BgmJ3clDrovvqWYg%2BGBJQ9mX29FI5ok8WFPVhEjYtgkVqOA40gbLNzghuiuKEqSlK0qmiBcEIEhgMkpbpM51YEEwJgsASLdSEUyRji%2BABOY4aUkNSzEkYkrICYkx5MjgzNICzJK%2BYkuGJAyx4MnflK4AIJ%2BJMuOrshynM71y1q89afN6gLdv2ubwrYTgmhYVGaRiphbgtAjVKY8vhcFUplfA2U8C5VgmLQqktpDSyULLKqugTr1Uao9Yupdy6dQ4D1PynxbgDXeMQb%2Bv9/6AN1FwEBYDjQQBmltOabczAdxWm5B%2Br94iBT2qgWaIwv4/xilQo6Y8uBJBoJaeIl1rpVWevdR6pB5GvXep9BwijfqMAIADIGHVQbg0hrQaGUk4Zs22DxfAjw0YYyqljZAONFH4y6B1YmpN7oU3MctdEtMpIMyZpgFm8MjDs1ALfPgPMFB8wFkLRgii4ES2Kog2QMtKo8TQQrDmRsrAq1cerQeWsei631obZWFhTa8QttAq2g8w49Hto7HIftggO2zh7f2aRvZZGjk0gOmRWkhxtvHCOadukZzjuHXoic3bJwziMxpsz%2Bj9NzmsAuxVsHtSqnZUh5C/4AIMNQ2hql8TN2ym3Ray0u6kB7n3EYg9CZrw3iAtSNIT40k0pIWe8VYK4MvrYa%2B7C77wAfr5PqPCuHEHftsL%2Bo0WAKFRilVGNCvgVhmBAluOU8qyHgYk0q8hkGpJ0CAY4pAMFNRhus8%2BmzupP36oNaFCVYXwtuIikBKKEQML4Uw%2BIbdjhsM5u5DanLtpgqFXNEA8LkjJANCyg0bKKJkPiqdKRF1KCyJ4so4GUkNWqK%2Bhovhf1tGA2BhYzAYMIZiCMYo0xwTPGkEsfHdG0MeJ2IcXTJxhMeKuLJucDxVNvGKL8WkAJrNgnhFCatcJTBeb80FsLOJWKEkSCSWVfFcsiUZOMKU1WMQ8ma21shTgvJ9ZK2NpYcp5t4iW1zYMiZ9T06wVdqUGZ7TCiZHrSkDpgdpk5zGbbYZ/R221ITos7tbSxgDtGanEdTae2LRWWJIuK8cEX0rvS24jKEVIrZccyBrcFp8tvt3Xu/dKDFwef4EBxxjgBB0upKyV6aS70pbZTgV9nKXOHgEceAQDIgTHpIMemlJ5cGJYTY4GyX32RvqtYuGVn0VygwC1YDN0jOEkEAA)

## Links

- [source code](../../../../conceptrodon/typelivore/concepts/all_clarify.hpp)
- [unit test](../../../../tests/unit/concepts/typelivore/all_clarify.test.hpp)
