# cmpe230p1

## BNF

```
<stmt> => <assignment> <comment>| <var> <comment>|
<assignment> => <var> = <expr>
<expr> => <expr> + <term> | <expr> - <term> | <term>
<term> => <term> * <factor> | term / <factor> | <operation>
<operation> => xor(<var>, <var>) | ls(<var>, <factor>)
| rs(<var>, <factor>) | lr(<var>, <factor>) | rr(<var>, <factor>) | not(<var>)
<var> => <letterlist>
<letterlist> => <letterlist> <letter> | <letter>
<letter> => lowercase/uppercase English letters
<comment> => % (str) | ""

Terminals: '(', ')', '=', '+', '-', '/', '*'

```

===================================================malyasin============================================================
