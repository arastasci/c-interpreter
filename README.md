# cmpe230p1

## BNF

```
<expr> =>  <term> + <expr> | <term> - <expr> | <var> = <expr> | <term>
<term> => <const> * <term> | <const> / <term> | <operation> | <var>
<operation> => xor(<expr>, <expr>) | ls(<expr>, <expr>)
| rs(<expr>, <expr>) | lr(<expr>, <expr>) | rr(<expr>, <expr>) | not(<expr>)
<comment> => % (str) | ""

Terminals: '(', ')', '=', '+', '-', '/', '*'

```

===============================================================================================================
```
<stmt> => <assignment> <comment>| <expr> <comment> | 
<assignment> => <var> = <expr>
<expr> => 

m = 3 * 5 - (a + b)
```