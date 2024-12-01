<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsUnequal`

<p style='text-align: right;'><a href="../../../index.md#arithmetic-examinations">To Index</a></p>

## Description

`Varybivore::IsUnequal` accepts a target and a list of variables.
It returns true if all variables are unequal to the target.
Otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> != Target) && (V<sub>1</sub> != Target) && ... && (V<sub>n</sub> != Target)</code></pre>

## Type Signature

```Haskell
IsUnequal :: auto... -> auto
```

## Structure

```C++
template<auto, auto...>
struct IsUnequal
{
    static constexpr bool value
    {RESULT};
};

template<auto, auto...>
static constexpr bool IsUnequal_v
{RESULT};
```

## Examples

```C++
static_assert(! IsUnequal<1, 1.0, 2, 3>::value);
static_assert(IsUnequal<1, 2, 2, 3>::value);
```

## Implementation

We will implement `IsUnequal` using only `<`, meaning <code>Variable != Target</code> is expressed as:

```C++
(Target < Variable) || (Variable < Target)
```

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsUnequal
{
    static constexpr auto value
    { (...&&(Target < Variables || Variables < Target)) };
};

template<auto Target, auto...Variables>
constexpr bool IsUnequal_v
{ (...&&(Target < Variables || Variables < Target)) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKz%2BpK4AMngMmAByPgBGmMQSGqQADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJXEl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcBJgsyQa7JgDMbkxeRADUACpNwJgEpJfnRAB07wBqTXhMMfQKJ2wJg0AEEZsQvA5LgBJBRyCIARy8YmBIJMAHYrKDLjjLjMmI5kJc0AwZphVMliM8LqhLgA3MReTCo3GXDEWS4Qd6vcwANj5EFuxHuBDZp0uX2IPz%2BmAUbPRbgxbgl31%2B/zFyqFIuWy3lABETli0eiDccjajdvtDszTi9aVqHk87dzJdL/oDUSSyRSqTFUJ4YXDEcjaAB9Omo9mc7l8gUO0UnZWutWy%2BWKhUqqUpuWJm53B46/WGyOggD0ACpK1Xq6XURXK9dsEJrlXa2Xqx3y220aD8YTQ0wFEpmhAwGBA/DMEiUacuE8uK8kpczE9joCQCAGd5MMti73Gv3B8OCBBYZPp7RE3Pl08V5c18dsBut0zd2aOKtaJx/Lw/BwtKQqCcIqljWHi6ybJgbJmMcPCkAQmgfqsADWARmK86JmJIAAc2H%2BBoACc/hmBovLYcc%2BicJIvAsIkSR/gBQEcLwCggEkCH/h%2BpBwLAMCICA6wEMkFzkJQaD7HQ8SRKw2yqNhvIALS8pIlzAMgRJSK8Zi8Jg%2BBEFK6B6PwggiGI7BSDIgiKCo6icaQuhzgA7sQTDJJwPCft%2Bv6IYBnAAPIXMJoqoFQlxyYpymqeplyaWYnIeBJ9BUuYsHLLwHFaKsEBIOJySSWQFAQLl%2BUgMAUgrjQtC7MQrEQDEPkxOETQAJ7ubwjXMMQzV%2BTE2i1BxcHiWwgh%2BQwtCtXZWAxF4wBnLQtCsdwvBYCwhjAOIk14MQ/V4HSso%2BeStQXNscHhLsX52bQeAxC5XUeFgPkEFKtFLaQe3EH6Sh6nsa1XUYiGrFQBjAAoHx4Jgjl%2BckjBtZZwiiOIFnGfIShqD5Dn6GtKDWNY%2BjXaxkCrKgyQ9ItCkzOgJx6qYoGWCRvCoO9Bn7YTnTdJkLgMO4nhtHooTzGUFR6AUGQCJMfhziLPSDILSxsztAh9BMPO5HONR1Irswy8MlRjP04t6PizTa4slSrAoEFbBInkcD%2BpAMQznBhfJSkqWpGmSFpnK4IQJDQal6UA6sCCYEwWAJBAKEgJIxyvARxzopIGiSFhvIaBo/i8gRlEcNRpC0bBry8lwZEEdhJf%2BJIXD%2BPHvL2z5TEsWx8EA9xfHZQJgUiYVxVJdJbCcE0LB0uiClMMSBhGDFBGvAuAG6b7BlGbIpmI9IyPWWjdm6CuzmuW1Nt2w7vkcAFQkXJcIXPMQw%2Bj%2BPyCT8A0%2Bz4u8WoIl8T%2B2YaUt5xWU5e/PKSVRJFUASVIeI8FIPzWlwAiVQ%2BB0GqrVeqdkOotVhmgrqPU%2BoOFhkNRgBBRrjR8lNGac0FqwxWr9bYAF8DbTqHtRa89VBHV2LDM6XQfJXRui1e6ND0rPVhu9T6mBvqrSMH9UAf8%2BDA1BuDSG0M/xwWRqvcy69ZCb1sgBHemN/o0ysJYPGMQCaR0AiTTIZMKZU30dYemgEmZ4CwCY82XQFZ%2BAgK4A2c5%2BalB1sLNIossgqwlikAJ0sBZ%2BLVq4jWvRZhePljEpWcxfGm0NnE4JaT%2BgmyFlwc2ltzKH28nZJi19b5jwnmtZ%2Bc9vZ6T9ilXJgc/7B1DuHSgNs84FxnsndENd0TomOCnSQyk5zH0brYZuGUuI8X4oJIKIDe5SRkoPG%2BkUWAKDpESOksDXjWhmDpWpS85wqIRmouGmj0YgAonvNyS1Cn12Kf5LuwVQpD1WeszZ2zdmiggAlIBn8UrHB/pM/%2BKAwHAJ7mCkYGzkjJHDLA0MXyBwrPXog%2BIyCGpNS6hgzF3Ver9Twe/YahCxoTVoZgaas0xAUNelQiR/DSB0J2owg6LDkDHXYYIThl1rq3Wanwx6gjXrCLSKIn6EjwhSMyjIpgIMwYQyhjDV6xyzISHUVZVGWidCXN0cYHGhjuHOLMaTTgpYKbY1phYOxjN4jM0NerHonNuY5BCT4hYOTQmFEyPEqWmRsly3tfUdJzrDbRJ6Ekv1usjYtAyWrLWETUm5LWBsK2iaLpHwbk7V5Kk1kbPpJ8gkspvk%2B30v7Bpv9MrNLDiMUxF0OkgDMDPY4xxAjJyqBoJt6IyL3MYpwJu7Eg6kFQpIdEWkelcCkARbp8cuDohzscIpPbmLlqQjnbS3bHZLuBasd66RnCSCAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/is_unequal.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/is_unequal.test.hpp)
