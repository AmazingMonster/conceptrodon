<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AnyConfess`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-2">To Index</a></p>

## Description

`Typelivore::AnyConfess` accepts a callable type predicate and a list of elements.
It returns true if there exists an element whose value result satisfies the predicate and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> (...||Predicate{}(Elements::value))</code></pre>

## Structure

```C++
template<typename, typename...>
concept AnyConfess = REQUIREMENT;
```

## Examples

`AnyConfess` turns a fold expression of a callable type predicate over `||` into a concept so that it can be used for subsumption.

The following code will fail since `(...||Pred_0{}(*))` and `(...||Pred_0{}(*)) && (...||Pred_1{}(*))` are both atomic:

```C++
using Pred_0 = decltype([](auto...){return true;});

using Pred_1 = decltype([](auto...){return true;});

template<auto I>
struct Monotony
{
    static constexpr auto value {I};
};

template<typename...Args>
requires (...||Pred_0{}(Args::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...||Pred_0{}(Args::value)) && (...||Pred_1{}(Args::value))
constexpr bool fun(){return true;}

static_assert(fun<Monotony<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEEgCcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BxemUYA1MrEmOgA%2BhqHJv4AIodYyLQEAJ6pmBAmgVaBtxBMXiIADoQasTAB2CynAhbBiHAjELyYG5WcG3MH%2BKwaACCJhx%2BwiwGOpwuXGudwe9Webw%2BXx%2BfwBwNBEKhmBhxDhCKRKIh6J5OLx2IImBYqQMwpubkZqEOAEkbthBXNEQ5DgBZASoIgMF6ClmCw6Gw5zJiOZCHNAMOaYVSpYiHaWHABuYiR10h8rR/NxXsxepxwtF4uR/jcr3ezDYIKB2OIwAUCsFpwAjl48KcFIcINGIW5cyczpd9WiILH4yAQC7vJhVmCcZbrbb7bFUJ5DlQvAwIGDIdDYe2xEoeV6BQGRWLTSGwzTI5ho2WE/5FTiU2mM9mQbn8ySi5DeaW4woK1WkbXrmYAGzmC9ZnPgvP3guk4t/BfH101uvYhvCpuHFtth2XY9qy7KcoiIaorc/rYiaZrnEwChKK01CdpKGoMFqAi6qGXCJku3YYhYHDrLQnCBLwfgcFopCoJweaWNYxqbNsmDnv4PCkAQmgkesADWICBBeQIABwXlIgTghekhJP4UlmP4%2BicJIvAsBIGgaKQVE0XRHC8EemncdRJGkHAsAwIgICbAQqSAuQlBoKKdAJFErC7KoYkALTSYcwDIOaUhAmYvBnIQJB4Ogej8IIIhiOwUgyIIigqOoxmkLoXCkAA7sQTCpJwPCkeRlE8bRnAAPKArZBCHKgVCHB5F7eZIvn%2BYcgVmFmHhOfQ9rmBxqy8EZWjrBASCOakzlkBQEATVNIDAFIZh8HQwrEEeECxKVsQRC0LwFbwO3MMQLzlbE2j1EZnGOWwgjlQwtD7WlWCxF4wBSrQtBHtwvBYCwhjAOIz3ppdeBOpg300Ta9SArsnERMKZFpbQeCxLlJ0eFgpUIngak/aQ4PEC2Si3CKAMo0YPHrFQBjxgAangmBZeVEYHYlwiiOICXRfIShqKVGX6ADKDWNY%2Bio0ekDrKgqR9N9nlzOgNy3KYjGWGYOmE8QEUQ/A6x1A0zgQK40x%2BJlYSLBUVR6EUWQCKbNsZHbDDDFbKzdL0jTzA7mUG30AytK7ozVBMgw%2B6HgeW8HEj6yxOwx0pHAUVppW6Q1Xk%2BX5AWSEFWa4GFfUKVwg1cVT6wIJgTBYIk3akAJkj%2BECsngpIGiSGYkgXhpQkpEjKmkGpHFAuJF4iUkIlcBegSSFwgSyReKdpbp%2BkgIZVOmRZY1WVVdkzXNvWuWwnAtCwTrgp5TAWgYRw1ECXBAlD%2BBENrkWZTzsVc9IPPJfzaW6MtOU8oHSKknEqS8Ko7xqnVB0xBT7n0vk8AG7Ukh3wfl1VAPUEjsTMCXYaJkt77wSPZWaGDJq9RACfM%2BnlEFGBqFwTSNBngJA2ltNKR09ps3YSdM6F0HBsxuowAg91HqlRem9D6X02Z/XJrsGi%2BBTgNHBpDEKqgYbCjZgjHopUUZoz2pjWRQ1tZ404oTYmmBSb/SMBTUAxlqa0wUAzJmLNGBs3fpzeKX9ZA/1SjRf%2BQtKaqysJYcWsRJa1xlnLTgCsCBKzuIE6wGteCoC1jrMJ%2BseigyNibTwHQ9AW3KNHTKts%2Bjh2KdkIOywQ5%2By9mHHJ%2BRfYZMNv0eYFTra%2B29nUs2EcFgFMqQnBQcd4ogOTtpJJnAYFwIvlfJBt975XAgPnZ%2B7Fi5DTLqQCuVcxi1z7qpAIKC27gjnuCcE/h26dxnovHSnAV5r1sRveAW9rLVWIYQ4gh9dgnx8iwBQTpzROlvsGOYIUn7hVfuzD%2BHj2beIFgEbKuV8o/WGWAq5HBKo2UBLVeqnyWrfN%2Bc6AFk45joMwYXfw/hcHrwIaQqaLzqXkN%2BakVI5x/lJHOICggCFYHSRWkw9alBWE0S4U9TiQqeGXX4Rg26QiHpPTkZgV670xCSPxtIqxBjSDyNBko0q0NkCww0YILRyNUboxePo7GRi2amIyOYsmVjCTrxpkwemjNmas3xm4uKEhPFJT5j4nQsLr7GFFsEnRaTaKy2yN9AA9IrEWasLCJNoikrA4bqlZIYO4TpeTM2tPdmU%2B22ailOz6HmqpjT/YdLyF09NzTBhlr0CaKYRbukNuLhsLY8d21IxGancZ2LDi4r%2BQS4URKFkgtJSs0utjy6V2rpQEB/c1JmBQWSwIgQ270I0GSqSIlLljL0rYVe06Rr8RAA3O%2B/gRLTwUhui8CkpKJ38Mig9qyZ2J2Cvusqh68G1gJsw7I56gA%3D%3D%3D)

By turning `(...||Pred_0{}(*))` and `(...||Pred_1{}(*))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires AnyConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AnyConfess<Pred_0, Args...> && AnyConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Monotony<1>>());
```

## Implementation

```C++
template<typename Predicate, typename...Elements>
concept AnyConfess = (...||Predicate{}(Elements::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAHKSuADJ4DJgAcj4ARpjEIGakAA6oCoRODB7evgHBaRmOAuGRMSzxicl2mA5ZQgRMxAQ5Pn5Btpj2xQwNTQSl0XEJSbaNza15HQrjAxFDFSNmAJS2qF7EyOwcBJgsKQa7JgDMbgQAnimMrJgA1MrEmPiiu6S3F1fMbAB0v9j0bEEChO2BMGgAgmgGFsUgRbuCGOcPAwqJgFApbicACK3CC/b4mADsbiJbgeTzwL0wRKshKxEH%2Be0YBAUIBAADcxF5MMtlicrBCweCAPQAKnFEslUuFQrFEtuABU0SzbpKZRC5VKteL1eChV4MkZ7o90AB9DSY444rDIWgfTAQEz%2BKz%2BelMLxEfF8wkWR4EDYMd7Ebn8olYvnHAV6iEGiLAY1PU1cS3W2p2y4Op0ut0e1Beml%2BgNBkORsMRqNC3b7Q7U07uoi3ACSIKFM2DDluAFkBKgiIihTShbdh7cZkxHMhblCZphVCliLd66hbpzvHcac26aHBVvS4KIVWDuPa2cM19MPjwcRgMDjqCIY8AI5ePCPDEIpECVHok5kk3mt4rxvfEWwhaddjnBdYlQTxbioLwGAgb1fUwf1iEDKgxCUUMt33cFDxrX97XPS9r1ve8r0wZ9XzReFEWRb9bz/RMNEAsiQLvTEzAANnMbi6M/FE0SY8kzS4NjgN%2BUDIQEGdINuaDYPgxDkMLdDi1rWksQHCExwnU0mHRBICGoBDf27BhewEc5fy4Fs7yQ8sOFWWhOH8Xg/A4LRSFQTgSUsaxR3WTZ1zMY4eFIAhNGc1YAGsAkkb4NEkLhCWODR/A0HjuLMQJglcjhJF4FgJA0VjPO83yOF4VlWKirznNIOBYBgRAQHWAgUg9chKDQfY6ASKIbk4VRAm4gBabjJFuYBkEnKRvjMXgKSIYg8HQPR%2BEEEQxHYKQZEERQVHUBrSF0cSAHdiCYFJOB4Fy3I86KfM4AB5D0urhVAqFuUaJqmma5tuBazFxDx%2BvoBdzHC5ZeHqrRVggJA%2BpSAayAoCAUbRkBgCkZIaDtBJWQgWJntiCImnOO7eHJ5hiHOV7Ym0Wp6oivrAQIV6GFoKnTqwWIvGANwxFoVluF4LAWEMYBxD5mi6nZNFntnWoPW2CKIl2ArvNoPBYmu%2BmPCwZ6CDWkrxdIRXiGgpQsT2aXdaMaLVioAwbwANTwTALtez5qYO4RRHEfatvkJQ1Ge879GllBrGsfQ9dZSBVlQWEsjF8aZnQbFTACywzEqq21qwJOkM6boshcBh3E8No9DCeZykqPRCkyARJj8cTW56QYm5GcSajqAQ%2BgmWu8gHroWfqWZe%2BGRIB9mDu9DHZpZ8WefVgUYKtgkB6OHc0gKt4KrfrGybptm%2BbEtBhl8FWriYbh53VgQTAmCwRIy/iyRjm%2BABOY4hJJDJTMJIbiZV/DcT/voTgRVSAlXCt8biXBuKBD/oEFB/gUr%2BAAdxQ%2Bz0qo1RAHVZ2TVWpI3ah9bqGMsaQyGmwTgTQWDskJONJgU4DBGi4H/b4XAkrLTviQdam1ZA7WDtIUOR0I6nV0MkK6N1qZ7wPkfF6HB3qdQ9Lcb6i5iDMNYew200tgY8L4RaCA4NUaQwfisJ%2BDVEbI1QBDBIPVMaOMsSMJhLDxqGKMNwrgrECa7GIMTUmp1aaU39uE%2BmjNmYOH9uzZkXMebPX5oLYWtBRb%2B0lg7bY3l8CPAVkrU6KtkBq39prLoz1db60pkbXJcMzb%2BytjbTAdspZGEdqAOxfA3YKE9t7X2jB/ahzEXtCRsgpEnW8rI6OTtc5WEsAnWIpcU5p1kpwTOBBs5WnmdYAux8i7rSVsncuU9nAQFcEvcSDcyhzxbukNu2Qx6d1SA8nujc7kTwrsPRezzl6TyHr0GeHz17L1%2BbkF5K85i3NBVwTe289pKKeqdE%2Bnj9EcKMdw3hSVcS4EICQB%2BcLbEIxfm/D%2BlA95wIQTw5KhIcGEjSpIUBU1xIqMIbYYhkVSHNTah1T6LjaGDWGhwJhAMWAKHZJOdkWKawzAEfi4uIjtpBzGQHSZkcQDHFIPI264skX4JRW9KhX0fqiumuKyVK4ZXHhmGDNxaMH7HFhly7pFDBXo16vayGHJkApBSKaaVf9TSyoIAZXRU0%2BB0CCSEsmFN6aRLjQzJmLN4mOI5kk3meTMACyFiLMWEVskdPqaQfJU9FZi28iUspFsKna14NUg2n5janVNngc2EVmnpFafbDpcZSGuyYB7L2Ps/YWxGSqiQ4zDrhymToTVszjBx0WdUlZPk1kMDFsKLOsc84WH2T5Q5Jd4CbwBT0KuNcIX12rmvZuXc3lZCua8ooWQb391OYCkeLQ/lfLOUC/or755jH6I%2BqFAHd5rA2DvOFMD97IsqpwHRLAxUSqlda3Ytrb4KsJc6%2BGMVSCv3fiMMuBUqVJB4ccY4/hMopTKhRwkqCDXweqhykhdi4ogEkP4f%2BQQeJ/0kH/NKgCuBaoKscODx9ODErwwVJajGJPMdw7yS2RNK6SCAA%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/concepts/any_confess.hpp)
- [unit test](../../../../tests/unit/concepts/typelivore/any_confess.test.hpp)
