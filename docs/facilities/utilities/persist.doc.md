<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Persist`

<p style='text-align: right;'><a href="../utilities.md#persist">To Index</a></p>

## Description

`Persist` accepts a list of items and returns a function.
When invoked by an operation, the function instantiates the operation with the items.

<pre><code>   Items...
-> Operation
-> Operation&lt;Items...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the items.

<pre><code>size() -> sizeof...(Items)</code></pre>

## Type Signature

```Haskell
Persist
 :: template<template<template<template<template<auto...> class...> class...> class...> class...> class...
 -> template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Persist
{
    static constexpr auto size() -> size_t;

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class>
    alias Dawn = RESULT;
};
```

## Examples

- We will create a `Persist` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we will transport the items to `Operation`.

```C++
/**** Items ****/
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedPersist = Persist
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Result ****/
using Result = PackedPersist::Dawn<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Persist`.

```C++
static_assert(PackedPersist::size() == 4);
```

## Implementation

```C++
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Items>
struct Persist
{
    static constexpr size_t size()
    { return sizeof...(Items); }

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class Tranquil>
    struct Detail { using type = Tranquil<Items...>; };

    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Tranquil>
    using Dawn = Detail<Tranquil...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAOwArKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAXCyG8WFuJgCbmQE3QWCosOwIJBfwBWIOQMxtwAkiw0vQ2IImI0vodcdiaWd0VcCJgiQZGbC3IzmeTMGyOcSuTymXzWXDeSzuSLBWK2UwvEQAHQK1G3SFMBQKBVypUqtUarUGHWKgLYZX69WG43as1y/EchSokETYheBy3ZTxLITdGJKxXW5%2B25zRzIZUCCaYVRpYgBvAAL0wAH0CNG4xBliD/TDvbdiJgCBsGMnMKgqBqIDamQo0wELJn7vTLhnRfyJZzhezJc3263xV2hT2m22Bz2ZfLzSbVVa9RPdUbxwbNbPLTOLabl3PPgAVYiGACOXjo9t9/sdzqTjxadEzNa8WSMtwIAE9njCAvdblvd/vaGzyyxJ0bYRrExEjrat60bDtB0g/toIFbs4L7BCpRbRC4RHVA1yXMcsIXFdp2w1cCPw3D1w1D8GD3A8AKPP0b3CYAHiYAB3AtYTfc8mCotxyMo2hlxAEBH2eQCvVAn1gV%2BWksWpO4ADE8GICZbmwVRWGJTBKRxDEpIBIF0TBCEoQ0tk0AYLY0gIO1qIk64jgJW1NLpBlYJQ5DezcockM7dDMMIkicKnedAv/NErhPF1f3jDQRKuEFPNczt4vcxKXLcHyiKCxc/OC3ziMPS5wqTSKuBimykvK1KKvgtDZQwjKQtI%2Brcsy0KCoIJ0Io5eMzFKuLKv66rkqgwb0v87KsryiaWsa3CHXa097KZeMAl6yS7gAeWebcKW%2BPrBqq1Chpg/bUtGnKmousbJrwlq5o6pNNvickclW2y7mUJhkAAa0wdBbgANQ%2BOxHKBOi7w%2B77frdRS8CUtjXXdWGCHROF039SKNFIGEaMWlh4y4LG0b9SKzEJnHIpW2KALA2K1oOW4hC8NI0iUdAACUPi8Wgk12q4wYYxnmcyX6OYULmk3hx7tpeqm3CJ3GorJht0a6gnseV4mutJ9WMwplG0Rpmy8VF8WQZBfnbhN7mXzfCGfvQaGPQIAT7mYhg2Sl56BHtQ3tLuDcPh5qk5ue5B4wneICAgREBIUVgE1VNkrYILHBeKEXOe51Eq3Ev2dNOGT6aETBTL%2BlS1PoM26fzwF60DPAw4jtoIDtqHEYmWPY0wVMbfhyQc44VZaE4ZJeD8DgtFIVBODlyxrADdZNmMsEeFIZ2J8H1YvpAZJJDlDQAA4zDMABOE%2BuGSQ%2BD64RJEmkYeOEkXgWAkDRMfHyfp44XgFBATH160KsOAsAYCIBAOsAgaRZTkEoGgIkdB4iRHjpwVQB8ABsABaNBkhbjAGQMGKQcozC8F%2BoQEgeB0B6H4IIEQYh2BSBkIIRQKh1Ab1ILoAmTFtxpE4DwIeI8x6aF4F/dasooFJmLLcVBmDsG4PwbcQhZhbgQA8PA%2BgUZzABC4MsXgADB6kAgEgOBaQEFkAoBAYxpiQDACkKTGg3N3SUBiEI0gMRwitAfLw3gbjmDEAfOtGI2gS7r1XnA0kBB1oMFoJ4thWAYheGAGlWgtBf7cF4FgFghhgDiFiQpYJeAABuHwXHhhLrKbYq9wiMgfpPWgeAYjbj8R4LALj2p4Bfmk0gRTiAxGFo8TJRg6lGCEasKgBhgAKH%2Bu8Jij1x6r2ocIUQ4gGELOYWoFxHD9BZJQNYaw%2Bh6m/0gKsVAFkcipIwYiNipg56WDMJ/bpxAKHFKOT0fJzgICuGmH4AmoRwjDCqKMAmxRsgCC%2BXoYFjQFgjASATOwbymiTHaJ4Toeg4UOD6IiqFAKYW2ERWC2FmK/mLEBasBQi8tgSH4RwUepAP7CM4FI9BWCcF4IIXvJREBcBkI0SvHRa8RmrAQJgJgWAEiplINvQIcoT4BDvhoSQZhJBoLfskNBJ99CcCfqQF%2BWi5RoK4Ggg%2BJ9r5oN3hfGVaDaUuK/j/P%2B/KN5ANAYY8BYjoHmMseopBbBOCtBYAUxIGCmDjjvFwE%2BcouD7xIfgIgjzKEEwWbQ5Z0hVlKHWWw3QpMuFMB4WkqlNK6VT04KIyBspbiSOkcy4NDFQ3hv3so1RJj1EwjBGYPleigFGNQGo%2BIMCLFdsbaMFURhQ1cExvYxkiknEuJ8R4rxrj3F%2BICUEhwc6wmMAiVEmJk84kJKSSkudGSsk5O3Xk9FRTUmT1Kcgcpc6qn1BcXUhpHjmnbEnm0jpq9um9KUP0o99ERl8HGZM6Zsy50JqWfQ5Nsg1msMnhmrZwzrlWEsPsmIhzxUnMaOcy5r4kPWDucIh5Tz0OkvqPClwDB3DIoKD8yjWKlhAsyCC3I1HvnpCY5Col0LUVkfRQIfoUxWM8d6PxwlFRuMEoGPi3F8wuPYspWsDYFLtEaupYIthX9GUyJwUO6tYaI0aGUVymNzatFtoFaQIVIrRjioflqnVYb5UpBPrfAICqlWSAJgWm1tg7XtoMU6pAEDxG9o9Yg5BHBfWyL/AU4MBSa1igmFG7lFCqGyETZBxh8hU2wZ0CAIIWac18NU/m61RbXUSKoFI6LChYu3Hi2GxLSYVH9tMaZgI5mHUGM7d2sxsDWvqJALF5m8YGvxia/GVQ2C%2BB0Anb/CAzi2Ezr8XO5b/jAnBNXV28JkTokuJ3YksQ%2B7OmHsGa%2B9Jp7HDnpKaoMpjJb2CHvWwx9jSHwvtaY8j9vAv19KZH%2B4ZXWxlMAmVMzAMznhzN4OBuhEgoNMJyxs/LCHjC7JQ4%2BkjU9Tmhk4DsGOeHbn3PiLG554q0WNAo1R/IbHfnifk4xkoORpMQpyPRwFry%2BMIqk0J2FvHGgCcGHJhjMnBNU9RWJ/5DHSXkvoXm9Tn8GVTZwTFuLCWuRKU5dGkgpntG6Is1Z0VlAqX2ZAKfOUAQAjJEvp5t%2B5vEiGqtRpzgtr/4WclckaVN9EhvwPpIc%2BXAj5mEtQ/AIcv6Xf3tYAqlxCHfy/D%2B21Y3SsjOEkEAA%3D%3D%3D)

## Links

- [Example](../../code/facilities/utilities/persist/implementation.hpp)
- [Source code](../../../conceptrodon/persist.hpp)
