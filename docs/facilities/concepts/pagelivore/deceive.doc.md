<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Deceive`

<p style='text-align: right;'><a href="../../concepts.md#pagelivore-deceive">To Index</a></p>

## Description

`Pagelivore::Deceive` accepts a class template predicate and a list of elements.
It returns true if the predicate invoked by the value results collected from the elements returns false and returns false if otherwise.

<pre><code>   Pred, Es...
-> not Pred&lt;Es::value...&gt;::value</code></pre>

## Structure

```C++
template<template<auto...> class, typename...>
concept Deceive = REQUIREMENT;
```

## Examples

`Deceive` turns a class template predicate into a concept so that it can be used for subsumption.

Since `(not Pred_0<***>::value)` and `(not Pred_0<***>::value) && (not Pred_1<***>::value)` are both atomic.
Both candidates are considered equally good.
Thus, the call is ambiguous.

```C++
/**** Pred_0 ****/
template<auto...>
struct Pred_0
{
    static constexpr bool value {false};
};

/**** Pred_1 ****/
template<auto...>
struct Pred_1
{
    static constexpr bool value {false};
};

/**** Vay ****/
template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

/**** fun ****/
template<typename...Args>
requires (not Pred_0<Args::value...>::value)
constexpr bool fun(){return false;}

template<typename...Args>
requires (not Pred_0<Args::value...>::value) && (not Pred_1<Args::value...>::value)
constexpr bool fun(){return true;}

/**** Test ****/
// Error
static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQB/qQADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJ/kl2mA6ZQgRMxATZPn6Btpj2RQwNTQQlUbHxibaNza25HQrjA%2BFD5SNVAJS2qF7EyOwcAPQAVAd7ANTKxJjoAPoaR4d7OyYaAIIEmCzJBi8m/m5MXkQAdICvtgHo8ZsQvA4TmdLhpQSYAOxWJ5HVFHGZMRzII5oBgzTCqZLEI4xVCeI4ANzEXkwR0RFioYiUiIAIl9kY9Wez4U99odoecLlwbod7k8Xm8Ppgvj8/qhAf9gaDwZCCALLlx4UjQWj0Y0sTiBPjCcTSeSqd5afTGbRmQi2f4OVzHTzHnyDkcAGpMACeIoOYuer3emOl31%2BRCOAEklU8VVDvT6tRzdRiDbjjUSjhHUJTqVakTH7dyns6nbzbkcqF4GP67qCJSHPt8CD7koxWJgFY9iMAFLGe5gAI5ePBnBRHCAMVBq06CuHfHt9kAgC00hXAldrzDLUEZl4mklk2hVmsQXdIs4EDa1m3Ml3F0vi4NSmWt9vMNjd3v9/wgp5nCOY6YBOU4zuqVwykuChbvmG5/rBlrLHSZgAGzmKhk7TrOMJClBP6IeuQIIau%2Ba7k8%2B4ElmZontWDDnvSV43kcBAQmGViPpyFb8gAKiBaq3IGOw7Ec2DEMQJDKvqeDIBcTAKEozTUDWMqJjKmp/sC567o6HCrLQnAAKy8H4HBaKQqCcG41jWOi6ybFaZj%2BDwpAEJoemrAA1iAhmof8AAcqFSIZCKoZIACc/ihU5%2BicJIvAsBIGhBKZ5mWRwvAwUEblmXppBwLAMCICA6wEMkfzkJQaBvHQ8SRJ2nCqIFAC0YVHMAyDYlI/xmLw5yECQeDoHo/CCCIYjsFIMiCIoKjqLlpC6FwpAAO7EEwyScDw%2BlGSZ7kWZwADyfzlWqqBUEcTWoa1kjtZ1RzdWYk4eDV9DEuYznLLwOVaKsEBINVyS1WQFAQIDwMgMAUhmHwdAvMQMEQDE%2B0xOETQ%2BltvCo8wxA%2BodMTaLUOUudVbCCIdDC0BjC1YDEXjAD8tC2pjpBYCwhjAOINPAXUFIgftBK1H82wueELwGQttB4DE624x4WD7axeCJdwvB88QpJKCyrwc1LRjuasVAGH2np4JgK2HR%2BLOjcIojiFNNuzWo%2B1LfoHMoDZlj6NLMGQKsqDJD0MEcM1MzoF8LKmJY1hmGl6vEEN/N%2B503SZC4DDuJ4bR6KE8xlBUegFBkAiTH4y1Fz0gz5yMy01HUAh9BMWe5LXXRE/UsxV8MCS17Mpd6BizRd4sPerAo9lbBIO0cMZpCpbw6WXS1bUdV1kg9ZOuADe9TlcF9rkG6sCCYEwWAJOepDeZI/j/JFCKSBokhmJIqHJb54WxRw8WkIl/hmP8/hUIIn8v4fyhlDJcCiuFfyc99rpUyiAbKBt8pFX%2BiVE6FVQbgzevVNgjVl63WQAYIwD1wr/C4P8cy/UiAJ2GstG2417bSEdkoZ2C1dAwzWhtTG09Z7zwOhwY6ZU/hHHOkva6bUiEc1IeQyhz1UCvXiChP%2B%2B8fp5TQdg%2BIlUwYKKBm9FAxCobhS4EEGgtB4aI2RgtbG6MWY2NxvjQmDgWak0YAQCmVN9q03pozZmqtWY6yMFzcy%2BAzi835gtQWyBhYszFl0faUsZbo3ltscySsVYuXVprTA2t2ZBPCKAXKhtjYKFNubS2jBrayEYZNZhsgnbzXMhwt2%2Bso5WC9ok32F8A5B04KHAg4d/CR09hYWOC946Jy6WPNu9c/AQFcP3ZaudSjd0LmkYuWRm5lxSOsyuedVmt1Tg3PuWyB4zJ6I3OYKyR4DxOTkbZg8rkLALnvNYGxJ6vIlnwuBnBxE3RxIYmRFDrgQC3jQ5Re9vqH1IMfU%2BIwL7eRMUECW39f6GX%2BBFQy4UzDYrQv5SBYVYELXgbYRBB8ikoPgGg0qp1tGaOILg7YTQWBtRYAoCk2IKRcDIVKGYfV8A0KGiNapdtanTXkKwxpOgAirXWptVWvC9rEqOhgs6F1VCsvZZy7l/xeVqggC9PRSiPr%2BFUcgjRujgZ0stfojlyRkgXC5eFC4eqLgauYXDeIliUZo1xnY31eMCZExcQosm7jKbUxCZgOmDMxB%2BJcmzXWqTeChPbnzYOVDVBCxeLEwQ8TJbS1lj6FJisE4ZLVvEbJuTdYFOQUbJgJszYWytv4hhoqJB1JmpKl2MrDEe2jh0n28B/aB0yMHHYYd%2B3tNGXHeItCk4Xzrj0dOmd7k5wzsPF5OzCiZEWdujZm6a4p3bsc/oe6l0d36IenuYwz2nN7le/ZNzXnj3eZNRVRK0q/PdUcNlHLKQ6r1ZvAVJAIVmqKUfE%2BZ9KDT1RQEf%2BBKnJmGQ1wfyGhUJYs/QvTgCCkEQcviAa%2B5DQGGSfv4Qy6GnKhU/v4JVX6Mrkt%2BtPXqWGBFQvw%2BrdIzhJBAA%3D)

By turning `(not Pred_0<***>::value)` and `(not Pred_1<***>::valu)e` into concepts, we allow compilers to perform proper subsumption.

```C++
/**** fun ****/
template<typename...Args>
requires Deceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires Deceive<Pred_0, Args...> && Deceive<Pred_1, Args...>
constexpr bool fun(){return true;}

/**** Test ****/
static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<template<auto...> class Predicate, typename...Elements>
concept Deceive = not Predicate<Elements::value...>::value;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgkv6kAA6oCoRODB7evgFBaRmOAmER0SxxCUm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJM/jcwNBr0wELcTC8RAAdKiIdhrsgDAoFNdlMRMPhRMDSNcCABPFKMViYVHI7BPRgEBTowFoBgbFIEa4AEUwGzwADdMNcITzrgxUNz8YS8MS4ZCGSCmQoQCBBWIvLS0f5sGqNd4FVYLoDvr8TqaDtcACqYMa4j6W82Ok1fK0y9AAfQ07wtF2hj1h8MRKJ12EBY2IXgceIJXo0gJMAHZjedrunrjNHMhMQIxphVCliNcYqhPNcDVrRSmqGIlMmeRDUw2m4m3TcPZ6uL69v8A2CFQikag6ayLpHo9K413EynARnM01s7mGPnC8XS%2BXKyLkxZa7R60nG/5m0fW67LlaAGpMck9nZ9kGB8GQkOoO5j84TmM38mz1MLlmcormuRbXG%2BFaajuKa3C2J6zsezbtns1xUF4DD3o%2BMIvlClLUmwdLnMQwAsrqgIEgAjl4eAErifICsK8KdkE1xESRo5kRc7KgRuZa0Kh6EQIsu4EgQawYfu9bwWeF79kGkIUlSzAEaibGkeGFyUdRtG8vymBCoOzGkmpHEYuYABsFm6QxhnTlwxnEQoplsnmwLriWfECQwQkiZgYnEBhBBRkaLYXmaNp2tyLpfkucqekwOLxAQ1DofCv7wlwrK6kJwknhwyy0JwACsvB%2BBwWikKgnBuNY1iZqs6w7mY/g8KQBCaPlywANYgEV5nIgAHOZUhFUm5mSAAnP4Y3NfonCSLwLASBoQRlRVVUcLwqpBO15X5aQcCwDAiAgKsBApEi5CUGgDx0PEkQ0pwqhDQAtON1zAMgOZSMiZi8LKRDEHg6B6PwggiGI7BSDIgiKCo6h7aQuj2QA7sQTApJwPAFcVpUdZVnAAPJIhd3KoFQ1zPeZb2SB9X3XD9ZjXBAHi3fQxbmC1iy8LtWjLBASA3Skd1kBQEBCyLIDAFIZh8HQwLEKqEAxPjMThM05JY7wavMMQ5KEzE2j8rtrU3c8BCEwwtCa4jWAxF4wAIrQB5a6QWAsIYwDiLbNHGwZqqIwW/JIpsrXhMChWI7QeAxOjeseFg%2BNBXgS3cLwwrEKWSh8h7RjR0YHXLFQBgkVeeCYCjhNKa7YPCKI4jQ7XcNqPjyP6J7KC1ZY%2Bgx6qkDLKgXJZAHL1jOgYqmJY1hmOtGdA1gfdCV0fvOBAriTH49mhOEgwVMM9mFJkAgb3oh/1HMQwJPZdgrw04ytJ47R6DfDg9PfF971ftj3yf1/vzv8x97LAUA1DYEgcYcBKqQNavANqU1eu9T631JC/WZrgQgJBRTNS4NzNqhdlgIEwEwLACQl49SSMiKaSZJAaEkGYSQ5kVp9QmnNDgC1SBLX8GYZE/hzJJgGv4AaRUipcGmhNAa0D8YbS2iAHahcDrHQFqdEml0xYS3Zg9NgT0EG0yxJ7BmE1kRcGRBVAGJBgag1kBDBu0gm5KBbojXQss0YYy1hAqBMCCYcGJudJE1xybwOpu9PRRgDFGJMczVmwt2ZYK4bg3m%2B0lHqPiFdcWqA2bDBCdLCaXAgg0FoArJWKtEY6w1q7UpesDZGwcK7M2TJLbW3xnbB2TsXZpzdiCT23sKr4AJK/YUAdTGqGDsCV24daj42jrHDWCdNgVWTqnVqGcs6YBzl08IoA9pFxLgoMuFcq6MBrlY%2BuUNbGyGbgjCqTj24F0nlYbuUzF4DyHnmTgo8CDj38DyO509Z7xHnnaeAwDai3xcAwdwj88hb3BR/BYB90hH2yJCzeqQEXnwAZfZ%2BILX4CF6BMZFWLui4v/mUTFf8%2Bi/2/rMDFn9wErDWGAnBrCPFSM4IEmmmIDChK4IY4xPoIDoMBrEnBPN8GkEIcQ4YZDlpBEjuwzhRVkSTSKhNMwqqzDmQGqI8akjEbSNsLIvBWyFHwCUWdUmqTknEE0ZsZoLB3osAUIKHMgoeXIgHGMf6%2BBAYWPsrXaxpyYbyHsZcnQARSAuMxmndxeM9VExUWTCmqgHVOpdW6j13IWbpOifEWJ/h4nyKSdmkWlri3s3VMgFIKRPSuomp6DNnpk22PlvEIpqt1Z63KR2/Whtja1PSebBpNsemYHto7MQbTWruy6XM3gvS/YDPxkHZAIcxmCAmVHGOcdySzKTkDRZ6d4grLWXnDZ8ji5MFLuXSu1d2n%2BpORIM5sMQ2t3DVy4wXcbCPKBZVF5q5OBbDHp3KelgZ6wLnsDQF/dl44r8GvcFlLt6ktpfCooWRKVnyyLC/eMH6h4ofrkFFL88Mkt3nCql%2BLCPP1I4Aq%2BwDQFQxjbq9abKm3XEdc6is6bYRjDQd6zBnMRVGr5gQohJDKAQPlQEbh2rmpmHk1wAaGhzIquY7AzgMi5FbO6iMIxgiip0P8EVZTzUxqsP8LGljm1hOdVYX9NTXjRXadIBnDIzhJBAA%3D%3D%3D)

## Links

- [Source code](../../../../conceptrodon/pagelivore/concepts/deceive.hpp)
- [Unit test](../../../../tests/unit/concepts/pagelivore/deceive.test.hpp)
- [Example](../../../code/facilities/concepts/pagelivore/deceive/implementation.hpp)
