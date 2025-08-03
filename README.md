This is the first C program I ever wrote. I was bored over summer 2017 and
Sam Azouzi told me to implement Linked Lists & some type of sorting on them.
I think the ask was loosely based on a comp arch assignment (why Linked Lists
are taught in a comp arch class, idk).

I'm keeping this repo around because of the memories and becuase I find it
funny now. It's absolutely terrible code, for example:

1. I didn't realize that C had "->" operator until like halfway through
the implementation, so I used "(*ptr_var)." to access members.

2. Didn't free any of the memory that was malloc-ed.

3. The void** return type of the function executed by the thread is very
suspicious.
