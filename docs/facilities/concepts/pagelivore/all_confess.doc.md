<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::AllConfess`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-all-confess">To Index</a></p>

## Description

`Pagelivore::AllConfess` accepts a class template predicate and a list of elements.
It returns true if the predicate evaluates to `true` for the value result of every element and returns false if otherwise.

<pre><code>   Pred, Es...
-> (...&&Pred&lt;Es::value&gt;::value)</code></pre>

## Structure

```C++
template<template<auto...> class, typename...>
concept AllConfess = REQUIREMENT;
```

## Examples

`AllConfess` turns a fold expression of a class template predicate over `&&` into a concept so that it can be used for subsumption.

Since `(...&&Pred_0<***>::value)` and `(...&&Pred_0<***>::value) && (...&&Pred_1<***>::value)` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
template<auto...>
struct Pred_0
{
    static constexpr bool value {true};
};

/**** Pred_1 ****/
template<auto...>
struct Pred_1
{
    static constexpr bool value {true};
};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (...&&Pred_0<Args::value>::value)
constexpr bool fun(){return false;}

template<typename...Args>
requires (...&&Pred_0<Args::value>::value) && (...&&Pred_1<Args::value>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQB/qQADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJ/kl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcAPQAVAd7ANTKxJjoAPoaR4d7OyYaAIIEmCzJBi8m/m5MXkQAdICvtgHo8ZsQvA4TmdLhpQSYAOxWJ5HVFHGZMRzII5oBgzTCqZLEI4xVCeI4ANzEXkwR0RFgIEMwiIAIl9kY9Wez4U99odoecLlwbod7k8Xm8Pszvr8AUD/CCnuDIQQBZcuPCkaC0ejGlicQJ8YTiaTyVTvLT6YyaVz/BzbfbebcjgA1JgATxFBzFz1e70x0p%2Bf1QRwAksDQcqoW73ZqOTqMfrcUaiUdZSHzTS6Ujwwi2XbNfnHY8%2BQcjlQvAwvXdQRL/Z9vgR3clGKxMID/o9iMAFBGnmcAI5ePBnBRHCAd8wANmnp0FcO%2BXZ7IBAmel2BXa%2BWoOTL2NJLJtHLlYg26RZwIGyrVDESm5eZ5vslAa%2BbibLeYbA7S97CtBg%2BHUdx0nMwZ1AudYVfH9N2pdcYItZY6VA6dgKBZDwJhIUoO7BR4JtBU8Mwbcnl3AlU1NI8KwYU96QvK8jmtaUrAfJ5QVLY4ABVMBmasfR2HYjmwYhiBISM9TwZALiYBQlGaahK1fGNXw1P8FVPbc7Q4VZaE4ABWXg/A4LRSFQTg3Gsax0XWTZLTMfweFIAhNC01YAGsQF0qd/gADinKRdIRKdJAATn8QK7P0ThJF4FgJA0IJDOM0yOF4XCgicoytNIOBYBgRAQHWAhkj%2BchKDQN46HiSI204VRfIAWiCo5gGQbEpH%2BMxeHOQgSDwdA9H4QQRDEdgpBkQRFBUdRMtIXQuFIAB3YgmGSTgeG0vSDOckzOAAeT%2BYrVVQKgjjqqdGskZrWqOdqzHHDwKvoYlzHs5ZeAyrRVggJByuSSqyAoCBfv%2BkBgCkMw%2BDoF5iFwiAYm2mJwiad01t4RHmGId1dpibRagyhzyrYQRdoYWgUZmrAYi8YAfloWhcO4XgsBYQxgHECmRzxvAKW47aCVqP5tgc8IXh0mbaDwGJlsxjwsG2xk8FixnSB54hSSUFlXlZiWjGc1YqAMHsXTwTAFt2j9UfG4RRHEMbBvkJQ1G2ub9FZlALMsfRJdwyBVlQZIegZ%2BqZnQL4WVMSxrDMJLVeIPred9zpukyFwGHcTw2j0UJ5jKCo9AKDIBEmPx5oLnpBlzkZ5pqOoBD6CYM9yauui5uvZgr4YEmr2Zi70DFmg7xYu9WBRrK2CQNo4fTSES3hktOhqmpatrJA68dcB6567K4N7HL11YEEwJgsASU9SHcyR/H%2BUKEUkDRJDMSQp3izzgsijhotIWL/DMf5/CnBE3l/DeV0rpLgYVgreRnttZKqUQDpT1tlPK30CoHRKoDYGT1qpsFqovS6yADBGBusFf4XB/jGW6kQOO/V5r22GrbaQ9tJpOxmroCGS0Vqo0ntPWeO0OD7SKn8I4x0F7nSagQ1mxDSHkPuqgR68QkI/13h9LKKDMHxFKkDORf0nooEIWDYKXAgg0FoNDWG8MZro2RpbKxmNsa4wcJbQmjACAkzJttSm1Nab00tszbW2xjL4DOHUHmDMKGqAFi8S2IsujbQllLZGssAnvTjkrByqt1aYE1izIwOtQCZX1obBQxtTbm0YJbOhNtRqMNkMw6axk2Gu11hHKwnt4k%2BzPv7QOnBg4EFDv4cOHsLDRznrHeOHSR4t1rn4CArhe7zWzqUTu%2Bc0iFyyI3EuKRVnlxzss5uyc279HmUnVuvR267KHn3HuGyrn9EHnnHeawNjj0eWLHhMDOCiIujifRUiyHXAgBvKhiid7vX3qQQ%2Bx8Rhn3ckYoIYtP7f10v8EKulgpmHRaBby4CgrQJmrA2w8C94FKQfAFBhVDqaPUcQbB2wmgsCaiwBQFJsQUi4CQqUMwur4CoX1Aash6HVKtnU52ARFrLVWozbhW18V7TQUdE6qhGXMtZey/4nLVQQAejohRL1/DKMQWo7R/0qXGt0Sy5IyQLhsuChcDVFwlWMKhvEcxCMkaYxse6rGOM8ZOLkUTVxpNyaBMwFTGmYgfHKz8bk5JpAglc1CXzCJyBBbRMELE8WktpbuiSfLVJlsMlpCyVrXJ4R8mfT4EUkpZsLbK0qSNCQNSJqO3qToMV%2Bj3aRzad7eAfsA6ZAZjsEOnbWnDJjvEahCcz41x6KndOORNmLIWA8rZhRMjHLLpke5VcTnTPri0G5%2BzTn7u3V3MYRzD3noHhch5I8x6jWlXipKnzHVHCZSyykaqNXrx5SQEFBqCkHyPifSgk9EUBF/jiuyZgYNcG8hoKcaKn1z04HAhBgHz4gEvqQ4BukH7%2BF0ghuygV37%2BBlc%2BlKxLPqT06shvhYKMOq3SM4SQQA%3D%3D)

By turning `(...&&Pred_0<***>::value)` and `(...&&Pred_1<***>::value)` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires AllConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AllConfess<Pred_0, Args...> && AllConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<template<auto...> class Predicate, typename...Elements>
concept AllConfess = (...&&Predicate<Elements::value>::value);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgkv6kAA6oCoRODB7evgFBaRmOAmER0SxxCUm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJM/jcwNBr0wELcTC8RAAdKiIdhrsgDAoFNdlMRMPhRMDSNcCABPFKMViYVHI7BPRgEBTowFoBgbFIEa7nWi0DwMKiYHHXCEAEWuEDp5gAbLL8YS8MS4ZCGSCmQoQCAAG5iLwq7Ba3XeTCLCFWC6A76/E5Wg7XAAqwuZ71tXxth3%2BdpuCvQAH0NK69v9oY9YfDESi0f5sICxsQvA48QT/RpASYAOwW87XXPXGaOZCYgRjTCqFLEa4xVCea7G/WirMEBNwjNi83ptsdy3un0pv1cIM7EMgsPgyGR1DSmNx5uJ7m%2Bged7N5/NNQvFhil8uV6u1%2BuYRsWOet9v%2BbOZs8X3t7a4ANSY5KHI5h44RSNQd1ZF3j8/vj%2BXQFVwLJVN23CtrknOs9UPTMLFuS9uwBLtz3TG8dmuKgvAYZ9AVDMEVShSlqTYOlzmIYAWRnC4CQARy8PACVxXl%2BQEIUcXhRcgh5CiFGnWMLnZcDdxrWhMOwiAzSzAkCDWHCqDEJQOy7HsgVHAj4QpKlmFI1FyMo79yMwejGOFHk%2BQFdiqLcLjSX0vjowxWVZXM1jBWFazFy4OzeP4tkS2BHcq1E8SGEkuCZLkskW2U9tVOtR1nVwn91yVP0mBxeICGobD4Qfcl4S4VkY0ks1zw4ZZaE4ABWXg/A4LRSFQTg3Gsax81WdZYLMfweFIAhNAq5YAGsQGqmVkQADhlKRqozGVJAATn8eaev0ThJF4FgJA0IJ6sa5qOF4TUggGhqKtIOBYBgRAQFWAgUiRchKDQB46HiSIaU4VRpoAWgW65gGQIspGRMxeEVIhiDwdA9H4QQRDEdgpBkQRFBUdRztIXRvIAd2IJgUk4HhKpqurBqazgAHkkUe7lUCoa4fplf7JEB4HrlBsxJQ8N76ErcxesWXgzq0ZYICQV6UnesgKAgKWZZAYApDMPg6GBYhNQgGIKZicJmnJYneD15hiHJKmYm0TAHCN0hXueAgqYYWhDaxrAYi8YAET5TVuF4LAWEMYBxDd0yHDwbVhQpstraRTY%2BvCYEqqx2g8BiAmzY8LAKebPBtr90hI%2BIaslDFEEg9ToxBuWKgDEou88EwXGqe0234eEURxBR9v0bUCmcf0IOUDayx9DTzVIGWVAuSyX3frGdBxVMSxrDMA6i%2BhrAJ8krprfqFwGHcTx2j0UJwkGCphm8wpMgESY/Gv9Jb4YOYhgSby7D3npxlaY%2B8g/2oX8BC9BaK/S%2B79bA/3vnoGYoDz7zCvssBQnUNgSFJhwWqpB9q8EOkzP6AMgYg0kGDSUuBCAkFFD1Lgwt%2BrV2WAgTATAsAJB3qNJIyJloZkkBoSQZhJAyl2uNRa60OCbVINtfwZhkT%2BBlBmSa/hJrVWqlwFai1JpYIpodY6IBTrV0ujdCWd1aZPTlgrfmn02DfXwWzLEQdOaLWRFwZEjVIYkBhnDWQiMu7SB7koPuWNdCq3xoTI26DMHYMphwGmD0kTXAZnglmANbFGHsY45xPNUB83iJQyRNDRYXUMWY%2BIz15aZOlvzFABgjBcEWlwIINBaAay1jrLGJsDa2zaWbC2VsbYF3tkyJ2LsKbu09t7Wgvs%2BoBwrpsRq%2BACTh0jr7FxqhY7AltonWoFNU7pwNlnGZItob5z6kXEumAy6ByMJXUA50a51wUA3JuLdGBt08Z3ZGPjZC90xo1QJg8q7LysKPbZ28p4zxLJweeBBF7%2BDFAC1e694ibyjpPXe4dnAQFcNA7yZ8yhvz0DfeoWLUhP3qGAhYADujAKgX/B%2BqL6ggP6PAvFH9qW5FpbAxluLwFoJWGsVB1CRHhM0ZwBJrNMRVOAKkpxgYIBkKhjk6hIs6GkAYUw4YrCdpBGTmIiR1VkRLWqotMwRqzAykmiohaGisZaNsDo2hNz9HwEMfdOmJSinEAsZsZoLAAYsAUNqIs2oanIgImMCG%2BAobuO8u3Lx7zUbyD8d8nQARSDBKJn7MJ5NrXU2MfTRmqhfX%2BsDcG0N3IIC83KdkwW/g8l6MKWUmWbqG0VIDSkFIfog2LT9KWv0BafHq3iM03W%2BszYdJHebS2e9bb9MEIM12szMAey9mIcZtspmXP2aQOZX9FnRxWcgOO6zBCbJTmnDO5I9k50ObbE56Qznl0ueEa5Ys%2BB3Iec3VuBcY1vIkB8tGib%2B4polcPFeQLx7wFBfUX2WwF4gcBRYNeOCN4w2RTvT%2BaK/AYsPkSnFF9yXEqKFkIlBKshkqvnS7%2BfQiXofpT/MjECOXUbo0y7lArkF8uRpmq1B0RV9uuH6gNdYS2wjGKQiNFDBaKvtWLehjDmGUHQTqgIUiLU9TMOprgk0NAykNdxnBnBtG6JuSNEYjiFHVV4f4aq2merzREf4LNPGjrSaGiI8GenIlKuM4XQdWREhAA%3D%3D)

## Links

- [Source code](../../../../conceptrodon/pagelivore/concepts/all_confess.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/all_confess.test.hpp)
- [Example](../../../code/facilities/concepts/pagelivore/all_confess/implementation.hpp)
