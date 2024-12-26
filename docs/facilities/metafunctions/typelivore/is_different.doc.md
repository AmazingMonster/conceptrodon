<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::IsDifferent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-is-different">To Index</a></p>

## Description

`Typelivore::IsDifferent` accepts a target and a list of elements.
It returns true if the target is different from every element;
otherwise, it returns false.

<pre><code>   Target, E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> (Target `different from` E<sub>0</sub>) && (Target `different from` E<sub>1</sub>) && ... && (Target `different from` E<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsDifferent
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct IsDifferent
{
    static constexpr bool value
    {RESULT};
};

template<typename...>
constexpr bool IsDifferent_v
{RESULT};
```

## Examples

```C++
static_assert(IsDifferent<int, int*, int**, int**>::value);
static_assert(! IsDifferent<int, int, int*>::value);
```

## Implementation

We will implement `IsDifferent` using `std::is_same_v`.

Here's the entire implementation:

```C++
template<typename Target, typename...Elements>
struct IsDifferent
{ static constexpr bool value
{(...&&(not std::is_same_v<Elements, Target>))}; };

template<typename Target, typename...Elements>
constexpr bool IsDifferent_v 
{(...&&(not std::is_same_v<Elements, Target>))};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIGb%2BpAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYqa6MyHiYCjeHZ5fXJ39H3wu5yBZkCEWQ3iwNxMgTcBAAnk8APoEYhMQgKGHYYHA37/fH7QF4m4ASRYqXobEETAanwORIJjNOOMuBEw5IMbJhcMRjFYmBuABUWsBMARSDcEU9mGwAHTy7CUxgETGBbGXcbELwOUkKO54KhUBLKnEAdgsN1mjmQNzQDHGmFUqWIN1iqE8NwAbmIvJgzRYIPLZeYAGyhiAMVAES0EdAgEB4BRIhT8pGe7mK9nKhQS4XEUUELFLJYmU13GEW0vlwJWS7Atkcml%2B2FSvlsIUisUS1syzBBzNUlVY4F2h1Ol1uj0kvUGo3EZVp6F182B%2BWh8OR6PjOMJpMpthpjNKwQ5jv5sVFktlissq5Mr64w43bCqVgUgUPn73%2Bm3q14ZBIkwChKK0EDTvqhrGoI3IROKNywbsEoIYh8GCPsWLxt63iYCWNbAn%2BAFASBBAQGAYC6hBc4mrCsFIYIdEELsGEgFhvq4RYHArLQnD%2BLwfgcFopCoJwbjWNYlprBsArmIEPCkAQmicSsADWASSLKGgABxmGYACculcP4WmaVwpqmtI3EcJIvAsBIGgaKQ/GCcJHC8AoIAOQpAmcaQcCwDAiAgGsBCpF44oUBAaDknQCRRPynCqJpIYALQhpINzAMgNpSLKZi8Jg%2BBEMQeBxlwMiCCIYjsFI5XyEoaiKaQuhlQA7miqScDwXE8XxjUuQA8mFoXRqgVA3IlKVpRlWU3DlZg3BAHjRfQLoyVwSy8F5WgrBASBRakMVkBF%2B2HSAwBSGYfB0GyxDuRAsSNbEEQtPCnW8E9zDEPC/WxNomAOG9pBRYO/UMLQr3eaQWCxF4wBuGItDudwvBYCwhjAOIkP4PODh4J67yNY6/1hVscmwXUjW0HgsRol9HhYI1qJ4LZyOkPjxBukoDxo0YVNGIpKxUAYwAKAAam8LX9dKgP8BVojiDVst1So6iQ81%2BjoygYmWPo1PuZAKyoKkDRI8l24wncpiWNYZjOezxVYPrEArHY/0NC4DDuJ4HR6GEERDJUIxlUUWQCFMfjBxkocMPMwyJGVru4wIfSTN7%2BQJ3Ubu9BMAz%2BwsQe2Dn4d6LMrSx4H8cu5JmwSN1HC8Y5fWcONSWpelmXZep80QLghAkNCoLrZtAsrAgmBMFgiTO6QqmSIEsq6YE5kaJIZiSCG9n%2BCGun6Jw1mkLZsmyiGXAhppukmSG/iSIZi8ho3kMuW5HnyQLvkBbtQVDWF5CUCdK1xTYJwFoLBPSmmSkwW0BgjCzV0rKLgGl8qFRICVPQStKoK2kErRQKtGq6Eum1JgHVkZ1wbk5XgA1v4jTGhNNuUD0awPgRpBaS0DorQHoEMwG1X7eR2ntVAy0Ei/0igIthIwIToy4AZByNBaA3Tug9SGH0XqA2UV9H6f0Aas2BsqUG4NGrQ1hvDWgiNAao3RpjQS2Ms74yRoJImyASaA3JpZQSVMaYvXplsQSTMWZyXZpzTA3MLERFALwvgwsxYSylowGWsgMHVSwbIHBDU1ZJA1vzK2VgdbuKdobY22RTbm0CJbbWFhbYUPtiVAmBtuhZ2cBAVwxcyp%2B3KHHPQIcGjNLSFHBo5dFgZx6MnIuacI51KTo0HO/SC6lzaKMkuUy87tPWqsdYNcVmWTIU3DgLdJrpQkTAqRTCNALV7kVDhQ8eHbVHuPSelA6770PnAlepp/C6TMoEVe68b4P2cpwZ%2Bnk35%2BUCsFYawj/6xXihwEBU0WAKE9DaT0RzOTvAIEgvuDs0HxPlok2qKTVaCV0MEQhxCuq73rr1R%2BnBBohTCjcUa41YXwsRcips4wWGiMOhwwI3Cto%2BU/hCo6f9OUrRYsgVIqQ0xSKRCi8YSJVBpSunIhICjHrPS%2Bqo9V31fpu0BjowQeiIZWMwDDOGCMkZyXMbzbxKM8A40cLYwmqhiZsmcYICmkN3G03hF4xmxU/G8ACRkIJ7IQn83CULJgItxaYEltLVm6CcUSCSYIfFeCQDBGgcYMputYh5KEgUgQSNtjbi1tbSwFShJVMdvAF2mcJkey9nkMZrSA4DJ6cUbI3TOnZGmfHcZDQU5zObSXetg7FltIrgs/o3TZl9trqsqSC7NmUr%2BTshV6U4UIq9Kytk7Ke7INWoPXlI9SBjwniMaellHlJDgYEQI/gjI33sve00Z9fkUP%2BbYF%2BfLiwzxAJIfwC9TKmnsppSQBkuDaTMPfSygRV2ftclcpS5K8ofqEl%2B39Kx2aZGcJIIAA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/typelivore/is_different.hpp)

- [unit test](../../../../tests/unit/metafunctions/typelivore/is_different.test.hpp)
