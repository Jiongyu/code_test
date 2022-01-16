typedef void(*FUNC)(void);
int main(void)
{
const static unsigned char insn[4] = { 0xff, 0xff, 0xff, 0xff };
FUNC function = (FUNC) insn;
function();
return 0;
}