<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsPageful`

## Description

`Omennivore::IsPageful` accepts a type.
It returns true if the type is a packed `Page` and returns false if otherwise.

<pre><code>   Type
-> Type == Page&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsPageful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsPageful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsPageful_v {RESULT};
```

## Examples

```C++
template<auto...>
struct PageLike;

static_assert(IsPageful<PageLike<0, 1>>::value);
static_assert(! IsPageful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsPageful
{ static constexpr bool value {false}; };

template<template<auto...> class Sequence, auto...Variables>
struct IsPageful<Sequence<Variables...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxBIA7KQADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxXEl2mA6ZQgRMxATZPn4Btpj2RQwNTQQlkTFxibaNza25HQrjA2FD5SNVAJS2qF7EyOwcBJgsyQa7JgDMbgQAnsmMrJgn2CYaAIIzxF4OANQAkgrKTMCYVC8tAejxMCQs7xmTEcyHeaAYM0wqmSxHe0VQnneADcxF5MO8wRYqGIlGCACInCHkykgkG7faHW6nekHaFMtxMLxEAB0vLucIMCgU7yEmAAjniGFtSO9OTzeQA1Jp4JjRegKO4gl5vAhfH5/AFAk5uUUSxhbY1K4gqtWYBS87ma473J6EyGNGFwgSI5Go9GYnHefGEgivW4JCnHKkRmmup4AegAVMmU6m0/GQUmU%2B8ACp2gjC1MZhNp0tF2lPFmM41y1AOzVPbUfX7/UIAayZVjjzw9eGQAH0mEK4gQIN8W4bgacJ%2B32YF3lwndgQCBA3jlrGe9C%2B4Ph80IGAwHqJ4Cp24wgQ7iu15gN1GOKtaJwAKy8PwcLSkVCcNzWayQ9ZNmDMxjh4UgCE0B9VjbEBnzMbkEjMSQAA5kOfDQAE44I0AA2ZDjn0ThJF4FgJA0QJ30/b8OF4BQQECCCPwfUg4FgGBEBAdYCGSLlyEoNB9joOIIhuThVGQnCAFocMkd5gGQWEpG5MxeEwfAiGtdA9H4QQRDEdgpBkQRFBUdQmNIXQuFIAB3YgmGSTgeEfF830gr9OAAeS5HjdVQKh3nEqSZLkhSF0kZT3ggDxBPoVFzFA5ZeEYrRVggJABOSISyAoCAMqykBgCkMw%2BDoXZiDoiBojc6Iwiac5HN4GrmGIc4POibRakYsCBLYQQPIYWh6vMrBoi8YAOVoWg6O4XgsBYQxgHEYa8GITq8CxO03KRWouW2MCLy6NzaDwaI7JajwsDc0M8FImbSA24h0SUMk9gW46jEg1YqAMYAFAVPBMGsjyrnfMCdOEURxEM8GTLUNzLP0BaUD/Sx9BOujIFWVBkh6abJJmdATjJUxLGsMwqIezTNsxzpukyFwGHcTw2j0EJ5jKCo9AKDIBEmPwrO5npBg5pZabWgQ%2BgmZncismo6gl2ZheGSoxn6Pm9ChZolcWSpVgUQCtgkZyOFfUhKN4aiAok6TZPkxTwrMSLcEIEgCRArhEvAz7VgQTAmCweIIGg/xjm5DDjgSAJJCQnDyOfHCMMIjhiNIUjQO5HCuDwjDkKz59JC4Z9w5ws23Oo2j6K9pjUvYtLOO83icry2KRLYTgmhYLEEkkpgBQWhcMO5LhuU/NSXc07TZD0qHpBhpQ4fM3Rits%2ByGuN03zfcjgvO4rl3j82ViE77ve%2BQAwjAHoeR8i6LMtit3jjMT3kuYuvm7iPjctQGKRg7rvJLPgtLgGEuCBBoLQMqFUqrmSanVBqpBYEtTah1Bw8CeqMAIP1QabkRpjQmlNeBc03rbE/PgVadQNrTVHqoHaux4EHSfOZY6p06oXRIUla0t0wIPSepgF680jDvVANXPgP0/oAyBiDeB4Np4GVnrIWGZlPxL0Rh9EmVhUbMIxkHL8ONMh4wJkTdRZMKZxCptovWXRxZ%2BAgK4dWVk2alGVlzNIPMsjS35ikVxQt2bONllY%2BWvRZj2LFoEyWcwnE6w1sEjx0T%2Bja05h7NYGxDZJMYRvMunBD7Hx7n3C%2BwCr4aCdupV28UPZJW9qQX2/sRg6MYSnNOg8NCSASEXBICRjjR0kDJKym9y62Eri/Gu8A65cR8p/d%2BxBW7bA7sFFgCgsSwixAUxkMxVIlInlZGRkM5FGXkPPJROgQAERXg5Ga69XLmWojvHy%2B9/KzNkvMxZ2IVlshmDfb%2Bd84gP2OM/T6LF0qfKyhMoFsVVzIGSMkfsyyML9lWQQQcR8ZIlQgXEKB1VaotXgYg1q7VOpoO/r1TBA0hqkMwKNcaYgCF3SIYI9hpAyFrUoVtGhyBdr0MEIdJhJ0zrnDYVdTh8CeFpD4a9QRYRhEpVEX8cRgNgaMGkVPHZEh5HGQOfDY5qjjAoxsFo%2BAWM9Hek4PGAmyNSaWHJhbSmeAsAWNCT0BmTMcieMcQsRJXjCiZBCYLTICTRZyx6OEkJAb6iK18VE2WMTnVxK1uGxJesDYGQuaXK5WSHnvCeUs15ux3kQGdhpB%2B5Sq4pR9n7AOlBjYNJAGYQexxjjPnQgXcidaEh4RTVRTgFcGKVJgi05SrSuBSAws0hI4cqhJ2OJcjtNFi1QSTipdtFtO2zuWKsB66RnCSCAA)

## Links

- [source code](../../../../conceptrodon/omennivore/is_pageful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_pageful.test.hpp)
