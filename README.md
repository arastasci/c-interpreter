# cmpe230p1

## BNF

```
<stmt> => <assignment> <comment> | <expr> <comment> 
<assignment> => <var> = <expr>
<expr> =>  <term> + <term> | <term> - <term> | <term>
<term> => <factor> * <term> | <const> / <term> | <operation> | <var>
<operation> => xor(<expr>, <expr>) | ls(<expr>, <expr>)
| rs(<expr>, <expr>) | lr(<expr>, <expr>) | rr(<expr>, <expr>) | not(<expr>)
<comment> => % (str) | ""

Terminals: '(', ')', '=', '+', '-', '/', '*'

```

===============================================================================================================
```

<expr> => 

m = 3 * 5 - (a + b)
```