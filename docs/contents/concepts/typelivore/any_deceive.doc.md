<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AnyDeceive`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-2">To Index</a></p>

## Description

`Typelivore::AnyDeceive` accepts a callable type predicate and a list of elements.
It returns true if there exists an element whose value result fails the predicate and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> (...||(not Predicate{}(Elements::value)))</code></pre>

## Structure

```C++
template<typename, typename...>
concept AnyDeceive = REQUIREMENT;
```

## Examples

`AnyDeceive` turns a fold expression of a callable type predicate over `||` into a concept so that it can be used for subsumption.

The following code will fail since `(...||(not Pred_0{}(*)))` and `(...||(not Pred_0{}(*))) && (...||(not Pred_1{}(*)))` are both atomic:

```C++
using Pred_0 = decltype([](auto...){return false;});

using Pred_1 = decltype([](auto...){return false;});

template<auto I>
struct Monotony
{
    static constexpr auto value {I};
};

template<typename...Args>
requires (...||(not Pred_0{}(Args::value)))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...||(not Pred_0{}(Args::value))) && (...||(not Pred_1{}(Args::value)))
constexpr bool fun(){return true;}

static_assert(fun<Monotony<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEEgCcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BxemUYA1MrEmOgA%2BhqHJv4AIodYyLQEAJ6pmBAmgVaBtxBMXiIADoQasTAB2CynAhbBiHKhiJQ3Kzg25g/xWDQAQRM2P2EWAx1OFy41zuD3qzzeHy%2BPz%2BAOBoIhUMwMOIcIRtCRGIhaORuJx2IImBYqQMwpubgZqEOAEkbtgBXNiF4HIcALICVBEBgvAXMgWHI2HOZMRzIQ5oBhzTCqVLEQ7Sw4ANzEXkw10h8tR/OxvN9gqxwtF4swkte72YbBBQKxxGACgVAtOAEcvHhTgpDhAYxC3HmIAxtUSzpcDaiIHGEyAQK7vJhVo2BVabXaHbFUJ54V4GBAwZDobD4YiwzyfX6hSKxWbR24I4xWJgY1XE/5FdjU%2BnMzmQXmC0WCCWLhpy38VzW6%2B7G6trmYAGzmO/Z3Pg/OvwvFk6lrinyvxhQXm6DZNtiLbCm2hwdl2VA9n2zKDuyhwECqo4orc%2BrYqa5rnEwChKK01A9pKmoHgIer%2BG4P5rgqfbohYHDrLQnCBLwfgcFopCoJw%2BaWNYJqbNsHrmP4PCkAQmgMesADWICBHeQIABx3lIgTgnekhJP4almP4%2BicJIvAsBIGgaKQbEcVxHC8ABpniexDGkHAsAwIgICbAQqSAuQlBoKKdAJFEi6cKoSkALTqYcwDIBaUhAmYvBnIQJB4Ogej8IIIhiOwUgyIIigqOo9mkLoXCkAA7sQTCpJwPCMcxrESZxnAAPKAp5h6oFQhwhXe4WSJF0WHLFZjZh4fn0A6wlcKsvB2Vo6wQEgvmpP5ZAUBAy2rSAwBSGYfB0MKxAARAsSNbEEQtC8NW8OdzDEC8zWxNo9R2aJvlsIIzUMLQV1FVgsReMAUq0Fy12kFgLCGMA4h/RmL14M6mAAUVtr1ICuyiREwpMUVtB4LElX3R4WCNcheBGdwvCI8QHZKLcIpQ3jRgSesVAGAmABqeCYGVzWRmD6XCKI4g5YL%2BVqI1JX6FDKDWNY%2Bj4wBkDrKgqR9MjoVzOgNy3KYvGWGYFnU8QKVI/A6x1A0zgQK40x%2BKVYSLBUVR6EUWQCHbrsZO7DDDM7KzdL0jTzJ7pWW30AytH7ozVBMgyh3HUdOzHEgWwJOyp3pHAsWZjWWd1YURVFMWSHF2a4Elk06dNs0s%2BsCCYEwWCJH2pAyZI/hApp4KSBokhmJId4mXJKQ4wZpBGSJQLKXeClJApXB3oEkhcIEml3rnRWWdZIC2SzjkuYtbltV562bRNgVsJwLQsM64KhUwloGEcNRAlwQIcYlRAm6lpWC5lItpBiyUBLIqug9oVSqtdOq2cGpbxaifDqXUb53wfk/KGQ0khvw/qNVA40Ei3n8GYGaYl95H3PgkbyG08ErQmiAFB98nhQxqFwUyNBngJGOqdIqt1Lpg14fdR6z0HBg3eowAgX0fqNX%2BoDYGoNKbgwZkYGGHF8CnAaIjZGn9VBo2FGDLGPRGp4wJpdYmuwOJkwpqJamtNMD00hsogk%2B82ZME5tzXm/MFH/2FtlIBshxaFQ4uA6WzM9ZWEsArWIStW6q3VpwTWBBtZ3DCdYQ2vBUDG1NtEi2PR4bW1tp4DoehHblBTqVN2fQE4VOyNHZYsdw7B3joU/IYdclW36PMWpLsw4h2afbROCxSl1MzgodO2UYE53MukzgjpiC33vo/JhL8sHvyuBACu39CE11IfZRspAG5NzGK3MehkAhYL7uCNe4JwT%2BH7oPFem8LKcB3nvXZB94BH3cu1KhFDiCX12DfCKLAFDOgtM6V%2BoY5gJXwN/FKaVZAAN8bleQIDAk6ACOVSq1VKYTLgU8jgrUPKAkOJ1WZLAgUgrBRCmccxcH4Krv4fwJC5oOXITQ1aPz2V0NBakVI5xwVJHOJCggOE5nqX2hwo6lBuEcQEb9UScqhEvVEXgj6Ejvq/VUZgAGQMxDyNEhDRm5jeBqPhpoxqqNkDo30YIQxuN8aExeGY0mJsrFUwSLY%2BxjMnFvJcW4nmfNGACwRT4iQfi8qoslhi5%2Bxg5YROMdkziatsjIwAPRa1lvrCwaTOKZKwImhp%2BSGDuD6cU4tXSA7VI9qW8p3s%2BgVvqW0iOvS8j9MLR0wYDa9CmimDWgZXbpobC2BnQdONJl5xmYC/qwLQUumpcKWl6yYUkC2cyuu%2BzG7N0oDA8eRkzBYMZYEQIfdWEaEZWpBSjzplWVsLvHZ81pIgA7m/fwCll46WPXeHSaks7%2BDxde2uuyYHxSvU1G9LK9nU0yM4SQQA%3D%3D%3D)

By turning `(...||(not Pred_0(*)))` and `(...||(not Pred_1(*)))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires AnyDeceive<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyDeceive<Pred_0, Args...> && AnyDeceive<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Monotony<1>>());
```

## Implementation

```C++
template<typename Predicate, typename...Elements>
concept AnyDeceive = (...||(not Predicate{}(Elements::value)));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGzSrgAyeAyYAHI%2BAEaYxCBmpAAOqAqETgwe3r4B0ilpjgKh4VEssfGJdpgOGUIETMQEWT5%2BgbaY9oUMdQ0ExZExcQm29Y3NOW0Ko31hA2VDZgCUtqhexMjsHASYLEkG2yYAzG4EAJ5JjKyYANTKxJj4otuk12cXzGwAdN/Y9GyCCiO2BMGgAgmgGBskgRrqCGKcACLVTB4ABuNyOCOuEG%2BnxMAHY3AS3BAGKgYXcHngnpgCVZ8QiIL8dowCAoQCBUWIvJhFnyjlYwSDQQB6ABUEslUulIuF4sl1wAKpgpgprlLZWD5dKdRLNaDhV40kZbvd0AB9DTXTHXLDIWhvTAQEwAVisLsZTC8RFxizp9wIawY1yoYiUAoJCL9h0FBrBRrCwFND3NXGthyxdod5ydrvdnu9qF9/swgeIwdDtHDMcj0djwu2u32tOOXqI1wAkkDhVNiF4HNcALICckCU7CunC67T65TJiOZDXCFTTCqJLEa5t1DXLneDH4ixdhkRoXHmtCsGNvbzlsnHMfTC40HEYCAw7AsH3ACOXjw9zVcKIsiaK3pSFoaC8z6vri3Zgsu2xrhu0SoJ4IZeAwEB%2BgeAZBiGYYtvSCITpeOzXgcxyOg%2BT4vm%2BH7PpgP5/iqsLwkiGwgUcbhgZakE0TB77WmY/jmP4LFAex6KcdxXC8dB3yweCAgroh1zIahVDoZhJZlsGBB9gRkbEaCc4LuaTAKEojTUOhnHDmSRDwpxXDdu%2BmF1hwyy0JwLq8H4HBaKQqCcESljWLOqzrBiZiHDwpAEJoHnLAA1iALqSJ8GiSFw%2BKHBoLoaEJ/hmAAHMV%2BicJIvAsBIGgQX5AVBRwvDshB8X%2BR5pBwLAMCICAqwEEk3rkJQaC7HQcQRFcnCqMV/gALSBNcwDIIuUifGYvBUkQxB4Ogej8IIIhiOwUgyIIigqOo7WkLoMkAO7EEwSScDwnneb5CWBZwADy3qDTCqBUNcM3zYty2relZjYh4Y30Bu5gxYsvBtVoywQEgo1JONZAUBAmPYyAwBSIkNAOnE7IQNEn3RGEDSnC9vA08wxCnN90TaNUbWxaN/wEN9DC0PT11YNEXjAG4YhVgzpBYCwhjAOIwtMTU6Lstdq7VN6myxWE2xeddtB4NEj0sx4WCfXpeDVdwvDosQyFKEictGIbRgJcsVAGK%2BABqeCYHd33vNLB3CKI4inSHF1qJ9t36PLKDWNY%2BhG%2BykDLKg0IZGrc1TOgmKmKFlhmA1ds7VgqeYe0nQZC4DDuJ4LR6CEsylOUej5OkAjjH4Mkd10/St0MMlVDUAg9GMDc5MPHSc7U0wD4M8TD9M3d6HOjQL/MS/LAoEUbBIb0cD5pD1bwjXA7NC2SEtK3XGtUNMvg22CYjyPu8sCCYEwWDxJXKWSIcT4ABOQ4%2BJJCZTMJIfwtUXT%2BCAeVDglVSDVRip8fwXB/DFSAcVDBaUuAuhAf4E%2Bn1GrNRAK1d2nUeroz6n9IauN8Zw0mmwTgDQWConxHNJgS4DAmi4EAz4XAMqbSfiQXa%2B1ZBHXDtISOSho7XV0IkB6T0GaH2PqfL6HBfoDW9NcQGm5iDsM4dw%2B08s74CKEVaCAMMsZwxfksN%2B7U0YY1QLDOIw08auNsUMNhHC5qmKMPwrgEFSbbGIBTKm10mZ02ltElmbMOYOGljzVk/NBafRFmLCWtApY2xljseWisAr4HuCrFUn0NbIC1tLXWHRPqG2NnTM2mwAqW2trFO2DtMBO0KYmShnsmA%2Bz9gHIOeSQ5SJOjI2QUcroBUUXHN2BcrCWGTtECu6dM5KU4DnAgecMxLOsMXM%2BpddrlLTlXWezgICuFXjJZuJRF7t1SJ3TIk8e7JGef3Fujzp7VzHivN5a8Z6j26PPb5W814AuyO89eMwHkQq4DvPeJ01EfWuufXxxieFmP4YIjK2JcCEBIC/RFjjUYfy/j/Sgh8kEoIEZlfEBD8Q5UkJAwIMkNGkNsOQuKlCuq9X6v9DxjCJpTQ4GwxaLAFCokXKiXFzYpgiKJWXCRh0w6TLOvIORsydAgEOKQZRz0baouIein6dCAZAwldfKVMqdzypvFMaGXjsYv0OEjXlTjOouLcTjEaLq4acmQEkJI5o5VAPNAqggZlDFtFCeTSgkSApxKFrFFNCTObJNcbzNJQtimYFFuLSWatYqy0KS03gJTZ6qwqaoTW2wamCDqQbI2JtTjNItjtdpts4hdJ6S7PpXqBlDP9oHRgwdJHqokFM862qY56oWcYROKyGnrMCpshgasRS5wToXCwRzAonPLvAHewKui13rtCpuddN5t17p8jItyPkFAyLeoeFyQXjyaIC35lzQW9DfUvEYvQn2wsAwfFYax96IoQeokhnADEsEldK2VDrthOsfsqklHqUaJVIJ/b%2BQxK761pQkARhxDgunyllWqFH8SYNNQ1TgZCKFOOSiASQLpgEumKkJIBkggE5VAVwfV%2BtDhoqY01T15KEEbUY2fZj0m8N2zSM4SQQA)

## Links

- [source code](../../../../conceptrodon/typelivore/concepts/any_deceive.hpp)
- [unit test](../../../../tests/unit/concepts/typelivore/any_deceive.test.hpp)
