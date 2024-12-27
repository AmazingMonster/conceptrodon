<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Add`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-add">To Index</a></p>

## Description

`Varybivore::Add` accepts a list of variables and sums them up.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> V<sub>0</sub> + V<sub>1</sub> + ... + V<sub>n</sub></code></pre>

## Type Signature

```Haskell
Add
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct Add
{
    static constexpr auto value
    {RESULT};
};

template<auto...>
static constexpr auto Add_v
{RESULT};
```

## Examples

We will sum up `1, 2, 3`.

```C++
static_assert(Add<1, 2, 3>::value == 6);
```

## Implementation

We will implement `Add` using a fold expression.

Note that the initiator is on the left side of the expression. This means we are doing a left-fold.

<pre><code>   Init + ... + Variables
-> (...((Init + Variable<sub>0</sub>) + Variable<sub>1</sub>) + ...) + Variable<sub>Last</sub>
</code></pre>

In our case, left-fold and right-fold produce the same result since `+` is commutative.

Here's the entire implementation:

```C++
template<auto Init, auto...Variables>
struct Add
{ 
    static constexpr auto value 
    { (Init+...+Variables) }; 
};

template<auto Init, auto...Variables>
constexpr auto Add_v 
{ (Init+...+Variables) }; 
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCBmXKQADqgKhE4MHt6%2BekkpjgJBIeEsUTFxtpj2eQxCBEzEBBk%2BfvF2mA5pNXUEBWGR0bEttfWNWYNdPUUlAwCUtqhexMjsHAD0AFQbm1vbO5srJhoAguubANQAkiwJ9GyCTFWnW/tHJ7tvu8%2BHB4cEmFcGvxMAGY3EwvEQLgxCKRTmCiAA6REANTqeCYEXoCmB2G%2BCgIxC8DlOh3Q6G%2BJgA7BZTt9TnTTnj7nhkKc0Aw8ZhVAliLDwahTgA3MReTA0o70mlU04Qc5QgjWRHw6wo4hojGYBTTSUAEWB1PJFN1QKsR2%2Bv3%2B90wwNBfMh0N5CORqPRmOx3zZHK5PLh/JJ6AA%2BgKxV8pTK5QrEcrnerNTq9cHvq93ttPknTthVKxrqKnonkx9yUdGY5kP6mAolPUIH7rfFTmYYUDsSAQELvKLgUbtacAGzTPXfDizWicACsvD8HC0pFQnDc1msDPmiw7ZiBPFIBE0Q9mAGsQKPJPCNAAOMxmACcF64o9PJ64FIp0hHHEkvBYEg0GlIk%2Bns44vAKCA35blOQ6kHAsAwIgIDzAQCTguQlBoFcdDRKErDLKoJ49gAtD2kinMAyAslI8JmLwmD4EQqroHo/CCCIYjsFIMiCIoKjqGBpC6PEADuxBMAknA8MOY4TtuM6cAA8uCCEEKcqBUKc2F4QRREkacZFmNKHiofQPLmOu0y8KBWizBASAoQkaFkBQEDWbZIDAFIDY0LQvzEEBEARJJETBHUACeIm8P5zDEIF0kRNobSgRuKG3AQ0kMLQwXcVgEReMAoK0LQQHcLwWAsIYwDiOleDELFeAChqkmcm04LLBuwS/C%2B060HgESCRFHhYJJ%2BJ4B%2BBWkDVxARMkmDan8JUdUY26zFQBjAAoSJ4JgfHSQkjAhWxwiiOIrEMfIShqJJvH6CVKALpY%2BidUBkCzKgCRVPluF4mSQLaqYljWGYf6jbRtUPeUlRpC4DDuJ4TT%2BBDEx9DE8Q5KkAgjM0iTJMjDBw8U/QtBUVUCJ0wxQ6MIME9UQzdMEvQ4wjtiU6jeiMvU2NTFwswKMuSwSGJHDjj%2Bkn/ipOH4YRxGkUeOkQLghAkDSa7s6Z82zAgmBMFgMQQHuICSEC8IXkCT4aJIZiSD2X6jj2F76Jwb6kB%2B67wj2XA9ieF73j2h43gbPYC9x/6AcBm7zRB0GWbBcmIfZjkGRhbCcHULAChSuFMKyBhGFpF7wlwx6UdRJB4HR8RHUxB3SEdHGndxugNgJQkhbz/O/rw/6yfB4KKcpqmi%2BnJVZznx66ag%2BnRPLQJmCZwdgRZVkjzZBlIQ589OcgGcude37uZ53m%2BdxYVBTtB8RVFMUODtCWMElKVpdOGVZTleU7UVM3LHfFVVTV%2BXTvVyCNTtLUKiSQ6l1IKvU36mVVENDco1xpKCmsVIws1QAzz4EtFaa0NpbUnBuUu%2B0WIV1kFXLi05a4XTmt9KwN0QH3S1jOZ6aRXrvU7JQ36/1oiA1oRzfG7RnAQFcIzeIgRqaTFxujXIaRBHiMxqzMRrReEUy6FI%2BRVQiZU0KPDJmDMSZo2ZuommbMOZcxYk3CS/tODCzUoRNe/cuDZ1zhoaUMsaLj0VtPcyKs1Ya0oLzO2Dts7GwpKOC8j4gQmzNpIeILcpIAVsEHMy4FIIwTgvJJeMd0KYQTsQFg6kWAKAFCyAUdj4QAg1AQfOstaL0VkGXAhu1iFnRAECUg9dhIFVMX7P8MlI4KSUipXJ%2BTCnFNKXiYeo9DJriBFPBJs8UAr0XtHeZ/QCkJASIGOx/oRkEH9KoAifA6A70oHvacx80oblOafWKF8R6JWSqlSS99spiCfsNF%2BSCIGkHwJVdoX86qqAar8ABgggHcRAd1QK4D%2BpQJ2rAiaCCZrBBQeZNBTBlqrXWptbaw08HMQkIQ9iJ0SE6CaeQ4w10bA0PgI9BhAh8orHeldH6lg/qtwBkXIGdCVFg34RDKRwiNG02yBjKoUikZVFkXTLlhNtGZF0Tw1RlMJVaKUTo5VLMRGaPZnMBY3MtUvmboLCxuzCJ5IKYKYZlpRnSwLhM4ySsZ6ePVv0OhL4/GxGzkCIEo5byRK/J6ikrtOmt04IHECytSD7kkKOfWD4KRfhPJIa8XAzxmF9i%2BIEZiumxJmbzCiQaYn2o8SNaIKRnCSCAA%3D)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/add.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/add.test.hpp)
