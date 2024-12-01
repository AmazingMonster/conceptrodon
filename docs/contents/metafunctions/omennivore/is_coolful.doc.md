<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::IsCoolful`

## Description

`Omennivore::IsCoolful` accepts a type.
It returns true if the type is a packed `Cool` and returns false if otherwise.

<pre><code>   Type
-> Type == Cool&lt;Items...&gt; ? true : false</code></pre>

## Type Signature

```Haskell
IsCoolful
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsCoolful
{
    static constexpr bool value {RESULT};
}

template<typename>
constexpr bool IsCoolful_v {RESULT};
```

## Examples

```C++
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct CoolLike;

template<template<template<template<typename...> class...> class...> class...>
struct SnowLike_0;

template<template<template<template<typename...> class...> class...> class...>
struct SnowLike_1;

static_assert(IsCoolful<CoolLike<SnowLike_0, SnowLike_1>>::value);
static_assert(! IsCoolful<int>::value);
```

## Implementation

```C++
template<typename>
struct IsCoolful
{ static constexpr bool value {false}; };

template
<
    template<template<template<template<template<typename...> class...> class...> class...> class...> class Consistency,
    template<template<template<template<typename...> class...> class...> class...> class...Silence
>
struct IsCoolful<Consistency<Silence...>>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxCBmAOykAA6oCoRODB7evv6BaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BATV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHASYLCkG2yYAzG4EAJ4pjKyYR9gmGgCCY8ReDgDUAJIKHp5UXrR39xMiQsrxmjmQrzQDDGmFUKWIr2iqE8rwAbmIvJhXkCLFQxEogQARI4gokkgEA7a7fbXB5HNwA15M15UvZMA7HVk0%2Blc9nXTk7Nkck6C7mc86XNgAOhlN0hBgUChlUrlyAVStlh2w8qYiuVqvV%2Bq1OsVrw80LwMIYyFOpEZzN5wsd/JF1L5PNF7vFF2Y0s12rVuo1KuNgb1/pNwYNQeVQjojA2FK1AKeLwIHy%2ByNov3%2Bx3NGStNvpcfo1swRtuybpwNBTXBkIEMLhCKRKPR3ixOIIz2uiWJh1JffJdIeAHoAFSTqfTmejgETqevAAqmDGCle07nY5nO83FIezo9bqdnpPx5dh%2B9kvLEbDUdDhtvj5DAefNxT3bTZqzoQA1vyrBHe5L1dIUL1PcDzx5CVfRvF9IwrBCnxjf0P2eN4hAYVAAHc/0wAB9DRh0BA8IKPMDyLFUCqLOH0rkQu8GLfB8UJfNCv0wnC8PwrhiI/dk8GQfCgziAgIE%2Bb5sz%2BelJLw4ssNwvB/0I0hXk4xTlN45MtRAEB20xRZiLBQThMVUSIDAMAM0knN6TCAgbl0/TMEMgcOGWWhOAAVl4PwOC0UhUE4BlLGsUFVnWTszEOHhSAITR3OWX8QC8swpUSMxJAADiyryNAATlSjQADYssOfROEkXgWAkDRAj8gKgo4XgFBAQJ4v89zSDgWAYEQEBVgIFIvAIchKDQXZ42ICIrk4VQsuKgBaYrJFeYBkAhKQpTMXhMHwIhiDwdA9H4QQRDEdgpBkQRFBUdROtIXQuFIbDiCYFJOB4DzvN8hLAs4AB5EbhvTVAqFeealpWtaNteLazFeCAPEm%2BgEXMGLFl4DqtGWCAkAmlIprGiACamkBgCkMw%2BDobZiFaiBoj%2B6IwmaU5Pt4ZnmGIU4AeibRMAcdnSAmthBABhhaDZh6sGiLxgDcMRaFa7heCwFhDGAcRpbwYgBccVFVz%2B2EBZGzZYvs2o/toPBoje7mPCwP7uzwGqVdIA3iCRJRCR2DXraMBLlioAxgAUAA1PBMGwgGfSF07hFEcQrvj261D%2Bp79A1lBrGsfQbdayBllQFJ6mVxaxnQI5CVMULLDMRqPcOrAC4gZY7D1rIXAYdxPHaPQQjCQYKmGZ7CkyARJj8Uf0nHhg5iGeJnvbhwenGVpe7yJfag7gRehaefh8X2w18nvQZn3wf5hHtuIo2CRvo4HzSAa3gmohhbltW9bNskbbEdwQgJBsTRS4JjOKgdlgIEwEwLA8RW6kGSpIQ4Up8qHESAESQmVip1S8sVfKFUOBVVIDVGKUpipcFKvlLKFCvKSC4F5VBxVn5/Sai1Nq4DOq4z6njAawMRrE1JqjGabBODNBYKiRIi0mA6iMHDfKUouBSgCntQBTcTqyHOknaQKclBpweroKmr13rswfk/F%2B/0OBAyGiNV4YNXhiIkVImRwA5EKKUYjZGhNUbAMOGYMB2Muo8MEXEARqAUbDAcZIwMRguD5S4IEGgtBab00Zg9TmrMhbpO5rzfmgs3Yi0YAQcWks/oyzlgrWgSshZqz9psAK%2BBdYrwNsrZRqgTbbCFhbTyD1ra21Zg7OpWNDqu1ih7L2mAfbqyMP7UAnC%2BAh3DpHaOsc3bx00ZdbRshU73QCgYzOAca5WEsHnaILci4lyyGXCuVdDnWHrq/RuR1DaFy6DvPwEBXCn2egPMoC89Bj3qF81IM96gHwWFvbou8T4bynq8leULZiXz%2BUvaFuRYXn36Eiw%2B98VhrDvqAghZiWGcHscQcRkjpHRJcbEtxGh/77SAejUBWMIGkCgTA4Y8DulEJIfIjQkhEgMMSIkQ4mDJArWeuY1hth2EBK4fAHhg0QahPCdNWaHAxHQxYAoVEEJUQ0ppGMXaDK1HPTWYnDZ115C6J2ToEA5UjEfRVqY36D0mpWJBrY8GmrVrat1WiA1fIxgeLCV4uIPjDj%2BMDt1fGoaiYUBJnG1GelkApBSPhfV%2BV8KGoIMJMlK1qZJLiCkpmLNuaZLLTzPmeshYFLFhLKW9TMCy3lorZWsUanTMGaQBpHdmlGzacgU2nTBCWx6TbO2pwBlO2GULMZ6QJm%2B2mWEWZON5lMFDhHKOMdGBxw0RaiQmybo2vTva/Zxgc7HN6WcwKFzGycFHBXbOtcLD3MCo85u8A27b3he8z5ML%2B7dzBSPYFRQshAoBVkYDR9l71D3uvNFZ8f1wbXtBs%2BqK%2B4osRb87FBKFC30ui65hbqSU%2BteH6vVgbtjBogAAg6PjmUcJxpA6BsDKAPx5QkeRhxDheTynQuqPHEilWI41TgbD2qssQYkbagquBSHyvyxIqCuDJG6YcV1YnmpMcSgQnaonX7iZ04sZYHsMjOEkEAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/omennivore/is_coolful.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/is_coolful.test.hpp)
