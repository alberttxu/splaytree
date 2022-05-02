#define str(x) #x
#define showint(x) printf(str(x)" = %d\n", x)
#define showhex(x) printf(str(x)" = 0x%x\n", x)
#define showptr(x) printf(str(x)" = %p\n", x)
#define showaddr(x) printf("&"str(x)" = %p\n", &x)
