<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# Hello World

Let us examine `boost::mp11::mp_bind_front`.

```C++
template<template<class...> class F, class... T>
struct mp_bind_front
{
    template<class... U>
    // `mp_defer<F, T..., U...>` will instantiate `F` by `T..., U...`.
    using fn = typename mp_defer<F, T..., U...>::type;
};
```

To summarize, `boost::mp11::mp_bind_front` accepts an operation and a list of elements.
Then, it returns a metafunction.
When invoked, the metafunction extends the back end of the previously provided list with its arguments and instantiates the operation with the result.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation
<
    mp_value<0>,
    mp_value<1>,
    mp_value<2>,
    mp_value<3>
>;

template<typename...Args>
using Metafunction = mp_bind_front
<
    Operation,
    mp_value<0>,
    mp_value<1>
>
::fn<Args...>;

using Result = Metafunction
<
    mp_value<2>,
    mp_value<3>
>;

static_assert(std::same_as<Result, SupposedResult>);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgOykrgAyeAyYAHI%2BAEaYxBIAzKQADqgKhE4MHt6%2BASlpGQKh4VEssfFcSXaYDplCBEzEBNk%2BflyB1bUC9Y0ExZExcYm2DU0tue0jvf2l5YkAlLaoXsTI7BzmCWHI3lgA1OZm0ahpBAD0LMlcXAB0CMnJhyYaAILPL17pRnvMbArJTDWe2OpxMCSsr0%2BYWAP1YmH%2BgMwe0u1zBELerwImEuBixYLcBAAnslGHCbuSwdh3goCMQvA49gB5EnEJiOARo97vKHfIReB5pTDoABK8K8tAIBwSABEmSy2ZkuQk3O89mrkckAPoANzEXkw%2BI0lNIqvVlx1eoNyq4xtNavNuu8VrcZltr3VGotTvxCUpSqp4K5mOxyVxzqJJN%2BmHJNxexGACj9kK%2BMIAspgGlQvAwugwpbLzdEwuhNVRiLIlSr3ermXEFQITdX7VrHfrDW6Xh6HZb8TaElTXkmXiAQFQGPi4wmY37A4Pk9C9qKFOLJWDZenM9nc5W7Z7W87Xf3G52zS2e8rff3/Zy5y8aQrkJqmAolE0IDT0COFHCn4nlUuV1IPY%2BQFJQRTFCVKXmNEOEWWhOAAVl4PwOC0UhUE4FVLGsPYFGWVYkU2HhSAITRYMWABrEAEI0G4EISAAOMxJAYgBODR/AANlYhCuAY6R4I4SReBYCQNA0UgULQjCOF4BQQAk0jUNg0g4FgGBEBAZYCGSLwCHISg0EuOg4giOFOFUBjOIAWk4yQ9mAZBkD2KQbjMXghUIEg8E/LgZEEEQxHYKR/PkJQ1DI0hdD8gB3Vlkk4Hg4MQ5DIpkxk9N0yVUCoPZLJsuyHKclzJDcvYIA8Yz6GIA4zASLh5l4JStEWCAkCM5ITLICgIA6rqQGAKQzD4OgsWIeSIGiSKi2YYhCUS3gZsaQlGWibQaiU4ijLYQRGQYWh5uU0gsGiLxgDcMRaHk7heCwFhDGAcQjvwYgNrwbV4UizBVBqPT1mIsIsUEtDaDwaJWTmjwsEi2k8FEm7SA%2B4hjiUaVsQe0GjDIxYqAMBMADU8EwGLaxQ4j%2BAC0RxBCimwpUdQjui/QHpQaxrH0MH5NgKMQBBGlEaGbgrPI9DknZBhrusj811MbDLDMaSkeIHzPsgRZOnFlwGHcTxWj0EIwgGMohj81J0nF8Y2nyc3MhmQYKlsTB7HFnoxl1iZHedupRj6Q3ZhNqY3ZyK37yaO3jYqdX8LWCRko4JDJLSzg8qs2z7Mc5zXLMcrcC8mqiMakjscWBBMCYLB4ggSiQEkBIblYhJ/EkDRJGYzjxIQ7j9E4YTSFEyRWLoswEPYuyG8YhJOMCKTeBkuSFKL5TWo0tqtMyvSDN61AqtM8yOEaFhtX8aymD2HYHpcwfbjQzyiGV3zQsC6npFpxR6ci3RhripgEpuuOE5nuhTgGUdJ6T2DlFOBV7Ln2%2BFwK%2BNwNDlUqp1aqtUEhmELs1FSq8%2BrVU3rgoYMDBqsS4BJGgEo4gTSmkdJac0FqkFoStNaG16HbUYAQPaB1IonTOhdWgV16F3QxusNCL03ofWujfH6yA/r0MBk7SKoNwbLShiIpqyt4bESRijTAaN7pGExqAJefA8YKEJsTUm9DaZP2Ci/WQb8IqMxAMNAwWNZZWEsBzaIXMoA8z5vpJGiVhbzEWKgMWmRJbSxlO46wCtZ5KxVj49WTs3rOAgK4S2%2BttbhzmKbAoFt3ZWzNoUBgOSA4a29r0TJfkKndB9mUh2odmiFL0E0hpsclgrBjg1bu8dUpHRkpAtOZ9XEwjgTca%2BOd8B3zQQ1JqxdSCl3LkMKuvTe6iRojcSQTcNANxopxTiXBOIJE7onAZnB56KQWVRAeWzDn%2BF4rsuqLcGJJEEgkfp0kLmLxanHdyZyvmyR%2BSLJG6RnCSCAA%3D)

From the template head of `boost::mp11::mp_bind_front`, we can see that one kind of metafunction gets special treatment, namely, the metafunctions acceptable as template arguments for `template<typename...> class`.

Now, let us check out `boost::mp11::mp_fold_q`, a valid operation to pass to `boost::mp11::mp_bind_front`.

```C++
template<class L, class V, class Q>
using mp_fold_q = mp_fold<L, V, Q::template fn>;
```

`boost::mp11::mp_fold_q` accepts a packed container `L`, an initiator `V`, and a quoted metafunction `Q`. Then, it left-folds elements in `L` using `Q::fn` and the initiator `V`.

<pre><code>   L&lt;E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>n</sub>&gt;, V, Q
-> Q::fn&lt;
   Q::fn&lt;
        &vellip;
   Q::fn&lt;
   Q::fn&lt;
       V, E<sub>0</sub>
   &gt;, E<sub>1</sub>
   &gt;, E<sub>2</sub>
      &vellip;
   &gt;, E<sub>n</sub>
   &gt;</code></pre>

With the help of `boost::mp11::mp_bind_front`, we can fix the packed container `L`, and obtain a metafunction that requires only the initiator `V` and the quoted metafunction `Q`; or fix the packed container `L` and the initiator `V` and obtain a metafunction that requires only the quoted metafunction `Q`.

```C++
struct Subtract
{
    template<typename A, typename B>
    using fn = mp_value<A::value - B::value>;
};

using V = mp_value<1>;

using Arg_0 = mp_value<3>;
using Arg_1 = mp_value<4>;
using Arg_2 = mp_value<3>;

using L = mp_list<mp_value<3>, mp_value<4>, mp_value<3>>;

template<typename...Args>
using BindL = mp_bind_front<mp_fold_q, L>
::fn<Args...>;

template<typename...Args>
using BindLV = mp_bind_front<mp_fold_q, L, V>
::fn<Args...>;

static_assert(std::same_as<
    BindL<V, Subtract>,
    mp_fold_q<L, V, Subtract>
>);

static_assert(std::same_as<
    BindLV<Subtract>,
    mp_fold_q<L, V, Subtract>
>);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArKQADqgKhE4MHt6%2BekkpjgJBIeEsUTHxdpgOaUIETMQEGT5%2BXLaY9nkM1bUEBWGR0XG2NXUNWc0KQ93BvcX9sQCUtqhexMjsHOYAzMHI3lgA1OZmEajJBAD0LAlcXAB0CAkJhyYaAILPL14pRnvMbAoJTFWe2OpxMGysr0%2BwWAP1YmH%2BgMwe0u1zBELer3GxC8Dj2Qi8EQIxEBBHeJgA7Oi9tS9gRMJcDHSwW4CABPBKMOF7F6kWnszlsPZWDbYd40vZQ75UBgHDYAEWRCQA%2BgA3MReTDMl4gEBq7xIgC0Qp1eo1YNF4LJ5LlaLJkK%2BMIAarKFZdVerNRs3FxzbbXu9JTCXsRgEqNC7Fe79cyNr7LfbodyQ0quBG3abPW5JHH0YGk6GzGnlRmYzm7R8HXsAkWlbQ8ONmemPaWRbym9GvdnW5GS17YyKy/7XnSGUwmV62RzfpgbrPg8AFL6E98LMF0NWwa7lRE10qqMRZI3lfxaOglQBHXkBJfakDSrUhhSzm6DjEvEcJRmZycCmdzx83nmq4MOuzqbpGO4gXuB6CEee6eGel5Vryjo3jq95evOT6zq%2B7zjGOeDIEqTAKEodQQOM6A6gocLEYuXpijSwHrsyjq8vihLEg45qkIx1JuieiHMgEKHsQSRIkje5pzH6b74Y4REkWRBAUQQVEgDRbB0cyfFCmuASoV6HESdxra6QJCEXsJol4uJXGkgO/oijJ4IcAstCcLEvB%2BBwWikKgnBuNY1h7AoSwrEimw8KQBCaG5CwANZxBoNyxBsAAcZiSOlACcGjkgAbDlsRcOl0geRwki8CwEgaBopA%2BX5AUcLwCggPVsW%2BW5pBwLAMCICASwEAkXgEOQlBoJcdDRKEcKcKo6UFQaBWSHswDIMgexSDcZi8Jg%2BBEMQeBUc0/CCCIYjsFIMiCIoKjqF1pC6M0ADuxIJJwPDuZ53lxf5nAAPKjSNBB7KgVB7AtS0rWtG1bZIO17BAHhTfQxAHGYGxcHMvCdVoCwQEgk0JNNZAUBAxOkyAwBSGYfB0HSxBtRAER/ZBtSsp9vDs8QrIAxE2gVJ10WTWwggAwwtCc49WARF4wBuGItBtdwvBYCwhjAOIMt4MQQt4Cq8J/ZgqgVKNazRcEdIVX5dYRMSvMeFgf1EngNWq6QhvEMcShyvSmt1kYcULFQBgLo6eCYC9ANTlzN3CKI4jXWd8hKGof3PfomsoMFlj6HgERtbA04gCC4ye/03CLfF/kJO0KsGpRm6mJY1hmE1XtHVgRcQAs5SVM4ECuCMTSkIEUxFCU2TJKkAgj9PuRpD0k/9GMrT6wInTDJ4jR6P37Rb5MhR9DEYwTPPZ9dMvJ8SH34WrLf%2Bg/Q1f3NZDi3Lat62bdthYQLghASAYyxjjGKwcFgIEwEwLAMRe6kCSpIDYNwcobHJJIDQkgsoFTqrEIqT9KrVRAJIHKqUzCxDyitFBGUNgFXJC/R6zVWrtTAV1Am/VCaDWBqNcaFNUCoxmnNDgtQWAqnJAaJgewdiay2iQ24fl9qAK7noFOF0k7SBTnddOj1dB0zekwD6qtvocC8vQpqgMuGg3Bu/aGq0pHfC4LIm44ZkZ8JJmjYBZhQF426hwymaMeF%2BP6HYmmOUuD1RoLQRmzNWaPR5tLaKcT%2BaCwcHHUWjACASyln9WW8tFa0GVnHdWAc1h%2BXwHrSohsVbyNNsgc2ccratD%2BnbB2rInYlNxkdd20UvY%2B0wH7DWRhA6gFYXwMOCgI5RxjowOOKjE5XXUbITRD0/I6KzkHFuVg852x7hAEuZcxpe0%2BtXOYCxUB1zSA3Ju8oNltw7tELuRtIB93XgPPwQ8QIXzHiBa%2BMxT6JBnu0T5ORZ4MB%2BVPNebQqjnx3qMFokLN4TDBavQYXRPn4TqEi0%2Bd9lgP2xvgkxjVeBvyhp/SRBh7GOOcQAw6wDsa43AaQSB0D%2BhwIqlVUgNVYgpUkGgjQKCuUFQKlwAqGxcGmKJZwJhHUGUIJIZIIV5ISp8sxhg9KGx8EbF%2BgwyVLD8ZGN2uK/6LVdU1y9ikZwkggA%3D%3D%3D)

But is this what we want?
Isn't fixing the first several elements inside `L` more interesting than fixing the whole thing?
`boost::mp11` has a function to do just that. Introducing `boost::mp11::mp_bind`, a quoted metafunction that implements the type-based equivalent of `std::bind`.

```C++
template<typename...Args>
using Bind = mp_bind
<
    mp_fold_q,
    mp_bind<mp_list, Arg_0, Arg_1, _3>,
    _1,
    _2
>
::fn<Args...>;

static_assert(std::same_as<
    Bind<V, Subtract, Arg_2>,
    mp_fold_q<L, V, Subtract>
>);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIaa4AMngMmAByPgBGmMQgAMxxpAAOqAqETgwe3r56KWmOAsGhESzRsWYatpj2BQxCBEzEBFk%2BftJ2mA4Z9Y0EReFRMfGJCg1NLTlctmN9IQOlQxUAlLaoXsTI7BzmcSHI3lgA1OZmkaipBAD0LElcXAB0CElJJyYaAIJv715pRofMbAUSSYm0OZwuJjiVg%2BPxCwH%2BrEwQJBmEONzukOhnw%2Bo2IXgchyEXkiBGIIIIXxMAHYsYc6YcCJgbgZGZC3AQAJ5JRiIw7vUgMrk8tiHKxxbBfemHWF/KgMY5xAAiaKSAH0AG5iLyYNnvEAgTXeVEAWlF%2BsN2shEqhlKpisxlJhv3hADUFcqbhqtTq4m4uFaHR8vjL4e9iMBVRp3SqvUa2XEAzanXC%2BeHVVxo56LT63JJE1iQ6mI2ZM2rs/H847vs7DoFS6raHhRmys96K%2BKBa24768x2Y%2BXfQnxZWgx9GcymKzfZzuQDMPcF2HgAoA8m/hYQuh65FN5TfZL6Z7%2BLR0KqAI6kA90z07hjoFtqxujAVLyMvtNTQ6qofYS8fKXpn%2B7wAWYe4Sh8%2Bpyrq4YKAu9wjti7yjJOeDIKqTAKEoTQQKM6D6goiLoSu%2B7/vSG53myLoCkSJJkg477FlaQFSkeninmebKBAKVGEsSpLkqunziksmIcCstCcAArLwfgcFopCoJwbjWNYhwKGsGyojsPCkAQmhiSsADWICSRo9ySXEAAcZiSJZACcGhUgAbHZklcJZ0gSRwki8CwEgaJUsnyYpHC8AoICVHpcliaQcCwDAiAgGsBBJF4BDkJQaA3HQMRhIinCqJZTnGk5kiHMAyDIIcUj3GYvCYPgRDEHgeFTPwggiGI7BSDIgiKCo6jRaQuhTAA7mSSScDw4lSTJ%2BkKZwADyaWpQQhyoFQhyFcVpXlZV1WSLVhwQB42X0MQxxmHEXBLLwUVaCsEBIFlSQ5WQFAQC9b0gMAUhmHwdCMsQ4UQJE823o0HJTbwEPEByi2RNonRRTpWVsIIi0MLQUNDVgkReMAbhiLQ4XcLwWAsIYwDiLjeDEMjeDqki82YKonRpVsOkhIyXnyY2kRknDHhYPNpJ4H5ZOkEzxBnEoipMlTjZGPpKxUAYy4ungmCjYts7Q71wiiOIPXtfIShqPNI36FTKAqZY%2Bh4JE4WwHOIDgs%2B0tTUVBkKUktSk8auGQoqpiWNYFS8Kg0vNVgzsQCsHRdM4ECuBMfhTEEcwlGUuSpOkAhp7n%2BQZP02dDFMie1D04yeK0eiV90Myl4MsQVzMhdt70zcLK3CcaZsEgzRw0mkEFkecFtRUlWVFVVTVJYQLghAkJd123bpKsrAgmBMFgsTx6QxmSHE9x2XEVKSBokg2U5AWSS5%2BicD5pB%2BZIdnmWYkkOaVZ9WXETlUlHvNEKYUIob2io9BKT0korTShlT6qAzq5XyhwRoLB1RUmNEwQ4%2BwqbVXfg8eSDVl4xz0KbTqxtpCm36hbIauh/rjSYJNMmQ8R5jwWhwZaKU0rrU2ttaeOCDB/C4AQ%2B4UYTqINeudVeZh173RitAr6514FKKGLgowIiuCVBoLQIGIMwZDVhjjHSRiEZIwcPrNGjACCY2xvNPGBMia0BJvrCmistjyXwPTLoTNSZELZsgDm%2BtubVHmvzQWHJhYeLus1CWOlpay0wPLSmRglagAgXwdWChNba11owfW5CjbdSobIGhg15L0OtsrUOVh7b8zjhAV27t0qe24N7JYKxUB%2BwyAHIOSoanh2CtHFqzNIAJ2qAzZOqda6TFIJnYoLci750yDM9OyQ861G7jnCuEyk51Hbqs%2Buuyq5NyzoszuNdshrOQk0LZ5c%2B7rAHjdR%2Bw85pDRCpPHaZV1HwhEfcQhx0l5NVXjdO6m9SDb13kMA%2BXln5%2BVMvcSQF8NBn1Mk5JyXAnJxHvkA95nBQGRXBUfd%2BkgMVUjciiq6V9LKJC8nEN5wV8XgIekPOquLGWhWZT7aWaRnCSCAA)

`boost::mp11::mp_bind` works creatively.
Not only does it replace the placeholders in its argument list, but it also detects the `binding` structure in its arguments and replaces their placeholders accordingly.
The result, however, is slightly arcane.
Moreover, since each placeholder indicates a single item in a list, the function cannot express the rest of the arguments using a pack expansion.
Therefore, we must decide beforehand the total number of the required arguments for the target operation, even if the operation is variadic.

Overall, I'd like the composition to be more intuitive and the technique shall be consistent throughout the library.
The reason why we find it difficult to handle the target list in `boost::mp11::mp_fold_q` is that the list is sealed inside the container `L`.
`boost::mp11` introduced the idea of 'quoted metafunctions'
Why don't we expose the target list using a member template, turning `boost::mp11::mp_fold_q` into a quoted metafunction?

```C++
template<typename V, typename Q>
struct QuotedFoldQ
{
    template<typename...Args>
    using fn = mp_fold_q<mp_list<Args...>, V, Q>;
};

template<typename...Args>
using BindFrontQuoted = mp_bind_front
<
    QuotedFoldQ<V, Subtract>::fn,
    Arg_0, Arg_1
>
::fn<Args...>;

static_assert(std::same_as<
    BindFrontQuoted<Arg_2>,
    mp_fold_q<L, V, Subtract>
>);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwapK4AMngMmAByPgBGmMQgZv6kAA6oCoRODB7evgFBaRmOAmER0SxxCUm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHOb%2B4cjeWADU5mYxqOkEAPQsKVxcAHQIKSnHJhoAgq9vXhlGB8xsChSTA2B1O5xM/is72%2B4WAf1YmEBwMwB2utwhUI%2B7zGxC8DgOQi8MQIxGBBE%2BJgA7JiDrSDgRMNcDAyIW4CABPFKMBEHN6kemc7lsA5WfzYT50g4w35UBhHfwAEVRKQA%2BgA3MReTCst4gEAa7wogC0Ir1Bq1EPFkIplIVGIp0J%2BcIAavKldd1Zrtf43FxLfb3p9pXC3sRgCqNG7lZ7Daz/P7rY7YbywyquFGPebvW5JAnMcGU%2BGzBnVVm43mHV8nQcQiWVbQ8GNWZmveWxfyW7Gfbn29Gyz742KK4H3gymUwWT6OVz/ijnfzp0KUQBFf3Ykl4ggHZdeVAM9AAMU86FXgepErpY5SzOzi9ndwfoeACjXb0lBdldf4tHQKoAjs2qoNk2PpPgoD53Ja/Lztuw4fLaAZYm8V43qyd4IhBYGvgWFjhIexCyDue6YOgdYxHhKpUARggUj6F60kR%2B5Hj%2Bq4%2BjBhLEqSDiWnqsqkPRhYRvyT5prR4rvLxDA6mG4EPnBnwzI4yAqkwChKC0EBjOgeoKAiKkvnR7ySrhDD4YRu77tJRZQQJHrfr%2BAE%2BiE0H8hxJJkq%2BlqLBiHDLLQnAAKy8H4HBaKQqCcG41jWAcCirOsKLbDwpAEJovnLAA1iAAUaHcAX%2BAAHGYkgFQAnBolIAGylQFXAFdI/kcJIvAsBIGhBCFYURRwvAKCAQSpaFvmkHAsAwIgICrAQKReAQ5CUGg1x0PEkQIpwqgFZVRqVZIBzAMgyAHFIdxmLwJGECQeDaVwMiCCIYjsFIt3yEoahpaQug3QA7qSKScDwfmBcF73dQA8rNM1bqgVAHBtW07XtB1HZIJ0HBAHhLfQxBHEkXCLLwg1aMsEBIItKTLWQFAQGTFMgMAUhmHwdAMsQfUQDE73kcwxDsv9vBc807KgzE2iYA4fOkItbCCKDDC0LzQ2kFgMReMAbhiLQfXcLwWAsIYwDiIr%2BDEGLjhqoi72YKoYuzZsyXhAyjVhQ2MSkjzHhYO9JJ4K12ukObxCnEoCqMvrDZGGlyxUAYz7OngmBfaDM4S/wd2iOIT2py9KjqIrn36PrKDRZY%2Bh4DEfWwLOIBgmM/vDNwm3peFKT1FrRpaRCCqmJY1hmF1AfEFdFuQMsdim1kLimZMfg3aE4SDBUww3YUmQCNPegr/UcxDAkN1jw4PTjK0njtHo%2B/1L0LTb4vu%2B2Ef6970f18LHjKxrBsEiAxwQWkJ1vDdbDTa21dr7UOsdYsEBcAXWxklfGKVI7LAQJgJgWAEgQEyiASQ/g7ilX8JSSQGhJDFUqu1AK1V9CcGaqQVqkhSp5TMAFcqO1cGFX8JVSkv8QacF6v1eBQ1ibjRJpNCGs15rU1QJjFaa0ODNBYGqSkRomAHD2PrI6dD7hhXOkQQe11nr3QztILOigc7vV0IzH6TA/ray/j/P%2B4VODg2mrNA40NAHw12io34XB1F3EjOjCR5MsY438GYOBhNhpCJpljMRUThiePpqVLgQQaC0BZmzDmisBY8wllkoWItTYSylowAgst5bvWVqrdWtBNYS11mHTYYVjbj3NlrTR1tkC2wlg7Wo70XZu3ZB7BpBNB6%2B2SgHIOmAQ56yMOHUA/C%2BAxwUHHBOSdGAp1kPox6hjZDGLennRIBcI7dysCXF2FcoBVxrnNAO/1G6LGWKgFuWQ24d0VMc3u/d4g6OHugro49nAQFcA/YIpln5L1SOkVe2QT55GXpCre895jgvPofPowKUUCEvv0RFO8z73xhTPO%2BswcU30/m/BKZLGq2K4RwNxwDlEGC8T4vxUDtHBLxgTBBpAkEoOGL8xqVDWo5TuJIfBGhcE5UqpVLglV/BkM4YrbqPCBpcqyrQkV0rKS1XFUkQhBVkiNX8MDRV3C%2BFEy/qdBVXVTXhPuXXVmE9JBAA%3D%3D%3D)
