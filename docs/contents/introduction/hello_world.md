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
Not only does it replace the placeholders in its argument list, but it also detects the 'binding' structures in its arguments and replaces their placeholders accordingly.
The result, however, is slightly arcane.
Moreover, since each placeholder indicates a single item in a list, the function cannot express the rest of the arguments using a pack expansion.
Therefore, we must decide beforehand the total number of the required arguments for the target operation, even if the operation is variadic.

Alternatively, we can use `boost::mp11::mp_compose` to inject the result of `boost::mp11::mp_bind_front` to `boost::mp11::mp_fold_q` with the help of `boost::mp::mp_bind_back`.

```C++
template<typename...Args>
using BindAlt = mp_compose
<
    mp_bind_front<mp_list, Arg_0, Arg_1>::fn,
    mp_bind_back<mp_fold_q, V, Subtract>::fn
>
::fn<Args...>;

static_assert(std::same_as<
    BindAlt<Arg_2>,
    mp_fold_q<L, V, Subtract>
>);

using Arg_3 = mp_value<2>;

using L_1 = mp_list<Arg_0, Arg_1, Arg_2, Arg_3>;

static_assert(std::same_as<
    BindAlt<Arg_2, Arg_3>,
    mp_fold_q<L_1, V, Subtract>
>);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISRqkrgAyeAyYAHI%2BAEaYxBIAHKQADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxXEl2mA6ZQgRMxATZPn4Btpj2RQwNTQQlkTFxibaNza25HQrjA2FD5SNVAJS2qF7EyOwc5gDMYcjeWADU5mbRqGkEAPQsyVxcAHQIyclnJhoAgh%2BfXulGx2YbAUySYW2OFyuJl2Vi%2BfzCwEBrEwILBmGOdwe0Nh3y%2BM2IXgcxyEXmiBGIYIIPxMAHYcccGccCJg7gZmdC3AQAJ7JRjI46fUhMnl8tjHKy7bA/RnHeEAqgMU67AAiGOSAH0AG5iLyYDmfEAgbXedEAWnFhuNuuhUph1Jpyux1Lh/0RADUlaq7lqdXrdm4uDanV8fnLEZ9iMB1RpPWqfSaObsg3aXQiBZH1VxY96rX63JJkziw%2Bmo2Zsxrc4nC87fq7jsFy%2BraHgZvqM4ES5mhRHS9WQ19maymOz/dzeUDMI8pz2FEHUwCLGF0J9aARG2g7mk9SH/dLGd7okv1VRiLIOd7mzNu%2B3r1HA5LDQrSHuGQej9EwQBrc8a/i0dDqgAjkKbpCiSZIUg4NqPgw1KSj8MFtsAChTo8fa4p8MzDngyDqkwChKM0EAzOghoKMieGzruXwyouDDLquSHqmYNrPjR%2B6/p4AGARywQgWBpLkpSc7fJKyzBhhxY9uquyNpW/osfBKaSXWwSZo2l5Uv60kdtJXC3sxBlJkpOI/Fhji4fhhEEMRBCkSA5FsJRHIvuKS4rlpbjSWYRmsa53p/txvFdscoHEoJkFaVKO7YOJMIcKstCcAArLwfgcFopCoJwbjWNYxwKOsmzonsPCkAQmgJasn4gMlGiPMluwJGYkgJAAnBoNIAGxtclVTSElHCSLwLASBogTpZl2UcLwCggIEFUZQlpBwLAMCICA6wEMkXgEOQlAbskdBxBEyKcKoCRdaaXWSMcwDIMgxxSI8Zi8Jg%2BBEMQeCkfp/CCCIYjsFIMiCIoKjqEtpC6PpADuFLJJwPCJSlaWVVlnAAPK7Tta6oFQxwXVdN13Q9T2SC9xwQB4dzHcQpxmLsXDLLwi1aKsEBIIdtP7RAXP0PEwBSD5NCrnEc0QNEaOHswxBcojvDS00XIY9E2i1ItZUbmwggYwwtBy5DWDRF4wBuGItBzdwvBYCwhjAOIht4MQ6t4JqKJo5gqi1Lt2xlWEzKDZlzbRBSsseFgaPkngo1W6QbvEBcSjKiydvNkYlWrFQBjIW6eCYDDGPjvLIPCKI4jA398hKGoaPQ/odsoHllj6Hg0RzbAE4gJCV7x4jl1VVlyQ9JbpokdCyqmJY1hmFN8dfVg7cQKsNR1M4ECuJMfj6SE8xlBUegFBkAibwfaRHwwgx70snTdPUswn/pK89H0zSX8MlRjP0D%2Bf6/u/vxIy8ipbAAfoFGpBJq8GmgTS611br3Ues9MsEBcCEBIPTRmzNyoZ1WAgTATAsDxCXqQGqkhdiPDarsGkARJAtS6uNZKPVQFDRGv4NqDUzDJQ6jdChTVdhdRpOAtG01ZrzSwUtdm60OabWxrtHmfMTpnQ4E0FgmoaSmiYMcQ4dsnpsKeJld6qD556ErgDcu0hK5gxrpDXQPk4ZMARlbZGHBUqCMhtNLG21drHDxtAomt0tEAi4Lox4MYqaoBpvzdBZhMGs2WlI%2BRZAKC83CUdfmKADBGCCVwQIItmTEHFpLSGitZbF2KcrVW6ti5a0YAQXW%2Bs0ZGxNmbWgFti421TtsTK%2BBnZ1DdpbfRXtkA%2B2Lv7LoaNg6hy5OHTpLMvoxzKvHROmBk62yMGnUA4i%2BDZwULnfOhdGDFxMWXIG5jZCWIhplGx9d06TysM3YOi8ICd27ntXu3B%2B7LFWKgIemQR5jxVLc6es84jz3dpAZeXQXZrw3p4Noegd6lH/vpQ%2BPRv4osyG/RYH8n53y/rC3Ij9IWr16LMTF%2B9H733xVvH%2BcxEVYpAYVDYwCmZMJcRA9GHBfGwM0RkxEQTHh6Mpigz66CmYs2waQXB%2BCRhEMGsNUgo06qPEkFQjQFC6pdS6lwLquwGGuKmpwERC0JUkLYZILVNI%2BpqoZhoVquwmG7FRm4w1Yi2ZONevqyBLrYmfLjmLTI/ggA%3D%3D%3D)

This method allows appending a variable number of elements to the end of the target list.
However, the technique is convoluted and not so adaptable to general cases.

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
using BindOpt = mp_bind_front
<
    QuotedFoldQ<V, Subtract>::fn,
    Arg_0, Arg_1
>
::fn<Args...>;

static_assert(std::same_as<
    BindOpt<Arg_2>,
    mp_fold_q<L, V, Subtract>
>);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIaa4AMngMmAByPgBGmMQgAMwAHKQADqgKhE4MHt6%2BeqnpjgLBoREs0bFmAOy2mPaFDEIETMQE2T5%2B0naYDpmNzQTF4VEx8UkKTS1tuVy2EwMhQ2UjVQCUtqhexMjsHOZxIcjeWADU5maRqGkEAPQsyVxcAHQIyclnJhoAgh%2BfXulGx2YbAUySY22OFyuJjiVi%2BfxCwEBrEwILBmGOdwe0Nh3y%2B42IXgcxyEXkiBGIYIIPxMlRxx3pxwImDuBiZ0LcBAAnslGMjjp9SIzuby2McrHFsD8Gcd4QCqAxTnEACIY5IAfQAbmIvJh2Z8QCAtd50QBaMUGo066GSmHUypK7HUuH/REANUVKrumu1uribi41sdXx%2BssRn2IwDVGg9qu9xvZcUDtudCP5EbVXBjXstvrckiTONDacjZiz6pzCYLTt%2BLuOgTLatoeHGevTGkF4cjM2LarMVeDXyZLKYbL9XJ5QPRrsF45F6IAioG8eTCQRjvOvKgmegAGKedCL4O0qUMofJVm52eTx43zsKJefaVF%2BUN/i0dBqgCO7K9TZbfrvG9HmtQVp3XftvntINcU%2BM8L3ZK9kSAu8HyLCwQnQAB5ZI12hT11UiDC1SoYhZGpP0T3pDct0wXd90XP0wJJMkKQca0DXlUhKJ7dsewDYMJR%2BDiGFbYAFCAiCfnGEc8GQNUmAUJQWggcZ0ANBRkXk%2B8KK%2BaV0IYLCcNE3sQO4r03w/b8/UCUDBWY8lKQfa0VmxDg1loTgAFZeD8DgtFIVBODcaxrGOBQNi2dE9h4UgCE0Ny1gAaxATyNEeTzEjMSQEgATg0SoADYcs8rgEmkDyOEkXgWAkDR218/zAo4XgFBAds4r8tzSDgWAYEQEANgIZIvAIchKDQO46BiMJkU4VQEgKk0CskY5gGQZBjikR4zF4WjCBIPA1JmfhBBEMR2CkGRBEUFR1E60hdBmAB3Clkk4Hh3K8nz4oCzhMJG4a11QKhjnmxbltW9bNskbbjggDxJvoYhTjMOIuBWXgOq0NYICQCbkimsgKAgfHCZAYApDMPg6CZYhWogSIfsI5hiE5d7eGZ5pOUwyJtG6DqYomthBEwhhaDZ%2B6sEiLxgDcMRaFa7heCwFhDGAcRJbwYh%2BbwDUUR%2BzBVG6EadhikImQq/ym0iClWY8LAfvJPAaqV0g9eIC4lCVZk1abIx4rWKgDDE108EwJ7sMYdmruEURxEuk75CUNQfse/Q1ZQELLH0PBIla2BJxASFxjdkZuAWhKApwzJFZNVS8NMSxrDMRr3eIQ79cgNYuh6ZwIFcKY/BmIIFlKco8jSDIBEHieCkyQYx5GGYe/qPpJk8do9BX3o5gX4ZYmXuYZ8P/o96WA/u4i7YJE%2BjhvNIBreCa0GFqWla1o2rbSwgXB9uR6KMaxQDmsBAmAmBYFiBAJK/g4iPBynESokgNCSCygVOqnkir6E4FVUgNVJA5XSmYTyeVlrwMSHEAq1RH6/WarYNqQDOo4z6rjAaAMRpjRJqgRG01ZocGaCwDUlQTRMGOIcNWm0CFPH8ntIg7cjoxzOvHaQicbop3uroKmL0mBvSVrfe%2B1Cmr/SGiNY4wMX7gxWmIgEXBJGPGjPDLhBMkYoziGYQBWMuosNJkjDh3iRhWIpjlLg7YaC0FpvTRm91Oas2jtE7mvN%2BbRyFowAgotxY/SljLOWtAFbRxVr7HY/l8Dax6HrRW0ijbIBNtHc2tQfrW1tpye2hTMbtxdjFd2ntMDe1VkYP2oBGF8GDgoUO4dI6%2BRionRRF1lGyFUXdfyGj07%2B0blYbO1t85QELsXUa7t3oVxWGsVA1cBC13rsqVZzdW4xDkZ3KBNQ6iZBcAZY%2BpAR4lH3rPKeWQN7TBSJPeoZ9x7L1qDrAQa9Wi/KHg8sFDRd6j0%2BSfdeORoXSRaECpel9NjX3Rlgu%2B317rPzBm/URBhrG2Psb/WRLj0aY2AaQUB4CRj3IqjgmqqVHiSEQRoeBqUCoFS4AVOIGCH4/Sai1ehHjDmkGSvgzlArKglR5ajZBCQ4h4riASxqnA6WMNvjtUVhKdUMOxmsd26RnCSCAA%3D)

Conceptrodon was created based on this idea.
By exposing different kinds of parameters using member templates, this library unleashes the potential of pack expansions and allows us to handle each kind of parameters independently.
The previous example will look like the following if metafunctions from this library are used.

```C++
template<typename...Args>
using BindAnother = Mouldivore::BindFront
<
    Mouldivore::FoldLeft<Subtract::fn>
    ::Mold<V>
    ::Mold
>
::Mold<Args...>;

static_assert(std::same_as<
    BindAnother<Arg_0, Arg_1>::Mold<Arg_2>,
    mp_fold_q<L, V, Subtract>
>);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAA7ABspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHMxsCklMqwDUALJLtPgAbiSYuyaxVhoAgiZ3APQAVK/PuwBinugBmFQEuzez0eD1uBEwLCSBnBJgAzG5wZDoZg4QiAJ5JRisTAAOjxcOwu2QBgUCl2AHlMcQmDUCaDhsQvA5Pt9fv9QVcbrddjzdoioTSUfCCBisWxdgBJBjpGkkOl3Xm7BlMgHKYioIiHY6gxWcnWK3n85GokWYja4vHYehsQQKeXcg085XMgAimHqdEu1yuLrhXP1jsej12FiYSl2bjD7A5CsduyDLOOuwEqxxAYNRsFJtF5t2VohjAI9rjSoIjNd7qYdFR%2BZtRdh2HTuu9sZLPK8aSMfNFl1hLopVJpGVRUplRDIeethbpsK5JZ9fpjDsDwa%2BSYIAHc8Kmm4aIQKYcKc9jPnhiMNSN2zSehJg0Ax0MW486AW6PbRUR8zxfdrf74%2BG13Hk9VbNsO2CYArxRUD5z7XlKWiIcBFRIC2wQ6laXhVC215UdHFlCcv3PIsYJw3tsEvP8BEfUicJnOc4wXWclxLBMACU72WNITguSMlBAFi4wTNd0D5LdVkvBBDHQeg%2BQQC4aGIsTUF2bZqTYcFz1IVCE2k3ZiE488LnArsCHk/TMGGNNaL5fdjSPa9xSIn9TTFC4qIfS9XPNPEcXJMzojtQCbJfXY3yrD94WcghKLvajL38%2BTz18p9HRA5cwM7SDXOw3k4X7NUNVQLUaIy2C3Fyx10KQhgUJsktqswir6rIvC8AIy9osqg0CVi/9ut1YKysYhsQBATNwTCytq3hRLApS0bxtFRcbKY/0bImoV0Uci0cVuYADILW1UoNEzIJK3t%2B3Cma3H2w66wUBbsDGnLmNAtbBJ5Tbsx23y7swI6CCCxtQLOg5vku3ZCs1b5UX%2BwHHvxQC3vuWJfRR0EXjeENgnQD51UEQE3hBO5vuFOyswctynqJEkyUa4chtCixcfx2QORbDKye26m8QsTBgGCaUjGB9NQuh4rYfezmS257zsV82tC1FmywYu/KB0Qpr%2BcFhhheARGcUvJXbSelaMo%2Bu50zl482F8nWhYglWMrViGNYlkrUQdvWnbNjG0fNjnfStq2zFhYJiS8LBLjMMwIlQVICEeSEuC4HEECSJJzDMJcwfNLYdguePE/NvPsQLvYU64QO7lCoQvAiMsdhI1GGK%2BinDx53Nbi822LisIbFTBqgGEhyEAH0TjELwttuMap%2B8C4AFoQ3n6ehUbf30fW24wYANTHpJJ/X1Fq%2BRnewduYhgHHjRD%2BPxfUVhejQUv6/x64e%2BF5n1FJBfu4343zMF/E%2B8Jn7n1zllXYAR760DwMMOG78NCXivjfNouxUHjxzhAkOYIO5bXlnbPEqDnZgxZg%2BW4DANRJUhocLwxw8BnAMmNcheMCYtzqhlOhDCmHsBACJNk9Y3D10btSBwY0R4nTGp7eEe8pEgE9lbIa0jYbwhIX7HekxHDIHHmGJQjQIDDHQGNBQ2JdFBWahlVhlDqHREQTfZBGD35n2ego1Rt137YIoumCe/BjjjwAI6ogCJePelEG5NwcPaAkcw/QcAWLQTgABWXgfgOBaFIKgTgFVLDWCVEsFYFxzCwh4KQAgmh4kLAANYgCSRoHESTYQAA4zCSCaQATg0AkdpSSuBNOkIkjgkheAsAkBoZBaSMlZI4LwBQIBkHlPSfE0gcBYAwEQCAJYBAkheBihQCAaBIR0GiKEbEnBVBNPiEveIkhdjAGQMgXYUgcRmF4JgfA448DGLaPwQQIgxDsCkDIQQigVDqCWaQXQbQNzUiSJwHgCTkmpIqZkzg5Jdk7IBKgKguwLlXJuXch5TzJAvN2BADwRz6DEBjiUuYvBFlaAWBAJAhykjHLIPs1l7KQDACkGYPgdBNJzIgBEFFERggNDRPC3g4rmDEDROSCI2g7yLNKYcus5IGC0ClRCrAEQvDAEjLQWgczuC8CwCwQwwBxC6rPCqxhlkUWYFUJxcE0ryCCCqCiuBERqTyo8FgFFZY8CjLNaQHixB45KDdJaowcCjAVIWFQAwBs954EwBuBCaTSm/OEKIcQQLc2grUCiqF%2BgrUoGsNYfQeAIhzNgOaEAxcLwRvhZcypmSkg1FNUvIx%2BVTC5MsGYKZEbiBfMdZABYdh7XOAgK4MYrRSCBGCH0UoAw2h5HSAIBduRUhboYNMfoMQJhVBnbUEYTRPAtD0NOhwnQL2HrXce2wF6d0TAfSumY66p0FNWBIRFHAUmkEmbwaZuLLnXNufcx5zzgEQFwIQEgNKuB0rKYmhY8kmBYBiBAapIBJCwhxO02EsRJAaEkK0%2BI4yknxHafoTgwzSCjMkO0hpZgkmdJucR5psJ4ixGAyi6Zsz5loaWUy9ZzLNkYt2eQSgXKqWnLYJwBoLATixCXkwWmVqnmsbThk95iGx3fOBXmgFEhpBFqUCWiFuh%2BUwqYHCs1AGgMgdRRwdF2zdnJhxXiyDWmuxcF0ziO%2B5LUCUuiDSswqGGXLMk/J6IsmDlhbZVSlABgjCBa4MgmgtAhWUFFRC2Vkr3VFflYq5V4iw3qsLJq7VKK9UGqNSa91FqrU2oyfgAyd6eKmv0y65Auy1ilOCOCQZGSfV%2BrRAGtYGTg2htKRGqNmAY1tYgomvgKaFBpozVm91ub/kFos7IYt4KMm2fLQmgdVhLA1rrfACAjbm0xVbdwdtcwFioC7RkHtfa%2BxXesMO0Do7x31tw%2B0M9LgHxvqXQ%2BR9swN17pqNDzdNQ4frvB3egQXRRhXvGBjmo2OeifqPTe19uPF2TEaGj49P7lh/pQ/RwDyKIVgd8wS4k2nAs4j02ShD45kPRfQ6QTD2HKAAcY6MupOJJCkY0MRup8R4hcHiLCGjAmWecGEwsoXNSWPS6V7EXpcuw7kaabCRnsJmdTM16JxlAHXnq%2BtzM23HaI1pGcJIIAA)

## Implementation

In the terminology of `boost::mp11`, the phrase 'quoted metafunction' refers to a class containing a metafunction member `fn`.
In a sense, the surrounding class acts as quotation marks.
However, I would like to think of it differently.
The word 'quoted' also describes a passage taken from a context.
In the documentation of `boost::mp11`, after instantiation, a metafunction is often said to return a quoted metafunction, meaning the instantiated surrounding template is considered a part of the result.

> `mp_not_fn<P>` returns a quoted metafunction `Q` such that `Q::fn<T…​>` returns `mp_not<P<T…​>>`.

```C++
template<template<class...> class P> struct mp_not_fn
{
    template<class... T> using fn = mp_not<P<T...>>;
};
```

In my opinion, invoking a metafunction creates contexts for its member templates.
Using such members is similar to quoting texts from an article--we quote members from an instantiated metafunction.
Therefore, for the purpose of this library, the term 'quoted metafunction' is better used to describe the member templates, and  'returning a quoted metafunction' returns a member template without quotation marks.
Following this thought, we will implement our metafunctions in such a way that the contexts are provided in steps, allowing manipulations to happen within each step before finally returning a quotable result.

### Failed Attempt

One way to do so is to accept different kinds of parameters using nested class member templates.
We will soon see the limitations of this method.

Consider the following example:

```C++
template<typename...>
struct Example
{
    template<typename...>
    struct Mold {};
};
```

This is quite straightforward.
However, such simplicity comes at a cost.
Namely, defining a member with the same name as its surrounding class is forbidden in C++.
Therefore, the following code won't compile.

```C++
template<typename...>
struct Example
{
    template<auto...>
    struct Page
    {
        // Error: Member 'Page' has the same name as its class
        // clang(member_name_of_class)
        template<auto...>
        struct Page {}  
    };
};
```

Assuming we are creating a metafunction that transforms the variable at a given position in a sequence, invoking the metafunction by `Metafunction<Transformation>::Page<Index>::Page<Variables...>` is impossible since class member templates with the same name cannot appear adjacent to each other.
Note that `::` indicates a nesting relationship on this occasion.

One solution is to add a separation structure between the class and its problematic member.

```C++
template<typename...>
struct Example
{
    template<auto...>
    struct Page
    {
        struct Slash
        {
            template<auto...>
            struct Page {}; 
        };
    };
};
```
