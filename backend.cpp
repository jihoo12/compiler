// need code formatting
#include <cstdint>
#include <vector>
class Backend {
private:
  std::vector<char> out;
  char leave = 0xC9;
  char syscall[2] = {0x0F, 0x05};
  char init[4] = {0x55, (char)0x48, (char)0x89, (char)0xE5};
  char ret = 0xC3;

public:
  struct ModRMParams {
    char base;
    char index = 0;
    char scale = 0;
    char displacement = 0;
    char dist;
    char num = 0;
    int option = 0;
    /*
      option:
      0 reg-reg
      1 reg-imm
      2 reg-memoryaddress
      3 reg-sib
      4 memoryaddress-reg
      5 memoryaddress-imm
      6 sib-reg
      7 sib-imm
     */
  };
  // need update
  void modrm(const ModRMParams &params) {
    
  }
  void movregreg(char num) {
    out.push_back(0x48);
    out.push_back(0x89);
    out.push_back(0xC0 | num);
  }
  void complexmovregreg(char dest_reg, char src_reg, int32_t disp = 0,
                        bool dest_is_mem = false) {
    out.push_back(0x48); // REX.W prefix for 64-bit operands

    if (dest_is_mem) {
      // mov [reg+disp], reg
      out.push_back(0x89); // MOV r/m64, r64
    } else {
      // mov reg, [reg+disp]
      out.push_back(0x8B); // MOV r64, r/m64
    }

    if (disp == 0 &&
        src_reg != 5) { // No displacement, except when src_reg is [rbp]
      out.push_back(0x00 | (dest_is_mem ? src_reg << 3 : dest_reg << 3) |
                    (dest_is_mem ? dest_reg : src_reg));
    } else if (disp >= -128 && disp <= 127) {
      out.push_back(0x40 | (dest_is_mem ? src_reg << 3 : dest_reg << 3) |
                    (dest_is_mem ? dest_reg : src_reg));
      out.push_back(disp & 0xFF);
    } else {
      out.push_back(0x80 | (dest_is_mem ? src_reg << 3 : dest_reg << 3) |
                    (dest_is_mem ? dest_reg : src_reg));
      for (int i = 0; i < 4; ++i) {
        out.push_back((disp >> (i * 8)) & 0xFF);
      }
    }
  }
  void movreg(char imm[4], char reg) {
    out.push_back(0x48);
    out.push_back(0xC7);
    out.push_back(0xC0 | reg);
    out.push_back(imm[0]);
    out.push_back(imm[1]);
    out.push_back(imm[2]);
    out.push_back(imm[3]);
  }
  // need update
  void sub(char imm1, char imm2, int ismem, char dist) {
    switch (ismem) {
    case 0:
      out.push_back(0x48);
      out.push_back(0x29);
      out.push_back(0xC0 | (imm1 | 8 * imm2));
      // reg,reg
      break;
    case 1:
      // reg,imm
      out.push_back(0x48);
      out.push_back(0xE8 | imm1);
      out.push_back(imm2);
      break;
    case 2:
      if (dist > 0) {

      } else {
      }
      // mem,imm
      break;
    case 3:
      // mem,reg
      break;
    case 4:
      // reg,mem
      break;
    default:
      // mem,mem
    }
  }
  void subregimm(char reg, const char imm[], int immsize) {
    out.push_back(0x48);
    if (immsize == 1) {
      out.push_back(0x83); // SUB r/m64, imm8
      out.push_back(0xE8 | reg);
      out.push_back(imm[0]);
    } else if (immsize <= 4) {
      if (reg == 0) {
        out.push_back(0x2D); // SUB RAX, imm32
      } else {
        out.push_back(0x81); // SUB r/m64, imm32
        out.push_back(0xE8 | reg);
      }
      // Add immediate value (little endian)
      for (int i = 0; i < immsize; ++i) {
        out.push_back(imm[i]);
      }
      // Pad with zeros if less than 4 bytes
      for (int i = immsize; i < 4; ++i) {
        out.push_back(0);
      }
    } else {
      // error
    }
  }
};
