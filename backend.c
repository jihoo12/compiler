#define syscall 0x0F05
#define leave 0xC9
#define pop(reg) (0x58 + (reg))
#define pushimm8(imm8) 0x6A##imm8
#define pushimm16-64(imm16-64) 0x68##imm16-64
#define pushreg(reg) (0x50 + (reg))
