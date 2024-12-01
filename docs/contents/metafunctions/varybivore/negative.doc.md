<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Negative`

<p style='text-align: right;'><a href="../../../index.md#arithmetic-modifications">To Index</a></p>

## Description

`Varybivore::Negative` accepts a variable and applies unary `-` to it.

<pre><code>V -> -V</code></pre>

## Type Signature

```Haskell
Negative :: auto... -> auto
```

## Structure

```C++
template<auto>
struct Negative
{
    static constexpr bool value
    {RESULT};
};

template<auto>
static constexpr auto Negative_v
{RESULT};
```

## Examples

```C++
static_assert(Negative<1>::value == -1);
static_assert(Negative<-1.0>::value == 1.0);
```

## Implementation

```C++
template<auto I>
struct Negative
{ 
    static constexpr auto value 
    {-I}; 
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBJcpAAOqAqETgwe3r56icmOAkEh4SxRMVxxdpgOqUIETMQE6T5%2BZZj2uQzVtQT5YZHRsbY1dQ2ZZYNdwT1FfaUAlLaoXsTI7BwEmCzxBmsmAMxuTF5EANQAkrvYJhoAggoExF4OR6GYwEyOAG6Yl1cmAOwWR2%2BR2BR1ubzwyCOaAYt0wqnixCOB2O7zEXkwgOuIMB/wAtGdfgARXYA75/Yk7KzXb4AegAVAzGUyabTGQAVbBCNmMlnXelMgW8n7XMGOZAAfSYCiUdQgz1eHy%2Bey45xAIFR3gxuwphKOuK4MxJ31FEMl0uiBDlL3Bn12bn1ADoNKr1WitTsdUcuE7DZSOHNaJwAKy8PwcLSkVCcNzWayghZLLVmHY8UgETT%2BuYAaxAQbMDt%2BZkkAA5i0GNABOPMaABsxZ2%2Bk4kl4LAkGg0pDDEajHF4ChAHfT4f9pDgsBgiBACwI8UO5EoaA2dGioVYK1UxZruJrkiOwGQkKkDrMvEw%2BCIxDw6D0/EEIjE7CkMkEihU6mHpF0cQA7sQmPFOB4ANg1DDNI04AB5Q5ZwII5UCoI4Ny3Hc9wPL1JGPI4IA8Jd6ERcwUxmXghy0OYICQRd4mXMgKAgSjqJAYApDMPg6DWYh%2BwgCIwIiYJagAT0A3heOYYh%2BIgiJtAqIdU0XNhBAghhaEEj8sAiLxgH2WhaH7bheCwFhDGAcRVLwYhpLwT5dIjOEKkOFZU2CNZAw/Wg8AiP8xI8LAwLuPBWz00hPmICIkkwQl1iMtyjAzOYqAMYAFAANTwTBvwg%2BJGCE59hFEcQn1veQlDUMCv30IyUFjSx9Hc/tIDmVB4jaXTcVudBtVMSxrDMbtgsvLA6ogOZykqZwIFcYYmlIQIJkKYosiSFIBEmhaclSbo5umWwWgsgQOiGTxGj0Ea2n28YCl6EoBk6FbRk6DbLokYaE2WJ7Gw4ENOzAntEM3bdd33Q8MLMLDcEIEhAWTA1iNiuYEEwJgsBiIbSBzSQdgdCsdl%2BSQNEkIsa3bIMawrd7m1IVsUwdGsuDrCti1poNJC4IMsZrL6Px7PsBzTWLRwncip2gudaPovDVzYThahYd5flxJgoQMIwvQrB1vRs88SCvG9ZHvfLpEK18So/XQWN/f8hOAj7QM5yDhdg%2BCkWIGW5YV5AleAFW1adLCcKovDIZ2MwiN54cyIo1BcOiec6Mj/2%2Bml2XcXdoyuArLgOxoWh2M47iPxEgTsoLsSJKkhxsrkxgCEU5SwLUjStJ07KDKilYI3wczKissDbOQezsqclowLcjyBO8tviMvALU2C0KlAiwyjGi0Aw74BLktS9LMrDVNCr1x8DdkI33wjU3ypizqrGqkfBoaprUhatqOqqiwet4VA%2BqvTBb%2B21pUhcBg7hDojGmoAh6UwrrZCWmkYBU0oFtHAfNZof89pjFur/Xa7QxiIK2mCA6GQpp4POpMJBz1FivQNO9T6XZ36cCdi7eWisjJe3VqDTW%2BEoYhxIpmUg8NEZ9BRi5cmlNVZ41%2BKzX4vwdj40kDuOINDwK9lsDzbhZEBZIGnDBGOYsVxrils7FCLAFDvEhO8NODotjfwIKedh2s4h7zygfHKx9SogAbObACekrbUO%2BnbGchw4IIWloY4xpjzGWNuL7OO1FA47C4XzQWOiaILmiXhdUyB4jxHFGYis4oIkEElAYg2bFoi5x4nxMSRcKniUktJCukd5LVyUipdumB1KaTEE3QKLcl4T1IB3Cy3cPy937oFQeLkIwj08vxcevkp7ZVnmFBeUVggr1ImvJgiUUppQyllQKDiHwSEPi%2BYqJ8dBuPPsYF%2BNUIg/0as1TgNI2qVS6pYN%2BkZP4DXgMNHao0/DjUAegmaF0IGrWgeg%2BB61ZqPWQZgs66CTpVGwdC0Fd18FHTRcQzaJQyGJjei5HxtsOD0JCSYo4OSLFvCsWw8GHDCIwzDnDBGSNKBW2ESAMwqsdg7CDOWZm7ZuW/DrBzbsnBuaDlhqjEAkhfjHnEaUSQFYxFYy4L8d6OwbaiqUaoq2J4RW0O1ZK4KyRnCSCAA)

## Links

- [source code](../../../../conceptrodon/varybivore/negative.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/negative.test.hpp)
