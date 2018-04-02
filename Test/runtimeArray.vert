#version 450 core

buffer bn {
    int a[];
    float b[];
} buf;

uniform un {
    int a[];
    float b[];
} ubuf;

buffer bna {
    int a[];
    float b[];
} bufa[4];

uniform una {
    int a[];
    float b[];
} ubufa[4];

buffer abn {
    int aba[];
    float abb[];
};

uniform aun {
    int aua[];
    float aub[];
};

int i;

void main()
{
    ubuf.a[3];
    ubuf.b[3];
    buf.a[3];
    buf.b[3];

    ubufa[3].a[3];
    ubufa[3].b[3];
    bufa[3].a[3];
    bufa[3].b[3];

    aua[3];
    aub[3];
    aba[3];
    abb[3];

    ubuf.a[i];             // ERROR
    ubuf.b[i];             // ERROR
    buf.a[i];              // ERROR
    buf.b[i];

    ubuf.a.length();       // ERROR
    ubuf.b.length();       // ERROR
    buf.a.length();        // ERROR
    buf.b.length();

    ubufa[1].a[i];         // ERROR
    ubufa[1].b[i];         // ERROR
    bufa[1].a[i];          // ERROR
    bufa[1].b[i];

    ubufa[1].a.length();   // ERROR
    ubufa[1].b.length();   // ERROR
    bufa[1].a.length();    // ERROR
    bufa[1].b.length();

    aua[i];                // ERROR
    aub[i];                // ERROR
    aba[i];                // ERROR
    abb[i];

    aua.length();          // ERROR
    aub.length();          // ERROR
    aba.length();          // ERROR
    abb.length();
}
